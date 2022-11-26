#include "kernel/types.h"
#include "user.h"

void choseData(char fromData[][2],char chosenData[][2]) {
    int i;
    int k=0;
    char num[2];
    
    int key;
    for(i=0;i<(strlen(*fromData)/2);i++){
        for(int j=0;j<2;j++){
            num[j]=fromData[i][j];
        }
        if(i==0){
            printf("prime %d\n",atoi(num));
            key = atoi(num);
        }
        if(atoi(num)%key!=0){
            for(int j=0;j<2;j++){
                chosenData[k][j] = num[j];
            }
            k++;
        }
    }
    for(;k<(strlen(*chosenData)/2);k++){
        for(int j=0;j<2;j++){
            chosenData[k][j]='\0';
        }
    }
}

void handle(char fromData[][2],char chosenData[][2]){
    if ((strlen(*fromData)/2)<=0){
        exit(0);
    }
    int p[2];
    pipe(p);
    int pid=fork();
    if(pid<0){
        exit(-1);
    } else if(pid >0){
        close(p[0]);
        write(p[1],chosenData,60);
        close(p[1]);
    } else{
        close(p[1]);
        read(p[0],fromData,60);
        close(p[0]);
        choseData(fromData,chosenData);
        handle(fromData,chosenData);
        
    }
}
int main(int argc,char* argv[]){
    char data[30][2]={"02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31"};
    int p1[2];
    pipe(p1);
    int pid = fork();
    char fromData[30][2];
    char chosenData[30][2];
    if(pid < 0){
        exit(-1);
    } else if (pid > 0){
        close(p1[0]);
        write(p1[1],data,sizeof(data));
        close(p1[1]);
        sleep(10);

    } else {
        close(p1[1]);
        read(p1[0],fromData,sizeof(fromData));
        close(p1[0]);
        choseData(fromData,chosenData);
        handle(fromData,chosenData);
        
    }
    exit(0);
}





// for(i=0;i<(strlen(fromData)/2);i++){
//                 for(int j=0;j<2;j++){
//                     num[j]=fromData[i][j];
//                 }
//                 if(i==0){
//                     printf("prime %d\n",atoi(num));
//                 }
//                 if(atoi(num)%2!=0){
//                     for(int j=0;j<2;j++){
//                         chosenData[k][j] = num[j];
//                     }
//                     k++;
//                 }
//             }


// int p2[2];
//         pipe(p2);
//         pid=fork();
//         if(pid<0){
//             exit(-1);
//         } else if(pid >0){
//             close(p2[0]);
//             write(p2[1],chosenData,sizeof(chosenData));
//             close(p2[1]);
//             sleep(40);
//         } else {
//             close(p2[1]);
//             read(p2[0],fromData,sizeof(fromData));
//             close(p2[0]);
//             choseData(fromData,chosenData);
//             int p3[2];
//             pipe(p3);
//             pid=fork();
//             if(pid<0){
//                 exit(-1);
//             } else if(pid >0){
//                 close(p3[0]);
//                 write(p3[1],chosenData,sizeof(chosenData));
//                 close(p3[1]);
//                 sleep(30);
//             } else {
//                 close(p3[1]);
//                 read(p3[0],fromData,sizeof(fromData));
//                 close(p3[0]);
//                 choseData(fromData,chosenData);
//                 int p4[2];
//                 pipe(p4);
//                 pid=fork();
//                 if(pid<0){
//                     exit(-1);
//                 } else if(pid >0){
//                     close(p4[0]);
//                     write(p4[1],chosenData,sizeof(chosenData));
//                     close(p4[1]);
//                     sleep(20);
//                 } else {
//                     close(p4[1]);
//                     read(p4[0],fromData,sizeof(fromData));
//                     close(p4[0]);
//                     choseData(fromData,chosenData);
//                     int p5[2];
//                     pipe(p5);
//                     pid=fork();
//                     if(pid<0){
//                         exit(-1);
//                     } else if(pid >0){
//                         close(p5[0]);
//                         write(p5[1],chosenData,sizeof(chosenData));
//                         close(p5[1]);
//                         sleep(10);
//                     } else {
//                         close(p5[1]);
//                         read(p5[0],fromData,sizeof(fromData));
//                         close(p5[0]);
//                         choseData(fromData,chosenData);
//                     }
//                 }
//             }
//         }
        