
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Block
{
	int block_size; //#of bytes in the data
	struct Block *next_block; //in C, you have to use "struct Block" as the type
	void *data; //a pointer to where the data starts
	
}Block;

const int overhead = 8+sizeof(void*);

struct Block *free_head;
void my_initialize_heap(int size);
void* my_alloc(int size);
void my_free(void *data);

int main(){
	const int HEAP_SIZE = 10000;
	my_initialize_heap(HEAP_SIZE);


/*	printf("TEST 1\n");

	int *first = my_alloc(sizeof(int));
    printf("%p\n",first);
    my_free(first);
    int *second = my_alloc(sizeof(int));
    printf("%p\n",second);
    my_free(second);*/

/*  printf("TEST 2\n");
  
    int* one = my_alloc(sizeof(int));
    printf("%d\n", one);
    int* two = my_alloc(sizeof(int));
    printf("%d\n",two );
    printf("Address 2 - 1 = %d - %d = %d \n",two, one,
	(two - one)*sizeof(int));
    printf("%lu\n",(8+8+sizeof(void*)) );*/

    printf("TEST 3\n");
    my_initialize_heap(50);
    int *uno = my_alloc(sizeof(int));
    printf("%p\t\n",uno);
    int *dos = my_alloc(sizeof(int));
    printf("%p\t\n",dos);
    int *tres = my_alloc(sizeof(int));
    printf("%p\t\n",tres);

    /*my_free(dos);
    double *d_tres = (double*)my_alloc(sizeof(double));
    printf("%p\t\n",d_tres);

    int *tres_new = (int*)my_alloc(sizeof(int));
    printf("%p\t\n", d_tres);
*/

    /*printf("TEST 4\n");
    my_initialize_heap(50);
    char *word = (char*)my_alloc(sizeof(char));
    printf("%p\t\n",word);
    int *numero = (int*)my_alloc(sizeof(int));
    printf("%p\n",numero);*/



	return 0;
}

void my_initialize_heap(int size){
	free_head = malloc(size);
    free_head->block_size = size;
    free_head->next_block = NULL;
}
void* newBlock(Block* block, int size){
	Block *new_open = (Block*)(((unsigned char*)block) +size);
    int new_size = block->block_size -size;
    new_open->block_size = new_size;
    new_open->next_block = block->next_block;
	new_open->data = (Block*)(((unsigned char*)new_open)+overhead);
    return new_open;
}

void* my_alloc(int size){
   int leftOver = size%sizeof(void*);
   size +=leftOver;
   Block* open_block = free_head;
   Block* previous_block = NULL;
   int req_size = size+overhead;
   while(open_block){
       if(size <= open_block->block_size){
	    //split and add head
	        if(req_size<=free_head->block_size){
		       //free_head->block_size = size;
		        free_head = newBlock(free_head,req_size);
		        return &open_block->data;
        //split and not add head
	       }else if(req_size<=open_block->block_size){
		        previous_block->next_block = newBlock(open_block,req_size);;
		        open_block->next_block = NULL;
		        open_block->block_size = size;
		        return &open_block->data;

        //not split and add head
	       }else if(req_size>free_head->block_size){
                 free_head = free_head->next_block;
                 open_block->next_block = NULL;
                 return &open_block->data;
        //not split and add head
	       }else{
	       	   previous_block = open_block;
                return &previous_block->data;
	      }
	

       }else{
	   previous_block = open_block;
	   open_block = open_block->next_block;
}


}
return 0;

}

void my_free(void *data){
	
	struct Block *clear_space = free_head;
	free_head = (Block*)(((unsigned char*)data) - overhead);
	free_head->next_block = clear_space;

}


