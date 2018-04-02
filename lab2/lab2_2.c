#include<stddef.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define SHMKEY 75
#define SIZE 512
//#define RAW 0
//shm attribution
struct  SHM{
  int written;
  char text[SIZE];
};

void processA()
{
  struct SHM* shm;
  int shmID;
  void* shmAddr=NULL;
  //NO1:generate shared memory
  shmID=shmget(SHMKEY,SIZE,IPC_CREAT|0666);
  //check1
  if (shmID==-1)
    printf("ProcessA:fun shmget run unseccesfully---shmID:-1\n");
  //NO2:connect shm with shared_memory
  shmAddr=shmat(shmID,NULL,0);
  shm=(struct SHM*)shmAddr;
  shm->written=0;//0:only write not0:only read
  //receive message
  while(1)
  {
    if(shm->written==0)
    {
      printf("processB-->processA:%s",shm->text);
      sleep(1);
      
      shm->written=1;
      
      if(strncmp(shm->text,"end",3)==0)
      {
        //end reading process
        break;
      }
    }
    else
    {
      sleep(1);
    }
  }
  //seperate processA with share_memory
  if (shmdt(shmAddr)==-1)
    printf("processA:seperate fails\n");
  //delete share_memory
  if (shmctl(shmID,IPC_RMID,0)==-1)
    printf("processA:delete fails\n");
}
void processB()
{
  struct SHM* shm;
  int shmID;
  void* shmAddr;
  char buffer [SIZE];
  //NO1:get shmID
  shmID=shmget(SHMKEY,SIZE,IPC_CREAT|0666);
  //check1
  if (shmID==-1)
    printf("ProcessA:fun shmget run unseccesfully---shmID:-1\n");
  //NO2:connect shm with shared_memory
  shmAddr=shmat(shmID,NULL,0);
  shm=(struct SHM*)shmAddr;
  //write message
  while(1)
  {
    if(shm->written==1)
    {
      printf("processB writes:");
      fgets(buffer,SIZE,stdin);
      strncpy(shm->text,buffer,SIZE);      

      sleep(1);
      
      shm->written=0;
      
      if(strncmp(shm->text,"end",3)==0)
      {
        //end reading process
        break;
      }
    }
    else
    {
      sleep(1);
    }
  }
  //seperate processB with share_memory
  if (shmdt(shmAddr)==-1)
    printf("processA:seperate fails\n");
  //wait PROCESSA delete share_memory
  sleep(2);
}
int main()
{
  pid_t pid;
  while((pid=fork())==-1);//loop untill fork succefully
  if(pid==0)
  {
    processA();
  }
  else
  {
    processB();
  }
}
