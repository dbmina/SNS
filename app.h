#ifndef PROBLEM2_APP_H
#define PROBLEM2_APP_H

#include <vector>

class App {

public:
    App(std::istream& is, std::ostream& os);
    void run();
    bool authenticate(std::string id, std::string pass);

    void post(std::string id, std::string title, std::string password);
    void recommend(std::string id);
    void search(std::string keyword);
    void count(std::vector<std::string> str);
private:
    std::istream& is;
    std::ostream& os;
};

#endif //PROBLEM2_APP_H
