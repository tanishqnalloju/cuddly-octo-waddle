#include <stdlib.h>
#include <unistd.h> 
int main(void) { 
	int n, fd[2];
	 char buf[100];
	      pipe(fd);
	       if (fork())
	        { close(fd[1]);
	         n = read(fd[0], buf, 14);
	           write(STDOUT_FILENO, buf, n);
	            } else{
	                  close(fd[0]); write(fd[1],"Hello World \n ", 50);
	                    }
	                     } 