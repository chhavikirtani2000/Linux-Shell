#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
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
#include "datep.c"
#include "lsp.c"
#include "catp.c"
#include "mkdirp.c"
#include "rmdirp.c"

#define ARGMAX 10
#define HMS 100

char *input;

char* inp[ARGMAX];
int countinp = 0;

char *history[HMS];
int tp = 0;

void function_pwd(char* cwd)
{
    char temp[1000];
    char* path=getcwd(temp, sizeof(temp));
    
    strcpy(cwd,temp);
   
    printf("%s\n",cwd);
}
void getInput()
{
    fflush(NULL); 
    input = NULL;
    ssize_t sz = 0;
    getline(&input,&sz,stdin);
    
    countinp = 0;
    
    while((inp[countinp] = strsep(&input, " \t\n")) != NULL && countinp < ARGMAX-1)
    {
        if(sizeof(inp[countinp])==0)
        {
            free(inp[countinp]);
        }
        else countinp++;
    }
    free(input);
   
}


void add_history( const char *command )
{
    if (tp<HMS)
    {
        history[tp] = strdup(command);
        tp++;
    }
    else 
    {
        free( history[0] );
        for (int i= 1; i< HMS-1; i++)
        {
            history[i] = history[i+1];
        }
        history[HMS - 1] = strdup(command);
    }
}

int main(int argc, char* argv[])
{ 
    
    int loc;
    //printf("yoo");
    while(1)
    {
        char cwd[1024];
        getcwd(cwd,sizeof(cwd));
        
        printf("%s",cwd);
        printf("$>");
        getInput();
        

        if(strcmp(inp[0],"exit")==0)
        {

            add_history(inp[0]);
            break;
            
        }
        else if(strcmp(inp[0],"pwd")==0)
        {
            //function_pwd(cwd);
            if(countinp>2)
            {
                pid_t pid=fork();
                if(pid==0)
                {
                    
                    execl ("/bin/pwd", "pwd",inp[1], (char *)0);
                    
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
                   
                    execl ("/bin/pwd", "pwd", (char *)0);
                    
                }
                else
                {
                    waitpid(pid,&loc,WUNTRACED);
                }
            }
            //execl ("/bin/pwd", "pwd",(char *)0);
            add_history(inp[0]);
        }
        else if(strcmp(inp[0],"date")==0)
        {
            /*pid_t pid=fork();
            if(pid==0)
            {
                
                execl ("/bin/date", "date",(char *)0);
            }
            else
            {
                waitpid(pid,&loc,WUNTRACED);
            }*/
            date_command(countinp,inp[1]);
            

            add_history(inp[0]);
        }

        else if(strcmp(inp[0],"echo")==0)
        {

            for(int y=1;y<countinp;y++)
            {
                //printf("%s",inp[y]);
                if(strcmp(inp[y],"/n")==0)
                {
                    //printf("%s",inp[y]);
                    printf("%c",10);
                    
                }
                else if(strcmp(inp[y],"/t")==0)
                {
                    printf("%s","   ");
                }
                else
                {
                    printf("%s%s",inp[y]," ");
                }
            }
            
            printf("\n");
            /*char* ip[1];
            ip[0]="";
            for(int y=1;y<countinp;y++)
            {
                //printf("%s%s",inp[y]," ");
                ip[0]=ip[0]+inp[y]+" ";

            }
            execl ("/bin/echo", "echo",ip, (char *)0);*/
            add_history(inp[0]);
        }
        else if(strcmp(inp[0],"history")==0)
        {
            if(countinp>2)
            {
                //printf("hello");
                //printf("%s",inp[1]);
                if(strcmp(inp[1],"-c"))
                {
                    memset(history,0,sizeof history);
                }
                else if(*inp[1]==3)
                {
                    int sz=atoi(inp[1]);
                    for(int k=0;k<sz;k++)
                    {
                        printf("%s",history[k]);
                        printf("\n");

                    }

                }
            }
            else
            {
                //int abc=0;
                for(int k=0;k<tp;k++)
                {
                    //if(strcmp(history[k],"NULL")==1)
                    //{
                        printf("%s",history[k]);
                        printf("\n");
                        //abc=abc+1;
                    //}
                }
                if(tp==0)
                {
                    printf("No history available to show");
                    printf("\n");
                }
                

            }
            /*for(int k=0;k<tp;k++)
            {
                printf("%s",history[k]);
                printf("\n");

            }*/
            /*if(countinp>2)
            {
                pid_t pid=fork();
                if(pid==0)
                {
                    
                    execl ("/bin/history", "history",inp[1], (char *)0);
                    
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
            }*/
            //execl ("/bin/history","history",(char *)0);
            add_history(inp[0]);
            
        }
        else if(strcmp(inp[0],"cd")==0)
        {
            if(countinp<3)
            {
                //printf("error: directory name required");
                //printf("\n");
                chdir("..");
            }
            else
            {
                chdir(inp[1]);
            }
            add_history(inp[0]);
          

        }
        else if(strcmp(inp[0],"ls")==0)//done
        {
            ls_command(countinp,inp[1]);
            /*if(countinp>2)
            {
                pid_t pid=fork();
                if(pid==0)
                {
                    
                    execl ("/bin/ls", "ls",inp[1], (char *)0);
                    
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
            }*/
            
            add_history(inp[0]);
        }
        else if(strcmp(inp[0],"cat")==0)//done
        {
            
            /*if(countinp>3)
            {
                pid_t pid=fork();
                if(pid==0)
                {
                    execl ("/bin/cat","cat",inp[1],inp[2],(char *)0);
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
                    execl ("/bin/cat","cat",inp[1],(char *)0);
                }
                else
                {
                    waitpid(pid,&loc,WUNTRACED);
                }
            }*/
            if(countinp<3)
            {
                printf("error: file name required");
                printf("\n");
            }
            else
            {
                cat_function(countinp,inp[1],inp[2]);
                printf("\n");
            }
            add_history(inp[0]);
            
        }


        else if(strcmp(inp[0],"mkdir")==0)
        {
            /*if(countinp>3)
            {
                pid_t pid=fork();
                if(pid==0)
                {
                    execl ("/bin/mkdir","mkdir",inp[1],inp[2],(char *)0);
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
                    execl ("/bin/mkdir","mkdir",inp[1],(char *)0);
                }
                else
                {
                    waitpid(pid,&loc,WUNTRACED);
                }
            }*/
            if(countinp<3)
            {
                printf("directory name required");
                printf("\n");
            }
            else
            {
                mkdir_command(countinp,inp[1],inp[2]);
            }
            add_history(inp[0]);
           
        }
        else if(strcmp(inp[0],"rm")==0)
        {
            /*if(countinp>3)
            {
                pid_t pid=fork();
                if(pid==0)
                {
                    int err=execl ("/bin/rmdir", "rmdir",inp[1] ,inp[2],(char *)0);
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
                    int err=execl ("/bin/rmdir","rmdir",inp[1],(char *)0);
                    if(err==-1)
                    {
                        printf("Error in removing");
                    }
                }
                else
                {
                    waitpid(pid,&loc,WUNTRACED);
                }
            }*/
            if(countinp<3)
            {
                printf("error: directory/file name required");
                printf("\n");
            }
            else
            {
                
                rmdir_command(countinp,inp[1],inp[2]);
            }
            
           
            add_history(inp[0]);

            
        }  
    }
}



