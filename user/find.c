#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"



void find(char* path,char* filename) {
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512], *p;
    if((fd = open(path, 0)) < 0){
        fprintf(2, "2 ls: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }
    
    switch(st.type){
        case T_FILE:
            if(strcmp(path,filename)==0){
                printf("1:%s\n",path);
            }
            close(fd);
            return ;
        case T_DIR:
            if(strlen(path)+1+DIRSIZ+1>sizeof(buf)){
                printf("find: path too long\n");
                break;
            }
            strcpy(buf, path);
            p=buf+strlen(buf);
            *p++='/';
            while(read(fd, &de, sizeof(de)) == sizeof(de)) {
                if(de.inum == 0){
                    if(strcmp(path,filename)==0){
                        printf("2:%s\n",path);
                    }
                } 
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ]=0;
                if(strcmp(p,filename)==0){
                    printf("%s\n",buf);
                } else if (strcmp(p,".")==0 || strcmp(p,"..")==0){
                    
                }else{
                    find(buf,filename);
                }
            }
            close(fd);
            break;
    }
    return ;
}

int main(int argc,char* argv[]){
    int fd;
    char buf[512], *p;
    char *path;
    char *filename;
    struct stat st;
    struct dirent de;
    if(argc == 2){
        path = ".";
        filename = argv[1];
    } else if (argc <2){
        path = ".";
        filename = ".";
    } else if(argc > 2){
        path = argv[1];
        filename = argv[2];
    }

    if((fd=open(path,0))<0){
        fprintf(2, "1 find: cannnot open %s\n", path);
        exit(0);
    }
    if(fstat(fd, &st)<0){
        fprintf(2, "find: cannot stat %s", path);
        close(fd);
        exit(0);
    }

    switch(st.type){
        case T_FILE:
            if(strcmp(path,filename)==0){
                printf("3:%s\n",path);
            }
            close(fd);
        case T_DIR:
            if(strlen(path)+1+DIRSIZ+1>sizeof(buf)){
                printf("find: path too long\n");
                break;
            }
            if(strcmp(path,filename)==0){
                printf("4:%s\n",path);
            }
            strcpy(buf, path);
            p=buf+strlen(buf);
            *p++='/';
            while(read(fd, &de, sizeof(de)) == sizeof(de)) {
                if(de.inum == 0){  
                    exit(0);
                } 
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ]=0;
                if(strcmp(p,filename)==0){
                    printf("%s\n",buf);
                } else if (strcmp(p,".")==0 || strcmp(p,"..")==0){

                }else{
                    find(buf,filename);
                }
            }
            close(fd);
    }
    exit(0);
}    