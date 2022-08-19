#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sudk.c"


int main(){

    pthread_t tid[11]; // thread identifier.
    pthread_attr_t attr; // set of thread attributes.

    pthread_attr_init(&attr); /*get default attribute.*/

    int k=0;
    parameter * args;

    //check row.
    args=(parameter *)malloc(sizeof(parameter));
    args->k=k;
    /*creating thread and assigning task.*/
    pthread_create(&tid[k++],&attr,check_row,(void *)args);

    //check column.
    args=(parameter *)malloc(sizeof(parameter));
    args->k=k;
    pthread_create(&tid[k++],&attr,check_column,(void *)args);

    //check subgrid.
    for(int i=0;i<9;i+=3){
        for(int j=0;j<9;j+=3){
            args=(parameter *)malloc(sizeof(parameter));
            args->row=i;
            args->col=j;
            args->k=k;
            pthread_create(&tid[k++],&attr,check_subgrid,(void *)args);
        }
    }

    //join thread.
    for(int i=0;i<11;i++){
        pthread_join(tid[i],NULL); /*wait for the thread to exit.*/
    }

    //output res.
    for(int i=0;i<11;i++){
        printf("%d,",res[i]);
    }
    printf("\n");

}

void * check_column(void *ptr){
    parameter *args=(parameter *)ptr;
    for(int col=0;col<9;col++){
        int freq[10]={0};
        for(int i=0;i<9;i++){
            freq[grid[i][col]]++;
        }
        for(int i=1;i<=9;i++){
            if(freq[i]>1){
                res[args->k]=0;
                free(args);
                pthread_exit(0);
            }
        }
    }
    res[args->k]=1;
    free(args);
    pthread_exit(0);
}

void * check_row(void *ptr){
    parameter *args=(parameter *)ptr;
    for(int row = 0;row<9;row++){
        int freq[10]={0};
        for(int i=0;i<9;i++){
            freq[grid[row][i]]++;
        }
        for(int i=1;i<=9;i++){
            if(freq[i]>1){
                res[args->k]=0;
                free(args);
                pthread_exit(0);
            }
        }
    }
    res[args->k]=1;
    free(args);
    pthread_exit(0);
}

void* check_subgrid(void *ptr){
    parameter *args=(parameter *)ptr;
    int row=args->row;
    int col=args->col;
    int freq[10]={0};
    for(int i=row;i<row+3;i++){
        for(int j=col;j<col+3;j++){
            freq[grid[i][j]]++;   
        }
    }
    for(int i=1;i<=9;i++){
        if(freq[i]>1){
            res[args->k]=0;
            free(args);
            pthread_exit(0);
        }
    }
    res[args->k]=1;
    free(args);
    pthread_exit(0);
}