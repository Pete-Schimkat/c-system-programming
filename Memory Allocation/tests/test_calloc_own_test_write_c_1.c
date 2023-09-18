#include <stdio.h>

#include "calloc_helpers.h"

#define MEM_SIZE (512)
MEMORY(MEM_SIZE, mem);

int test_1() {
	char * ptr_a = my_calloc(8, sizeof(char), 0);
	for(int i = 0; i < 8; i++) {
		if(ptr_a[i] != 0) {
			printf("\ntest_1 failed\n");
			return 1;
		}
	}
	printf("\ntest_1 OK\n");
	my_free(ptr_a);
	return 0;
}

int test_2() {
	char * ptr_a = my_calloc(7, sizeof(int), 1);
	for(int i = 0; i < (int) (7*sizeof(int)); i++) {
		if(ptr_a[i] != 1) {
			printf("\ntest_2 failed\n");
			return 1;
		}
	}
	printf("\ntest_2 OK\n");
	my_free(ptr_a);
	return 0;
}

int last_check(size_t total_size_start) {
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
		return 1;
	}
	return 0;
}

int main() {

	my_calloc_init(mem, MEM_SIZE);
	size_t total_size_start = mem_size_total(mem);

	int check_sum = 0;
	check_sum += test_1();
	check_sum += last_check(total_size_start);
	check_sum += test_2();
	check_sum += last_check(total_size_start);

	exit(check_sum);
}
