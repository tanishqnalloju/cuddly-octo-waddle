/*
As part of the tradition, Treasure Hunt is played in Hogwarts school of witchcraft and
wizardry by all the houses. By decoding all the hints, Gryffindor has reached the final
level, the rest were knocked out. Gryffindors have obtained the Treasure, to unlock
the treasure they must perform the following operations using UNIX system calls
(open, close, read, write):
a) Open and Read the file /etc/passwd, write all the contents of file to crypt.txt
(In pwd).
b) Close the file (/etc/passwd).
c) Using lseek go to the last line of crypt.txt.
d) Store the first 12 characters of last line to a file decrypt.txt
e) Display the contents of decrypt.txt
The contents of decrypt.txt is the key to unlock the treasure.
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
    char buf;
    int c;
    //Opening passwd file
    int  fd1 = open("/etc/passwd", O_RDONLY);
    // Creating crypt.txt
    int  fd2 = open("crypt.txt", O_CREAT | O_WRONLY |O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    //Copying all the contents of passswd to crypt.txt
    while(1){
   	 if(read(fd1,&buf,1)!=0)
   		 write(fd2,&buf,1);
   	 else
   		 break;
    }
    close(fd1);
    close(fd2);
    fd1 = open("crypt.txt",O_RDONLY);
    // creating decrypt.txt
    fd2 = open("decrypt.txt",O_CREAT | O_WRONLY |O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    //Going to the end of crypt.txt
    lseek(fd1,-2,SEEK_END);
    read(fd1,&buf,1);
    printf("%c",buf);
    while(buf != '\n'){
   	 lseek(fd1,-2,SEEK_CUR);
   	 read(fd1,&buf,1);
    }
    //saving the 12 characters to decrypt.txt
    char s[12];
    read(fd1,s,12);
    write(fd2,s,12);
    close(fd1);
    close(fd2);
    fd1 = open("decrypt.txt", O_RDONLY);
    while(1){
   	 if(read(fd1,&buf,1)!=0)
   		 write(1,&buf,1);
   	 else
   		 break;
    }
    return 0;
}