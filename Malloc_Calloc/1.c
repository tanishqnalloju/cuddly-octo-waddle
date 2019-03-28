/* implement malloc(), calloc(), realloc() and free()	- memalloc.c	*/
#include <unistd.h>
#include <string.h>
#include <pthread.h>
/* Only for the debug printf */
#include <stdio.h>

struct header_t {
	size_t size;
	unsigned is_free;
	struct header_t *next;
};

struct header_t *head = NULL, *tail = NULL;
pthread_mutex_t global_malloc_lock;

struct header_t *get_free_block(size_t size)
{
	struct header_t *curr = head;
	while(curr) {
		/* see if there's a free block that can accomodate requested size */
		if (curr->is_free && curr->size >= size)
			return curr;
		curr = curr->next;
	}
	return NULL;
}

void free(void *block)
{
	struct header_t *header, *tmp;
	/* program break is the end of the process's data segment */
	void *programbreak;

	if (!block)
		return;
	pthread_mutex_lock(&global_malloc_lock);
	header = (struct header_t*)block - 1;
	/* sbrk(0) gives the current program break address */
	programbreak = sbrk(0);

	/*
	   Check if the block to be freed is the last one in the
	   linked list. If it is, then we could shrink the size of the
	   heap and release memory to OS. Else, we will keep the block
	   but mark it as free.
	 */
	if ((char*)block + header->size == programbreak) {
		if (head == tail) {
			head = tail = NULL;
		} else {
			tmp = head;
			while (tmp) {
				if(tmp->next == tail) {
					tmp->next = NULL;
					tail = tmp;
				}
				tmp = tmp->next;
			}
		}
		/*
		   sbrk() with a negative argument decrements the program break.
		   So memory is released by the program to OS.
		*/
		sbrk(0 - header->size - sizeof(struct header_t));
		/* Note: This lock does not really assure thread
		   safety, because sbrk() itself is not really
		   thread safe. Suppose there occurs a foregin sbrk(N)
		   after we find the program break and before we decrement
		   it, then we end up realeasing the memory obtained by
		   the foreign sbrk().
		*/
		pthread_mutex_unlock(&global_malloc_lock);
		return;
	}
	header->is_free = 1;
	pthread_mutex_unlock(&global_malloc_lock);
}

void *malloc(size_t size)
{
	size_t total_size;
	void *block;
	struct header_t *header;
	if (!size)
		return NULL;
	pthread_mutex_lock(&global_malloc_lock);
	header = get_free_block(size);
	if (header) {
		/* Woah, found a free block to accomodate requested memory. */
		header->is_free = 0;
		pthread_mutex_unlock(&global_malloc_lock);
		return (void*)(header + 1);
	}
	/* We need to get memory to fit in the requested block and header from OS. */
	total_size = sizeof(struct header_t) + size;
	block = sbrk(total_size);
	if (block == (void*) -1) {
		pthread_mutex_unlock(&global_malloc_lock);
		return NULL;
	}
	header = block;
	header->size = size;
	header->is_free = 0;
	header->next = NULL;
	if (!head)
		head = header;
	if (tail)
		tail->next = header;
	tail = header;
	pthread_mutex_unlock(&global_malloc_lock);
	return (void*)(header + 1);
}

void *calloc(size_t num, size_t nsize)
{
	size_t size;
	void *block;
	if (!num || !nsize)
		return NULL;
	size = num * nsize;
	/* check mul overflow */
	if (nsize != size / num)
		return NULL;
	block = malloc(size);
	if (!block)
		return NULL;
	memset(block, 0, size);
	return block;
}

void *realloc(void *block, size_t size)
{
	struct header_t *header;
	void *ret;
	if (!block || !size)
		return malloc(size);
	header = (struct header_t*)block - 1;
	if (header->size >= size)
		return block;
	ret = malloc(size);
	if (ret) {
		/* Relocate contents to the new bigger block */
		memcpy(ret, block, header->size);
		/* Free the old memory block */
		free(block);
	}
	return ret;
}

/* A debug function to print the entire link list */
void print_mem_list()
{
	struct header_t *curr = head;
	printf("head = %p, tail = %p \n", (void*)head, (void*)tail);
	while(curr) {
		printf("addr = %p, size = %zu, is_free=%u, next=%p\n",
			(void*)curr, curr->size, curr->is_free, (void*)curr->next);
		curr = curr->next;
	}
}
/*
Compile and Run
vishnu@mannava:~$ gcc -o memalloc.so -fPIC -shared memalloc.c

The -fPIC and -shared options makes sure the compiled output has position-independent code and tells the linker to produce a shared object suitable for dynamic linking.
On Linux, if you set the enivornment variable LD_PRELOAD to the path of a shared object, that file will be loaded before any other library. We could use this trick to load our compiled library file first, so that the later commands run in the shell will use our malloc(), free(), calloc() and realloc().

vishnu@mannava:~$ export LD_PRELOAD=$PWD/memalloc.so

Now, if you run something like ls, it will use our memory allocator.

ls
memalloc.c      memalloc.so

You can also run your own programs with this memory allocator.
*/
/*
vishnu@mannava:~$ cc sll.c
sll.c: In function deletenode:
sll.c:10:6: internal compiler error: Segmentation fault
 void deletenode(node * head, int num) {
      ^
Please submit a full bug report,
with preprocessed source if appropriate.
See <file:///usr/share/doc/gcc-5/README.Bugs> for instructions.
*/
After restarting the linux
/*
vishnu@mannava:~$ cc sll.c
vishnu@mannava:~$./a.out
insert 5 more elements in to Linked List - Already element 0 is in SLL
Display elements in Linked List
5 4 3 2 1 0
Display elements in Linked List after deleting 2
5 4 3 1 0
*/
/* Program for implementation of single Linked List with out functions */
#include <stdio.h>
#include <stdlib.h>
struct node
{
int data ;
struct node * next ;
} ;
typedef struct node node;
void deletenode(node * head, int num) {
node *temp;
if(head->data == num)
{
/* remove the node */
temp = head->next;
free(head);
head = temp;
}
else {
while(head->next->data != num)
head = head->next;
temp = head->next->next;
free(head->next);
head->next = temp;
}
}
void main( )
{
int i;
node *head, *tmp;
head = malloc(sizeof(node));
head->data = 0;
head->next = NULL;
printf ( "\n insert 5 more elements in to Linked List - Already element 0 is in SLL" ) ;
for(i=1; i < 6; i++) {
tmp = malloc(sizeof(node));
if(tmp == NULL)
{
printf("malloc failed");
}
tmp->data = i;
tmp->next = head;
head = tmp;
}
printf ( "\n Display elements in Linked List\n" ) ;
tmp = head; // start at the 1st node
while(tmp != NULL) {
printf(" %d ", tmp->data);
tmp = tmp->next; // make tmp point to next node
}
deletenode(head,2);
printf ( "\n Display elements in Linked List after deleting 2\n" ) ;
tmp = head; // start at the 1st node
while(tmp != NULL) {
printf(" %d ", tmp->data);
tmp = tmp->next; // make tmp point to next node
}
}


