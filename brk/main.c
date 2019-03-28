#define MAX_ALLOCS 1000000 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
int main(int argc, char *argv[]) 
{ 
char *ptr[MAX_ALLOCS]; 
int freeStep, freeMin, freeMax, blockSize, numAllocs, j; 
printf("\n"); 
if (argc < 3 || strcmp(argv[1], "--help") == 0) 
{ printf("%s num-allocs block-size [step [min [max]]]\n", argv[0]); 
exit(5); } 
numAllocs = strtol(argv[1], NULL, 10); 
if (numAllocs > MAX_ALLOCS) 
{ printf("num-allocs > %d\n", MAX_ALLOCS); 
exit(5); } 
blockSize = strtol(argv[2], NULL, 10); 
freeStep = (argc > 3) ? strtol(argv[3], NULL, 10): 1; 
freeMin = (argc > 4) ? strtol(argv[4], NULL, 10) : 1; 
freeMax = (argc > 5) ? strtol(argv[5], NULL, 10) : numAllocs; 
if (freeMax > numAllocs) 
{ printf("free-max > num-allocs\n"); 
exit(5); } 
printf("Initial program break: %10p\n", sbrk(0)); 
printf("Allocating %d*%d bytes\n", numAllocs, blockSize); 
for (j = 0; j < numAllocs; j++) { 
ptr[j] = malloc(blockSize); 
if (ptr[j] == NULL) 
{ perror("malloc"); 
exit(5); } 
} 
printf("Program break is now: %10p\n", sbrk(0)); 
printf("Freeing blocks from %d to %d in steps of %d\n", 
freeMin, freeMax, freeStep); 
for (j = freeMin - 1; j < freeMax; j += freeStep) 
free(ptr[j]); 
printf("After free(), program break is: %10p\n", sbrk(0)); 
exit(10); 
}  