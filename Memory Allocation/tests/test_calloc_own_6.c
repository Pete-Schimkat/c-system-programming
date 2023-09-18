#include <stdio.h>
#include "calloc_helpers.h"

#define MEM_SIZE ((sizeof(mem_block)+8)*3)
MEMORY(MEM_SIZE, mem);

const char * str_a = "AAAAAAA";
const char * str_b = "BBB";
const char * str_c = "CCCCCCC";

int blocks(unsigned int expected) {
	unsigned int final_block_count = mem_block_count(mem);
	// printf("\nblock count: \t%d\n", final_block_count);
	// printf("Expected: \t%d\n", expected);

	if(final_block_count != expected) {
		fprintf(stderr, "Did not match!\n");
		return 1;
	}
	return 0;
}

int size_start_end(size_t total_size_start) {
	if(mem_size_total(mem)==total_size_start) return 0;
	return 1;
}

int main() {

	my_calloc_init(mem, MEM_SIZE);
	int check_sum = 0;
	size_t total_size_start = mem_size_total(mem);

	char * ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	char * ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);

	/***************
	 * ZWEI ALLOCS *
	 * *************/

	check_sum += blocks(3);
	my_free(ptr_b);
	my_free(ptr_a);
	check_sum += blocks(1);

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);

	check_sum += blocks(3);
	my_free(ptr_a);
	check_sum += blocks(3);
	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/***************
	 * DREI ALLOCS *
	 * *************/

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);

	char * ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_c);
	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_b);
	my_free(ptr_c);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_b);
	my_free(ptr_a);
	my_free(ptr_c);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_b);
	my_free(ptr_c);
	my_free(ptr_a);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_c);
	my_free(ptr_b);
	my_free(ptr_a);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_c);
	my_free(ptr_a);
	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/***************************
	 * VIER ALLOCS, EIN LASSEN *
	 * *************************/

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_b);
	check_sum += blocks(2);

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_c);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_b);
	my_free(ptr_a);
	check_sum += blocks(2);

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_c);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_c);
	check_sum += blocks(3);

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_c);
	check_sum += blocks(3);

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_b);
	my_free(ptr_a);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_c);
	my_free(ptr_a);
	check_sum += blocks(3);

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_b);
	my_free(ptr_a);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_c);
	my_free(ptr_a);
	check_sum += blocks(3);

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_c);
	my_free(ptr_b);
	check_sum += blocks(2);

	ptr_b = my_calloc(strlen(str_b)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_b);
	my_free(ptr_c);
	check_sum += blocks(2);

	ptr_b = my_calloc(strlen(str_b)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_c);
	my_free(ptr_b);
	check_sum += blocks(2);

	ptr_b = my_calloc(strlen(str_b)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_b);
	my_free(ptr_a);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_c);
	my_free(ptr_b);
	check_sum += blocks(2);

	ptr_b = my_calloc(strlen(str_b)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/***********
	 * POINTERS*
	 ***********/

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_a);
	my_free(ptr_b);
	check_sum += blocks(2);

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);

	my_free(ptr_a);
	my_free(ptr_c);
	check_sum += blocks(3);

	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/****************** NEU VON LEER *****************************************/

	ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += blocks(3);
	my_free(ptr_b);
	my_free(ptr_c);
	check_sum += blocks(2);

	ptr_b = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);
	check_sum += blocks(3);
	ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);
	check_sum += blocks(3);
	my_free(ptr_c);
	check_sum += blocks(3);
	my_free(ptr_a);
	check_sum += blocks(3);
	my_free(ptr_b);
	check_sum += blocks(1);

	check_sum += size_start_end(total_size_start);

	/******************* ENDE ************************************************/

	size_t total_size_end = mem_size_total(mem);

	printf("\nTotal memory at start: %zu\n", total_size_start);
	printf("Total memory at end  : %zu\n", total_size_end);

	if(total_size_start != total_size_end) {
		fprintf(stderr, "Did not match!\n");
		exit(1);
	}

	unsigned int final_block_count = mem_block_count(mem);
	printf("\nFinal block count: %d\n", final_block_count);
	printf("Expected         : 1\n");

	if(final_block_count != 1) {
		check_sum++;
		fprintf(stderr, "Did not match!\n");
	}

	if(!check_sum) {
		printf("\n================================\n");
		printf(  "ALLE TESTS IN ...own_6 BESTANDEN\n");
		printf(  "================================\n");
	} else {
		printf("MIND EIN FAIL\n");
	}
}