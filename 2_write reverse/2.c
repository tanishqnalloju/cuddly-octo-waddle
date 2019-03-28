/*
Write a program using system calls to write in reverse order of all the contents of file
(/etc/passwd) to reverse.txt. Show a pictorial arrangement of File Descriptor, File and Inode
tables for a single process that has two different files open.
*/

#include <fcntl.h>  
#include <unistd.h>                 /* For STDOUT_FILENO */
#include <stdio.h>  
#include <stdlib.h>
  
int main(int argc, char **argv) {
    int size, fd;
    char buf;                                  
    int fd1 = open("reverse.txt",O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if ((fd = open(argv[1], O_RDONLY)) == -1){
        perror("open");
        exit(2);
    }
    lseek(fd, 1, SEEK_END);                /* Pointer taken to EOF + 1 first */

    while (lseek(fd, -2, SEEK_CUR) >= 0) { /* and then back by two bytes */ 
       if (read(fd, &buf, 1) != 1){ 
          perror("read");
          exit(1);
       }
       if (write(fd1, &buf, 1) != 1){
            perror("write");
          exit(1);
       }
    }              
    close(fd);                 /* Can have error here too */
    close(fd1);
    exit(0);                   /* exit doesn't return - hence no error */
}