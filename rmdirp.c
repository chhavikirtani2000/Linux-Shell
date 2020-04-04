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
void rmdir_command(int countinp,char* inp1,char* inp2)
{
	int loc;
	if(countinp>3)
            {
                pid_t pid=fork();
                if(pid==0)
                {
                    int err=execl ("/bin/rm", "rm",inp1 ,inp2,(char *)0);
                    printf("%d",err);
                    if(err==-1)
                    {
                        printf("Error in removing");
                    }
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
                    int err=execl ("/bin/rm","rm",inp1,(char *)0);
                    if(err==-1)
                    {
                        printf("Error in removing");
                    }
                }
                else
                {
                    waitpid(pid,&loc,WUNTRACED);
                }
            }
}