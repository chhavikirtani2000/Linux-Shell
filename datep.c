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
void date_command(int countinp,char* inp)
{
	int loc;
	/*pid_t pid=fork();
	if(pid==0)
	{
	                
	    execl ("/bin/date", "date",(char *)0);
	}
	else
	{
	    waitpid(pid,&loc,WUNTRACED);
	}*/
	if(countinp>2)
            {
                pid_t pid=fork();
                if(pid==0)
                {
                    int err=execl ("/bin/date", "date",inp,(char *)0);
                    printf("%d",err);
                    
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
                    int err=execl ("/bin/date","date",(char *)0);
                    
                }
                else
                {
                    waitpid(pid,&loc,WUNTRACED);
                }
            }
}