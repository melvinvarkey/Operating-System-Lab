//----------------------------------------------------------
// Reader -writer problem
//----------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,writeblock;
int data = 0;
int rcount = 0;
char chdata[30]="Hello";

void *reader(void *arg)
{
      int f;
      f = ((int)arg);
      sem_wait(&mutex);
      rcount = rcount + 1;
      if(rcount==1)
       sem_wait(&writeblock);
      sem_post(&mutex);
      printf("Data read by the reader %d is : ",f);
       printf("%s\n",chdata);
      sleep(1);
      sem_wait(&mutex);
      rcount = rcount - 1;
      if(rcount==0)
       sem_post(&writeblock);
      sem_post(&mutex);
}

void *writer(void *arg)
{
      int f,i;
      f = ((int) arg);
      sem_wait(&writeblock);
      data++;
      printf("Data writen by the writer%d is \n",f+1);
       scanf("%s",chdata);
      sleep(1);
      sem_post(&writeblock);
}

main()
{
      int a=0,i,b; 
      pthread_t rtid[30],wtid[30];
      sem_init(&mutex,0,1);
      sem_init(&writeblock,0,1);
do
{
 for(i=0;i<=4;i++)
  {
    pthread_create(&rtid[i],NULL,reader,(void *)i);
  }
    pthread_create(&wtid[1],NULL,writer,(void *)data);
     pthread_join(wtid[1],NULL);
  for(i=0;i<=4;i++)
  {
    pthread_join(rtid[i],NULL);
  }
  a++;
}while(a!=5);
}
