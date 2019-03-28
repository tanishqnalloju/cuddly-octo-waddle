#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
 
int main(int argc, char **argv) {
    int fd1, fd2, rv, exit_status;
    if (fork() == 0) {          	/* Child */
   	 if ((fd1 = open(argv[1], O_RDONLY)) == -1)
   	 {
    			 perror("Error in opening file for reading\n");
   		 exit(1);
   	 }
   	 if ((fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
   	 {
   		 perror("Error in opening file for writing\n");
   		 exit(1);
   	 }
   	 dup2(fd1,0);
   	 dup2(fd2,1);
   	 execvp(argv[3], &argv[3]);   /* Uses PATH */
 			 perror("exec error");
   	 exit(2);
    }
    else {                    	/* Parent */
   	 wait(&rv);
   	 printf("Exit status: %d\n", WEXITSTATUS(rv));
 			 exit(0);
   }
}
