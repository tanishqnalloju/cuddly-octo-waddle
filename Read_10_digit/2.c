/*
Write a C program that reads line by line in myfile.txt and prints the first 10-digit
number in the given file (digits should be continuous), If not found then print first 10
characters excluding numbers.
*/

#include <stdio.h>

int main()
{
	//Reading the file
	FILE *fp = fopen("myfile.txt" , "r");
	int count;
	int c=0;
	while(1)
	{    
    		count = 0;
    		for(int i=0;i<10;i++){
        			c = getc(fp);
        		if( c == -1)
            		break;
        		if(c>='0' && c<='9')
            		count++;
    		}
    		if(c == -1)
        			break;
    		if(count==10){
        			char s[10];
        			fseek(fp,-10,SEEK_CUR);
        			fgets(s,11,fp);
        			printf("%s",s);
        			break;
    		}
    		fseek(fp,-9,SEEK_CUR);
	}
	if (count!=10)
	{
    		rewind(fp);
    		for(int i=0;i<10;)
    		{
        			c = getc(fp);
        			if(c>='0' && c<='9')
            			continue;
        			printf("%c",c);
        			i++;
    		}
	}
    return 0;
}