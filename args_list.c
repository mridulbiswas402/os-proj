#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 80
#define MAX_ARGS 10

char ** args_list(char *s){
    char **args=(char **)malloc(sizeof(char*)*MAX_ARGS);
    char *token=strtok(s," ");

    int i=0;
    while(token!=NULL){
        args[i]=(char *)malloc((strlen(token)+1)*sizeof(char));    
        strcpy(args[i++],token);
        token=strtok(NULL," ");
    }
    return args;
}

int main(){
    char buff[MAX_SIZE];
    scanf("%[^\n]%*c",buff);
    char **args=args_list(buff);

    for(int i=0;args[i]!=NULL;i++){
        printf("%s\n",args[i]);
    }
}
