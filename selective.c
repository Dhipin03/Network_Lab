#include<stdio.h>

int main(){
    int w,i,ack,sent=0;
    printf("enter the window size:");
    scanf("%d",&w);

    for(i=0;i<=w;i++){
        printf("\nframe %d has been transmited\n",sent);
        sent++;
        if(sent==w){
            break;
        }
    }
    while(1){
        printf("enter the frame number ack not recieved");
        scanf("%d",&ack);
        if(ack>w){
            printf("inavalid");
        }
        else{
            printf("%d is transmitted",ack);
        }


    }
    return 0;
}