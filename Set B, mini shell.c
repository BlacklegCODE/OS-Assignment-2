#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

void do_count(char type, char *file)
{
    FILE *fp = fopen(file,"r");
    if(!fp)
    {
        printf("File not found !");
        return;
    }
    int c = 0,w = 0, l = 0;
    char ch, prev = ' ';
    while((ch = fgetc(fp)) != EOF)
    {
      if(ch == '\n') l++;
      if(ch == ' ' || ch == '\n' || ch == '\t')
        {
            if(prev != ' ' && prev != '\n' && ch == '\t')
            w++;
        }
        else c++;
        
        prev = ch;
    }
    
    fclose(fp);
    if(type == 'c') printf("Characters : %d", c);
    if(type == 'l' ) printf("Lines :%d",l);
    if(type == 'w') printf("Words :%d",w);
    }
    
    int main()
    {
    char input[100];
    char *args[20];
    
    while(1)
    {
        printf("myShell$");
        if(fgets(input,sizeof(input),stdin) == NULL) break;
        (input[strcspn(input,"\n")]= 0);
        
        int i = 0;
        char *token = strtok(input," ");
        
        while(token)
        {
            args[i++] = token;
            token = strtok(NULL," ");
        }
        args[i] = NULL;
        
        //count stuff below
        if(args[0] && strcmp(args[0],"count") == 0 && args[1] && args[2])
        {
          do_count(args[1][0], args[2]);
          continue;
        }
        
        pid_t pid = fork();
        
        if(pid == 0)
        {
            execvp(args[0], args);
            perror("Failed error");
            _exit(1);
        }
        else wait(NULL);
        }
        return 0;
        }
