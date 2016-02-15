#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Block
{
	int block_size; //#of bytes in the data
	struct Block *next_block; //in C, you have to use "struct Block" as the type
	void *data; //a pointer to where the data starts
	
}Block;

const int overhead = sizeof(int)+sizeof(void*);//Added 8 instead of sizeof(int) to avoid segmentation fault

struct Block *free_head;
void my_initialize_heap(int size);
void* my_alloc(int size);
void my_free(void *data);
void standard_deviation();

int main(){

	my_initialize_heap(5000);


	/*printf("TEST 1\n");
	int *first =(int*) my_alloc(sizeof(int));
    printf("%p\n",first);
    my_free(first);
    int *second =(int*) my_alloc(sizeof(int));
    printf("%p\n",second);
    my_free(second);*/

    /*printf("TEST 2\n");
    int* one = (int*)my_alloc(sizeof(int));
    printf("%d\n", one);
    int* two = (int*)my_alloc(sizeof(int));
    printf("%d\n",two );*/

	/*
    printf("TEST 3\n");
    my_initialize_heap(50);
    int *uno =(int*) my_alloc(sizeof(int));
    printf("%p\t\n",uno);
    int *dos = (int*)my_alloc(sizeof(int));
    printf("%p\t\n",dos);
    int *tres = (int*)my_alloc(sizeof(int));
    printf("%p\t\n",tres);
    my_free(dos);

    double *d_tres = (double*)my_alloc(sizeof(double));
	printf("\nNew Allocation\n");
    printf("%p\t\n",d_tres);

    int *tres_new = (int*)my_alloc(sizeof(int));
    printf("%p\t\n", tres_new);*/

    /*printf("TEST 4\n");
    my_initialize_heap(50);
    char *word = (char*)my_alloc(sizeof(unsigned char*));
    printf("%p\t\n",word);
    int *numero = (int*)my_alloc(sizeof(int));
    printf("%p\n",numero*/


	/*printf("TEST 5\n");
	int* array = (int*)my_alloc((100 * sizeof(int)));
	int* int_val = (int*)my_alloc(sizeof(int));
	
	printf("array: %p\t",array);
	printf("int value: %p\t\n",int_val);
	my_free(array);
	printf("Array has been freed\n");
	printf("array: %p\t",array);
	printf("int value: %p\t\n",int_val);*/

	//standard_deviation();

	return 0;
}

void my_initialize_heap(int size){
	free_head =(struct Block*) malloc(size);
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
		   printf("Head Block Size:%i\n",free_head->block_size);
	        if(req_size<=free_head->block_size){
		       //free_head->block_size = size;
		        free_head = (Block*)newBlock(free_head,req_size);
		        return &open_block->data;
        //split and not add head
	       }else if(req_size<=open_block->block_size){
		        previous_block->next_block =(Block*) newBlock(open_block,req_size);
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
/*void standard_deviation(){
		printf("Eneter a positive number\n");
	int user_int;
	scanf_s("%d",&user_int);
	int *user_arr = (int*)my_alloc(user_int*sizeof(int));
	int number, sum = 0;
	double standard_dev = 0 ,mean = 0;
	for(int i = 0; i < user_int; i++){
		printf("Enter a number: \n");
		scanf_s("%d",&number);
		user_arr[i]=number;
	}
	for(int i = 0; i < user_int; i++){
		sum = sum+user_arr[i];
	}
	mean = sum/user_int;
	for(int i = 0; i < user_int; i++){
		standard_dev += pow(user_arr[i]-mean,2);
	}
	standard_dev = sqrt(standard_dev/user_int);
	printf("Standard Deviation: %f\n",standard_dev);
}*/
