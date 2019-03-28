#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdio.h>
#include<stdlib.h>

int main( int argc,char *argv[] )
{
    char buf;
    int sourcefile,destfile,n;
    if(argc!=3)
    {
        write(STDOUT_FILENO,"Invalid arguments \nprogram <sourcefile> <destination file>\n",58);   
        exit(1);
    }
    else
    {
         sourcefile=open(argv[1],O_RDONLY);
         if(sourcefile==-1)
         {
            perror("SOURCE FILE ERROR");
            exit(1);
         }
         else
         {
            destfile=open(argv[2],O_WRONLY | O_CREAT , 0641);
            if(destfile==-1)
            {
                perror("DESTINATION FILE ERROR");
                exit(1);
            }
            else
            {
                n=read(sourcefile,&buf,1);
                while(n != 0 && n != -1 )
                {
                    write( destfile, &buf, 1 );
        n=read(sourcefile,&buf,1);
                }
                write(STDOUT_FILENO, "FILES COPIED\n" , 15);    
                close(sourcefile);
                close(destfile);
            }
        }
    }
    return 0;
}