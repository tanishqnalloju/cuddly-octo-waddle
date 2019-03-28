/*
3. Write a C program that saves 10 random numbers to a file, using own “rand.h” header
file which contains your own random( ) function.
*/

#include <stdio.h>
#include <time.h>
#include "rand.h"
int main()
{
	srand(time(0));
    FILE *fptr;
    fptr = fopen("random.txt","w");
    for (int i = 0; i < 10; ++i)
    {
        fprintf(fptr, "%d", ownrand()%10);
            fprintf(fptr, "\n");
    }
	return 0;
}
