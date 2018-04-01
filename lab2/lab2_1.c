#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#define MSGKEY 75 
struct msgbuf{
  long mytype;
  char* mytext;
};
void sender()
{
  //PREPARE TEH MESSAGE
  struct msgbuf Msg;
  Msg.mytype=1;
  Msg.mytext="I'm sender,I'm sending you mesagge...\n";
  //prepare sending message
  int msgid;
  while((msgid=msgget(MSGKEY,IPC_CREAT|0660))==-1);
  msgsnd(msgid,&Msg,1024,IPC_NOWAIT);
}
void receiver()
{
  struct msgbuf Msg;
  Msg.mytype=1;
  //prepare receive message
  int msgid;
  while((msgid=msgget(MSGKEY,IPC_CREAT|0660))==-1);
  int i;
  msgrcv(msgid,&Msg,1024,1,0);
  printf("I'm receiver.\nThis is the message i receive:\n%s",Msg.mytext);
}
int main()
{
  int pid;
  while((pid=fork())<0);
  if(pid==0)
  {
    sender();
  }
  else
  {
    int pid2;
    while((pid2=fork())<0);
    if(pid2==0)
      receiver();
  }
  return 0;
}
