#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include<wait.h>
#include <fcntl.h>

int main()
{
    char* pcomm[] = {"wc","-l","Mickey",NULL};
    char* ccomm[] = {"wc","-w","Mickey",NULL};
    switch(fork())
    {
   	 case -1:
   		 perror("fork");
   		 exit(1);
   	 case 0:
   		 //child
   		 if(execvp("wc",ccomm)<0)
   			 printf(" execvp error in child\n");
   			 exit(2);
   		 break;
   	 default:
   		 if(execvp("wc",pcomm)<0)
   			 printf(" execvp error in parent\n");
   			 exit(3);
   		 break;
    }
}
