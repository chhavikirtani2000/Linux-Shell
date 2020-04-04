#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
void ls_command(int countinp,char* inp)
{
        int loc;
        if(countinp>2)
        {
                pid_t pid=fork();
                if(pid==0)
                {
                            
                    execl ("/bin/ls", "ls",inp, (char *)0);
                            
                }
                else
                {
                    waitpid(pid,&loc,WUNTRACED);
                }
        }
        else
        {
            pid_t pid=fork();
            if(pid==0)
            {
                           
                execl ("/bin/ls", "ls", (char *)0);
                            
            }
            else
            {
                waitpid(pid,&loc,WUNTRACED);
            }
        }
}