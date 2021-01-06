#include <iostream>
#include <fstream>
#include "app.h"
#include "config.h"
#include <filesystem>
#include "time.h"
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>

App::App(std::istream& is, std::ostream& os): is(is), os(os) {
    // TODO
}
bool App::authenticate(std::string id, std::string pass){
    std::ifstream file;
    std::string realpass;
    file.open(SERVER_STORAGE_DIR+id+"/password.txt");
    if (file.is_open()){
        file>>realpass;
    }
    if (realpass==pass){
        return true;
    }
    else{
        return false;
    }

}

void App::post(std::string id, std::string title, std::string content) {
    int number = 0;
    int max = 0;
    std::string path = SERVER_STORAGE_DIR;

    for (const auto &file: std::filesystem::directory_iterator(path)) {
        for (const auto &sub: std::filesystem::directory_iterator(file.path() / "post")) {
            std::string name = sub.path().filename().string();
            std::string deli = ".";
            number = std::stoi(name.substr(0, name.find(deli)));
            if (number > max) {
                max = number;
            }
        }
    }

    std::ofstream write(SERVER_STORAGE_DIR + id + "/post/" + std::to_string(max+1) + ".txt");
    time_t currentTime = time(NULL);
    struct tm *local = localtime(&currentTime);
    std::string date=std::to_string(local->tm_year+1900)+"/"+std::to_string(local->tm_mon+1)+"/"+std::to_string(
            local->tm_mday)+" "+std::to_string(local->tm_hour)+":"+std::to_string(local->tm_min)+":"+std::to_string(local->tm_sec);
    write<<date+"\n";
    write<<title+"\n\n";
    write<<content;
    write.close();

}


