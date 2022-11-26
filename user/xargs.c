#include "kernel/types.h"
#include "user.h"
#include "kernel/param.h"
#include <stddef.h>

void doNextLine(int argc, char* argv[]){
    int status;
    //char* line = (char*) malloc(sizeof(char)*MAXARG);
    char line[MAXARG];
    if(strcmp(gets(line,MAXARG-argc),"")==0){
        exit(0);
    }
    line[strlen(line)-1] = '\0';
    char* arguments[MAXARG];
    memmove(arguments,argv+1,(argc-1)*sizeof(char*));
    char** p = arguments+argc-1;
    *p = line;
    p++;
    *p = malloc(sizeof(char));
    **p=0;
    int pid = fork();
    if(pid < 0){
        exit(-1);
    } else if(pid >0){
        if(wait(&status)>0){
            doNextLine(argc,argv);
        }
    } else {
        exec(arguments[0],arguments);
    }
}
int main(int argc,char* argv[]){
    int status;
    char line[MAXARG];
    if(strcmp(gets(line,MAXARG-argc),"")==0){
        exit(0);
    }
    line[strlen(line)-1] = '\0';
    char* arguments[MAXARG];
    memmove(arguments,argv+1,(argc-1)*sizeof(char*));
    //char* rest = malloc(sizeof(char)*MAXARG);
    char** p = arguments+argc-1;
    *p = line;
    p++;
    *p = malloc(sizeof(char));
    **p=0;
    int pid = fork();
    if(pid < 0){
        exit(-1);
    } else if(pid >0){
        if(wait(&status)>0){
            doNextLine(argc,argv);
        }
    } else {
        exec(arguments[0],arguments);
    }
    exit(0);
}