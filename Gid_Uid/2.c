/*
The process obtains its own PID and its parent’s PID using the getpid and getppid system
calls. The program also prints the effective UID and GID, which normally are equal to the
real UID and GID. Write a UNIX system program that prints PID, PPID, real and effective
UIDs and GIDs and fetches and sets PATH
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
        pid_t p;
        printf("This process is %d\n",getpid());
        printf("This real user ID  is %d\n",getuid());
        printf("This effective user ID is %d\n",geteuid());
        printf("Real group ID: %d\n",getgid());
        printf("Effective group ID: %d\n",getegid());
        if(fork()==0){
        printf("This process is %d\n",getpid());
        printf("This real user ID  is %d\n",getuid());
        printf("This effective user ID is %d\n",geteuid());
        printf("Real group ID: %d\n",getgid());
        printf("Effective group ID: %d\n",getegid());

        printf("PATH : %s\n",getenv("PATH"));
        char *s=strdup(getenv("PATH"));
        setenv("PATH","sumanth",1);
        printf("PATH : %s\n",getenv("PATH"));
        setenv("PATH",s,1);
        printf("PATH : %s\n",getenv("PATH"));

        }
}