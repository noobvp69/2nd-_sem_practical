#include<stdio.h>
#include<stdlib.h>

int empty = 5;
int mutex =1;
int buffer[5];
int full=0;
int in=0;
int out=0;

void wait(int *s){
    while(*s <=0);
    (*s)--;
}
void signal(int *s){
    (*s)++;
}

void producer(){
    int item;
    if(empty==0){
        printf("buffer is full. Cannot produce more! ");
        return;
    }
    printf("Enter an item: ");
    scanf("%d",&item);

    wait(&empty);
    wait(&mutex);
    buffer[in]=item;
    in=(in+1)%5;
    signal(&mutex);
    signal(&full);
    printf("Produced item is %d\n",item);
}

void consumer(){
    if(full==0){
        printf("Buffer is empty cannot consume more!");
        return;

    }
    wait(&full);
    wait(&mutex);
    int item = buffer[out];
    out = (out+1)%5;
    signal(&mutex);
    signal(&empty);
    printf("Consumed item is %d\n",item);
}

int main(){
    int ch;
    printf("\n1.Producer 2.Consumer 3.Exit \n");
        
   
    while(1){
         printf("\nEnter your Choice: ");
         scanf("%d",&ch);

        switch(ch){
            case 1:
            producer();
            break;
            case 2:
            consumer();
            break;
            case 3:
            printf("\nExiting...");
            exit(0);
            default:
            printf("invalid reply");
        }

    }
}

