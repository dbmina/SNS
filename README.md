# SNS
## implementation of SNS

### Problem 1: Authenticate        
Objective: Implement an authentication feature. In particular, it compares the input password with the password stored in the server to check its validity.       
Description: Upon the program start, the console will ask for the user id and the password.     
In the given skeleton code, a user cannot log in even with a valid password.        
Now, we want to change it so that login can be possible with a valid password.         
● The password of a user is stored at the path $(DATA_DIRECTORY)/(User ID)/password.txt; here, the (User ID) is the id of the user.            
● Assume that all the names of the direct child directories of $(DATA_DIRECTORY) are valid user ids.  
● Assume that every $(DATA_DIRECTORY)/(User ID) has a password.txt.The format of the password.txt is given in the following example (plain text without a newline).    
Suppose the password of the user ‘root’ is ‘pivot@eee’.        
● For successful authentication, the input password and the stored password should be identical including white spaces.         
● If the login fails, the program terminates.      
Note that text in red in the following example indicates the user input, and the text in blue indicates the currently authenticated user ID:       \

### Problem 2: Post a User Article
Objective: Implement a posting feature to store the written post on the server.          
Description: When a user inputs the “post” command to the console, he can start writing a post with the title and content.      
The content of the post ends when the user inputs “Enter” twice.          
● Store the user’s post at the path $(DATA_DIRECTORY)/(User ID)/post/(Post ID).txt.        
(User ID) is the user’s id used for the login, and the (Post ID) is the nonnegative integer assigned uniquely to each and every post in the $(DATA_DIRECTORY).       
The newly assigned ID should be 1 + the largest post id in the entire posts of all users in $(DATA_DIRECTORY) .         
● Assume all the $(DATA_DIRECTORY)/(User ID) has a directory named post, and each post directory has at least one post.         
● The format of the post file is given in the examples below.      
● The content of the post should not include the trailing empty line.        
For example, let’s say that the user name is ‘root’, and the largest post id in the entire $(DATA_DIRECTORY) is 302.        
Then, the new post id should be 302 + 1 = 303. Also, let’s say that the post date is 2019/12/11 21:01:02, the post creation date/time for the local timezone. 
Then the post is saved to "$(DATA_DIRECTORY)/root/post/303.txt".          


### Problem 3: Recommend Friends’ Posts 
Objective: Implement the recommendation feature to print the latest posts of the user’s friends.       
Description: Our SNS service recommends a user the latest posts of her friends.        
When the user inputs the “recommend” command to the console, up to 10 latest posts of the friends should be displayed.        
● The list of the user’s friends is stored at the path "$(DATA_DIRECTORY)/(User ID)/friend.txt".          
The format of the friend.txt is given in the following example. Suppose the user “root” has 3 friends, “admin”, “redis”, and “remp”.            
● You need to look at all the posts of the friends and print up to 10 posts with the latest created dates.         
● It is not guaranteed that the ids of the posts we provide in the skeleton is not in the order of post creation time.      
● How do we decide those 10 posts to recommend?        
○ Sort posts by the created date specified in a post file in descending order (from latest to oldest).        
○ Select the first 10 posts from the sorted list.         
● Assume the created date and time of each post is unique. No two posts have the same created date and time.        
● Assume all the friend IDs on the friend.txt are valid, and the corresponding folders exist in the $(DATA_DIRECTORY).       

### Problem 4: Search Posts     
Objective: Implement the searching feature to display up to 10 posts that contain at least one keyword.       
Description: Our SNS service enables users to search for posts with multiple keywords.         
When the user inputs the “search” command along with a set of keywords, the console should display up to 10 posts containing the most number of keywords in descending order of the created date and time.     
● The range of the search is the entire posts of all users (NOT friends only) in the $(DATA_DIRECTORY).      
● The command string starts with “search” followed by keywords.           
● Two keywords are separated with space(‘ ’). The newline should not be considered as a keyword.       
● Duplicate keywords should be ignored. For example, the output of "search hi hi" should be identical to the output of "search hi".       
● You should count the number of occurrences of the exact keyword from the title and the content of the post.     
● More specific details for the keyword matching:        
○ It should be a case-sensitive comparison.       
○ You should only count the word that is identical to the provided keyword. You don’t need to consider the word that has the given keyword as a substring.     
● For example, the input command is "search to to be", and the content of a post "To be trusted is a greater compliment than to be loved.". Then the keywords are "to" and "be",
and the number of occurrences of the keyword from the content is 3.       
● How do we decide those posts to show?         
○ Sort the candidate posts based on two criteria. First, sort by the number of occurrences of the keywords in descending order.         
When multiple posts have the same number of occurrences, sort them by the created date and time of the post in descending order (from latest to oldest).          
○ Select up to 10 posts from the beginning of the sorted list.         
● Print a summary (id, creation date/time, title) of each post in one line
