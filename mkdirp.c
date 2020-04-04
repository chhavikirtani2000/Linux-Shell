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
void mkdir_command(int countinp, char* inp1, char* inp2)
{
	int loc;
	if(countinp>3)
            {
                pid_t pid=fork();
                if(pid==0)
                {
                    execl ("/bin/mkdir","mkdir",inp1,inp2,(char *)0);
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
                    execl ("/bin/mkdir","mkdir",inp1,(char *)0);
                }
                else
                {
                    waitpid(pid,&loc,WUNTRACED);
                }
            }
}