#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

#define MAX_SIZE 80
#define MAX_ARGS 20

void args_list(char *args[],char *s){
    char *token=strtok(s," ");
    int i=0;
    while(token!=NULL){
        args[i]=(char *)malloc((strlen(token)+1)*sizeof(char));    
        strcpy(args[i++],token);
        token=strtok(NULL," ");
    }
    args[i]=NULL;
}

int main(){
    char buff[MAX_SIZE];
    char *args[MAX_ARGS];

    while(1){
        printf("mish>");
        fflush(stdout);
        scanf("%[^\n]%*c",buff);
        args_list(args,buff);
    
        if(strcmp(args[0],"exit")!=0){
            pid_t pid=fork();
            if(pid==0){
                //child.
                execvp(args[0],args);
            }
            else{
                wait();
            }
        }
        else{
            free(args[0]);
            break;
        }
        for(int i=0;args[i]!=NULL;i++) free(args[i]);
        
    }

}