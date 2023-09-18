#include <stdio.h>

#include "calloc_helpers.h"

// Simple first fit test
const char * str_a = "AA";
const char * str_b = "BB";
const char * str_c = "CC";
const char * expected = "AACC";

#define MEM_SIZE (256)
MEMORY(MEM_SIZE, mem);

/* Dieser Test mach zwei Allokationen, freed dann die zweite und wieder eine Allokation
 */

int main() {

	my_calloc_init(mem, MEM_SIZE);

	size_t total_size_start = mem_size_total(mem);

	//mem_print_blocks(mem);


	char * ptr_a = my_calloc(strlen(str_a)+1, sizeof(char), 0);
	strcpy(ptr_a, str_a);
	char * ptr_b = my_calloc(strlen(str_b)+1, sizeof(char), 0);
	strcpy(ptr_b, str_b);

	my_free(ptr_b);

	char * ptr_c = my_calloc(strlen(str_c)+1, sizeof(char), 0);
	strcpy(ptr_c, str_c);


	printf("Comparing order of memory\n");
	char * result = mem_concat_data(mem);

	printf("\nExpected: %s\n", expected);
	printf("Found   : %s\n", result);

	if(strcmp(expected, result) != 0) {
		fprintf(stderr, "Did not match!\n");
		exit(1);
	}

	printf("\nFreeing all allocations\n");

	my_free(ptr_c);
	// mem_print_blocks(mem);
	my_free(ptr_a);
	// mem_print_blocks(mem);

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

	free(result);
}
