#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>     
#include <stdio.h>    
#include <unistd.h>  
#include <stdlib.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
int fd;
if ((fd = creat("file.hole", 777)) < 0)
perror("creat error");
if (write(fd, buf1, 10) != 10)
perror("buf1 write error");
/* offset now = 10 */
if (lseek(fd, 16384, SEEK_SET) == -1)
perror("lseek error");
/* offset now = 16384 */
if (write(fd, buf2, 10) != 10)
perror("buf2 write error");
/* offset now = 16394 */
exit(0);
}

/*
$ ./a.out
#(check its size)
$ ls -l file.hole
-rw-r--r-- 1 sar 16394 Nov 25 01:01 file.hole

#(let’s look at the actual contents)
$ od -c file.hole 

Both files are the same size, the file without holes consumes 20 disk blocks,
whereas the file with holes consumes only 8 blocks
*/