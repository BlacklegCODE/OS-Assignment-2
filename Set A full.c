#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

int main()
{
    char input[100];
    char * args[10];
    
    while(1)
    {
        printf("myShell$");
        if( fgets(input,sizeof(input),stdin) == NULL)
        break;
        
        input[strcspn(input ,"\n") ] = 0;
        
        char *tocken = strtok(input," ");
        int i = 0;
        
        while(tocken)
        {
            args[i++] = tocken;
            tocken = strtok(NULL," ");
        }
        args[i++] = NULL;
        
        pid_t pid = fork();
        
        if(pid == 0)
        {
          execv(args[0],args);
          perror("Could not execute !");
          _exit(1);
        }
        else
        {
        wait(NULL);
        }
        }
        return 0;
    }