bool compare2(std::string a1, std::string a2){
    std::string line1;
    std::string line2;
    line1=a1.substr(a1.find("t: "), a1.find("t: ")+5);
    line2=a2.substr(a2.find("t: "), a1.find("t: ")+5);
    line1=line1.substr(3, line1.size());
    line2=line2.substr(3, line2.size());
    return (line1>line2);
}
void App::recommend(std::string id){
    std::ifstream read(SERVER_STORAGE_DIR + id + "/friend.txt");
    std::string friends;

    std::string oneline;
    std::vector<std::string> str;
  while(!read.eof()){
    std::getline(read, friends);
      std::string path = SERVER_STORAGE_DIR+friends+"/post";
      for (const auto &file: std::filesystem::directory_iterator(path)) {
          std::string tmpread="";
          tmpread+=("id: "+file.path().filename().string().substr(0, file.path().filename().string().find("."))+"\ncreated at: ");
          std::ifstream tmp(file.path());
          std::getline(tmp, oneline);
          tmpread+=oneline+"\ntitle: ";

          std::getline(tmp, oneline);

          tmpread+=oneline+"\ncontent:\n";
          while(!tmp.eof()){

              std::getline(tmp, oneline);
              if (oneline!=""){
                  tmpread+=oneline+"\n";
              }

          }
          tmpread.erase(tmpread.find_last_not_of("\n"));
          str.push_back(tmpread);
      }
  }
  std::sort(str.begin(), str.end(), compare2);

  for(int i=0; i<9; i++){
     os<<str.at(i);
      os<<"\n-----------------------------------\n";
  }
    os<<str.at(9)<<"\n";

}
bool comparison(std::string s1, std::string s2){
    std:: istringstream ss(s1);
    std:: istringstream ss2(s2);
    std::string f;
    std::string f2;

    getline(ss, f, '\n');
    getline(ss2, f2, '\n');
    if (f!=f2){
        return (f>f2);
    }
    else{
        return compare2(s1, s2);
    }
}
void App::count(std::vector<std::string> str){


    std::string path = SERVER_STORAGE_DIR;
std::string tmp_;
std::string oneline;
std::vector<std::string>::iterator it;
std::vector<std::string>::iterator it2;
std::vector<std::string> word;
std::vector<std::string> stringcollect;
    for (const auto &file: std::filesystem::directory_iterator(path)) {
        for (const auto &sub: std::filesystem::directory_iterator(file.path() / "post")) {
            std::string tmpread="";
            tmp_=("id: "+sub.path().filename().string().substr(0, sub.path().filename().string().find("."))+", ");
            std::ifstream tmp(sub.path());
            std::getline(tmp, oneline);

            tmp_+=("created at: "+oneline+", ");
            std::getline(tmp, oneline);
            tmp_+=("title: "+oneline);
            tmpread+=oneline+" ";
            while(!tmp.eof()){

                std::getline(tmp, oneline);
                if (oneline!=""){
                    tmpread+=oneline+" ";
                }

            }
            int count=0;


            std:: istringstream ss(tmpread);
            std::string f;
            while(getline(ss, f, ' ')){
             word.push_back(f);
            }
            int i=0;
            for (it=str.begin(); it!=str.end(); it++){
                int j=0;
                for(it2=word.begin(); it2!=word.end(); it2++){
                    if (str.at(i)==word.at(j)){
                        count++;
                    }
                    j++;
                }
                i++;
            }
            word.clear();
            tmp_=std::to_string(count)+"\n"+tmp_;
            if (count>0){
                stringcollect.push_back(tmp_);
            }

        }
    }
   std::sort(stringcollect.begin(), stringcollect.end(), comparison);
    if (stringcollect.size()>=10){

        for(int i=0; i<10; i++){

            os<<stringcollect.at(i).substr(stringcollect.at(i).find("\n")+1, stringcollect.at(i).size())<<"\n";
        }

    }
    else{
        for(int i=0; i<stringcollect.size()-1; i++){
            os<<stringcollect.at(i).substr(stringcollect.at(i).find("\n")+1, stringcollect.at(i).size())<<"\n";
        }
        os<<stringcollect.at(stringcollect.size()-1).
        substr(stringcollect.at(stringcollect.size()-1).find("\n")+1, stringcollect.at(stringcollect.size()-1).size())<<"\n";
    }

}
void App::search(std::string keyword){
    std::vector<std::string> only;

    std:: istringstream ss(keyword);
    std::string f;
    while(getline(ss, f, ' ')){
        only.push_back(f);
    }
    std::sort(only.begin(), only.end());
    only.erase(std::unique(only.begin(), only.end()), only.end());
     std::unique(only.begin(), only.end());
    count(only);
}
void App::run() {
    // TODO
    std::string id;
    std::string pass;
    std::string command;

        os<<"------ Authentication ------\n";
        os<<"id=";
        is>>id;
        os<<"passwd=";
        is>>pass;
    is.ignore();
     if (authenticate(id, pass)){
     }
     else{
         os<<"Failed Authentication.\n";
        return;
     }
    while (true){
        os<<"-----------------------------------\n";
        os<<id<<"@sns.com\n";
        os<<"post : Post contents\nrecommend : recommend interesting posts\nsearch <keyword> : List post entries whose contents contain <keyword>\nexit : Terminate this program\n";
        os<<"-----------------------------------\n";
        os<<"Command=";

       std::getline(is, command);
        if (command=="exit"){
            break;
        }
        if (command=="post"){
         std::string title;
         std::string tmpcontent="33";

         std::string content;
         os<<"-----------------------------------\n";
         os<<"New Post\n";
         os<<"* Title=";
            is.ignore();
            std::getline(is, title);


         os<<"* Content\n";
do{
    os<<">";
    std::getline(is, tmpcontent);

    content+=(tmpcontent+"\n");
}while(tmpcontent.length()!=0);

         post(id ,title, content);
        }

        if (command=="recommend"){
            os<<"-----------------------------------\n";
          recommend(id);
        }
        std::string tt=command;
        if (tt.substr(0, 6)=="search"){

            os<<"-----------------------------------\n";
            search(command.substr(7 , command.size()));
        }

    }
}
