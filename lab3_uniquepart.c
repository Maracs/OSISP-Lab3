#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h> 

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
 
int walk(const char* dirname,int maxProc,char* find);        
 
 
int main(int argc, char* argv[])
{
    if(argc < 4)
    {
    fprintf(stderr, "Not enougth parametrs\n" );
    exit(1);
    }
    
    
  
  
    exit(walk(argv[1],atoi(argv[2]),argv[3]));
}
 







int numProc=0;
char buf[PATH_MAX];
 
int walk(const char* dirname,int maxProc,char* find)
{


    pid_t p;
    


    DIR* dp;
    struct stat st;
    struct dirent* dirp;
    int retval = 0;
 
    size_t len = strlen(dirname);
 
    if((dp = opendir(dirname)) == NULL)
    {
    perror(dirname);
    return 1;
    }
 
    strncpy(buf, dirname, len);
 
    while((dirp = readdir(dp)) != NULL)
    {
    if(strcmp(dirp->d_name, ".") == 0 ||
       strcmp(dirp->d_name, "..") == 0)
        continue;
 
    buf[len] = '/';
    buf[len+1] = '\0';
 
    strcat(buf, dirp->d_name);
    
    if(lstat(buf, &st) == -1)
    {
        perror(dirp->d_name);
        retval = 1;
        break;
    }
 
    if(S_ISDIR(st.st_mode))
    {
        if(walk(buf,maxProc,find) == 1)
        {
        retval = 1;
        break;
        }
        
    }
    
    else{ 
    		if(numProc<=maxProc){
    			numProc++;
    			p=fork();
    			}
    		else
    		{
    			int status;
    			
    			wait(&status);
    			
    			p=fork();	
    		}
    		
    		if(p==0){
    		   int Equals=0;
    		   char temp[BUFSIZ];
    		   
    		   FILE *input=NULL;
    		   input=fopen(buf,"rb");
    		   
    		   if(input == NULL){
    		   	retval=1;
    		   	printf("\n\n1\n\n");
    		   }
    		   int i=0;
    		   while(!feof(input))
    		   {
    		   	   fseek(input,i,SEEK_SET);
    		   	   fread(temp,sizeof(char),strlen(find),input);
	    		   
	    		   
	    		   if(strcmp(find,temp)==0)
	    		   	Equals++;
	    		   i++;
	    		   	
	    		   
    		   }
    	
    		   printf("%s%d  %s%d  %s%s  %s%lu\n",
    		   "Found sequensis in file:",Equals,
    		   "Pid:",getpid(),
		   "Full path:",buf,
		   "Size:",st.st_size);
		   
		   exit(retval);
    		}
    		else
    		{
	    		 if(p<0)
	    		 {
	    			return 1;
	    		 }
    		}
    		
    		 
 	     }
    buf[len] = '\0';
    }
 
    closedir(dp);
    return retval;
}
