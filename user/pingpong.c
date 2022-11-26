#include "kernel/types.h"
#include "user.h"

int main(int argc,char* argv[]){
    int p[2];
    int q[2];
    if(pipe(p) <0){
        printf("Error\n");
        exit(-1);
    }
    if (pipe(q) <0){
            exit(-1);
    }
    char needToPing[] = "ping";
    char ping[5];
    ping[4] = '\0';
    char needToPong[] = "pong";
    char pong[5];
    pong[4] = '\0';
    int pid = fork();
    if(pid <0){
        printf("Error\n");
        exit(-1);
    } else if(pid >0) {
        close(p[0]);
        close(q[1]);
        write(p[1],needToPing,sizeof(needToPing));
        close(p[1]);
        sleep(10);
        read(q[0],pong,sizeof(pong));
        close(q[0]);
        printf("%d: received %s\n",q[0],pong);
    } else {
        close(p[1]);
        close(q[0]);
        read(p[0],ping,sizeof(ping));
        close(p[0]);
        printf("%d: received %s\n",p[0],ping);
        write(q[1],needToPong,sizeof(needToPong));
        close(q[1]);
    }
    
    exit(0);
}