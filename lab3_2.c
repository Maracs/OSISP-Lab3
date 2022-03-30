#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/time.h>
#include <time.h>


void getTime()
{

struct timeval time;
gettimeofday(&time,NULL);

struct tm *info;
info=localtime(&(time.tv_sec));


int millsecs=time.tv_usec/1000;
char buffer[64];

strftime(buffer,sizeof(buffer),"%H:%M:%S",info);
printf("%s:%d\n",buffer,millsecs); 



}



int main(int argc,char*argv[]){

pid_t p1;

p1=fork();

if(p1>0)
p1=fork();

if(p1==0)
{
	printf("This is child proc,pid=%d\n",getpid());
	printf("His parent proc,pid=%d\n",getppid());
	getTime();
	 	
 }
 else if(p1>0)
 {
 	printf("THis is parent proc,pid=%d\n",getpid());
 	getTime();
 	system("ps -x");
 	
 }

}
