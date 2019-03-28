 /*
Write a program using system calls to print the content of the file (/etc/passwd) onto the
console.
 */
#include <fcntl.h>  
#include <unistd.h>                 /* For STDOUT_FILENO */
#include <stdio.h>   
#include <stdlib.h>
  
int main(int argc, char **argv) {
    int size, fd;
    char buf;                                /* Single-character buffer */
    if ((fd = open(argv[1], O_RDONLY)) == -1){ 
        perror("open");
        exit(2);
    }

    while ((read(fd, &buf, 1) >0)) { /* and then back by two bytes */ 
       if (write(STDOUT_FILENO, &buf, 1) != 1){
          perror("write");
          exit(1);
       }
    }              
    close(fd);                 /* Can have error here too */
    exit(0);                   /* exit doesn't return - hence no error */
}
