#include <stdio.h>

#include "calloc_helpers.h"

#define MEM_SIZE ((sizeof(mem_block)+8)*4)
MEMORY(MEM_SIZE, mem);

const char * str_a = "AAAAAAA";
const char * str_b = "BBB";
const char * str_c = "CCCCCCC";
const char * str_d = "DDDDDD";

const char * expected1 = "AAAAAAABBBCCCCCCC";
const char * expected2 = "AAAAAAACCCCCCC";
const char * expected3 = "AAAAAAACCCCCCCAAAAAAA";
const char * expected4 = "AAAAAAACCCCCCCCCCCCCCAAAAAAA";
const char * expected5 = "AAAAAAABBBCCCCCCC";

int check(const char * expected) {
	char * result = mem_concat_data(mem);

	if(strcmp(expected, result) != 0) {
		fprintf(stderr, "Did not match!:\n");
	}

	printf("\nExpected: %s\n", expected);
	printf("Found   : %s\n", result);

	free(result);
	return 0;
}

int test_no_space(int size) {
	char *ptr_null = my_calloc(size, sizeof(char), 0);
	if(ptr_null == NULL) {
		printf("\nNULL as expected\n");
	} else {
		printf("\nno memory left, should be NULL, found: %p\n", ptr_null);
		return 1;
	}
	return 0;
}

int blocks(unsigned int expected) {
	unsigned int final_block_count = mem_block_count(mem);
	printf("\nblock count: \t%d\n", final_block_count);
	printf("Expected: \t%d\n", expected);

	if(final_block_count != expected) {
		fprintf(stderr, "Did not match!\n");
		return 1;
	}
	return 0;
}

int main() {

	my_calloc_init(mem, MEM_SIZE);
	int check_sum = 0;
	size_t total_size_start = mem_size_total(mem);

	char* ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);

	char* ptr_b = my_calloc(strlen(str_b)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);

	char* ptr_c = my_calloc(strlen(str_c)+1,  sizeof(char), 0);
	strcpy(ptr_c, str_c);

	check_sum += check(expected1);

	my_free(ptr_b);
	
	check_sum += check(expected2);

	char* ptr_a2 = my_calloc(strlen(str_a)+1, sizeof(char), 0); 
	strcpy(ptr_a2, str_a);

	check_sum += check(expected3);

	
	char *ptr_c2 = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c2, str_c);

	check_sum += check(expected4);

	check_sum += test_no_space(strlen(str_b)+1);
	check_sum += test_no_space(0);

	my_free(ptr_c2);
	my_free(ptr_a2);

	char *ptr_b2 = my_calloc(strlen(str_b)+1, sizeof(char), 0);
	strcpy(ptr_b2, str_b);

	check_sum += check(expected5);

	my_free(ptr_a);

	char* ptr_a3 = my_calloc(strlen(str_a)+1,  sizeof(char), 0);
	strcpy(ptr_a3, str_a);

	check_sum += check("BBBCCCCCCCAAAAAAA");

	char * ptr_b3 = my_calloc(strlen(str_b)+1,  sizeof(char), 0);
	strcpy(ptr_b3, str_b);

	check_sum += check("BBBBBBCCCCCCCAAAAAAA");

	check_sum += test_no_space(0);

	my_free(ptr_b3);
	char * ptr_d1 = my_calloc(strlen(str_d)+1, sizeof(char), 0);
	strcpy(ptr_d1, str_d);

	my_free(ptr_b2);
	my_free(ptr_d1);

	ptr_d1 = my_calloc(strlen(str_d)+1, sizeof(char), 0);
	strcpy(ptr_d1, str_d);

	char * ptr_a4 = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a4, str_a);

	check_sum += check("DDDDDDAAAAAAACCCCCCCAAAAAAA");

	my_free(ptr_a4);
	my_free(ptr_c);

	char * ptr_b4 = my_calloc(strlen(str_b)+1, sizeof(char), 0);
	strcpy(ptr_b4, str_b);

	char * ptr_d2 = my_calloc(strlen(str_d)+1, sizeof(char), 0);
	strcpy(ptr_d2, str_d);

	//     d1       d2
	check_sum += check("DDDDDDBBBDDDDDDAAAAAAA");

	check_sum += test_no_space(strlen(str_b)+1);

	my_free(ptr_b4);
	my_free(ptr_a3);
	my_free(ptr_d1);

	char * ptr_b5 = my_calloc(strlen(str_b)+1, sizeof(char), 0);
	strcpy(ptr_b5, str_b);

	char * ptr_a5 = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a5, str_a);

	char * ptr_c3 = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c3, str_c);

	check_sum += check("AAAAAAACCCCCCCDDDDDDBBB");

	check_sum += blocks(4);

	my_free(ptr_c3);
	//check_sum += blocks(4);
	my_free(ptr_b5);
	//check_sum += blocks(4);
	my_free(ptr_d2);
	blocks(2);
	check("AAAAAAA");
	my_free(ptr_a5);

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
		fprintf(stderr, "Did not match!\n");
		exit(1);
	}
	if(!check_sum){
	 	printf("\n====================\n");
		printf("\nALLE TESTS BESTANDEN\n");
		printf("\n====================\n");
	}
}