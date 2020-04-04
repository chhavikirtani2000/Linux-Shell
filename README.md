# Linux-Shell
I developed a linux shell using C programming and system calls.
Maximum arguments in the command acceptable are 10, each argument needs to be separated by space. Commands shell accepts: Ls​- ls command 
can accept all possible options a normal ls can accept(--color,-a,-1 etc). Ls has been implemented using execl() system call using the file
available in the bin directory. Error handling and corner cases- None was required for ls. Mkdir​- mkdir command can accept all possible 
options a normal mkdir can accept. Mkdir has been implemented using execl() system call using the file available in the bin directory. 
Error handling and corner cases- shell throws an error if the given directory already exists or if no second argument is provided after 
writing mkdir. Assumptions- shell can be used to make only one directory at a time. Rm​- rm command can accept all possible options a 
normal rm can accept. rmdir has been implemented using execl() system call using the file available in the bin directory. Error handling 
and corner cases- shell throws an error if the given directory/file does not exist or if no second argument is provided after writing rm. 
Assumptions- shell can be used to remove only one directory/file at a time. Date​- date command can accept all possible options a normal 
date can accept. Date has been implemented using execl() system call using the file available in the bin directory. Error handling and 
corner cases- None was required for date. Cat​- cat command can accept options like- “-n”,”-E”,”-e” etc. cat has been implemented using 
execl() system call using the file available in the bin directory. Error handling and corner cases- shell throws an error when no such 
file as specified exists or there is no second argument provided. 
 History​- I have defined a function add_history a container history to store all the previous commands. History command accepts options 
 like “-c”(delete previous history) and “3”(show only first 3 stored commands) etc, working for the above options have been implemented 
 using separate if conditions. Error handling and corner cases- Shows a message “No history available to show” in case the buffer is empty.
 Echo​- I have defined a loop which prints the arguments given after echo command. Options handled are “/n” gives a line break and “/t” 
 gives a tab space. Error handling and corner cases- shell prints a blank line in case there is nothing to echo. Cd​- cd command is 
 implemented using chdir() function. It handles cd .. type of command too. Other than that, there were no more options to handle. Error 
 handling and corner cases- Assumes it to be equivalent to cd .. if no argument is provided after cd. Pwd​- pwd command accepts all kinds 
 of options a normal pwd would. It has been implemented using execl() system call to the bin directory.  Error Handling and corner cases- 
 There was no need to error handling for pwd command. Exit​- exit command gets executed by using break option. No options needed.  Errors 
 and corner cases/Assumption: exit exits the shell no matter whatever we type after exit. TEST CASES: 
1. Pwd 
2. ls --color 
3. ls -a 
4. date 
5. date -u 
6. mkdir -v mydir 
7. rm file1 
8. cat text.txt 
9. echo my name is /n chhavi 
10.history 
11. history -c 
 
 
