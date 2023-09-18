#include "../include/calloc.h"
// Für memset
#include <string.h>

static void * MEM;
static size_t MEM_SIZE;
size_t round_size(size_t value);
void fill_memory(mem_block* memory_to_fill, int value);
mem_block* separate_blocks(mem_block* curr, size_t rounded_size, int c);
int check_if_occupied(mem_block* to_check);
void* combine_blocks(mem_block* prev, mem_block* next);

/* Die aktuelle Position für das Next Fit Verfahren */
static mem_block * last_allocation = NULL;

void my_calloc_init(void * mem, size_t mem_size){
	MEM = mem;
	MEM_SIZE = mem_size;

	/* Initial existiert genau ein mem_block direkt am Anfang des Speichers */
	mem_block * beginning = MEM;

	beginning->next = NULL;
	beginning->prev = NULL;

	/* Der verwaltete Speicher des initialen mem_blocks ist die des
	 * gesamten Speichers minus die Größe seiner eigenen Verwaltungsstruktur
	 * Da sowohl MEM_SIZE ein Vielfaches von 8 ist und sizeof(mem_block) auch
	 * mindestens ein vielfaches von 8 oder mehr ist, ist das LSB
	 * auch direkt 0 -> free.
	 */
	beginning->size = MEM_SIZE - sizeof(mem_block);

	/* Pointer for next-fit */
	last_allocation = beginning;
}


size_t round_size(size_t value) {
	if(value == 0){
		return 0; 
	}
	if(value%8 == 0){
		return value;
	}
	value = value / 8; 
	value++;
	value = value * 8; 
	return value; 
}

void * my_calloc(size_t nmemb, size_t size, int c) {
	if(nmemb == 0 ||size ==0) {
		return NULL;
	}
	int rewind_flag = 0; 
	
	mem_block* curr;
	size_t rounded_size = round_size(size*nmemb); 
		curr = last_allocation;
		while(curr!=NULL){
			if(curr->size >= rounded_size&& (curr->size & 1) == 0 ){
				size_t curr_size_diff = curr->size - rounded_size;
				size_t minimum_size = sizeof(mem_block) + 8; 

				if(curr->size==rounded_size){ //passt exakt
					curr->size |= 1; //setzt letztes bit von size (auf 1) -> belegt
					fill_memory(curr, c);
					last_allocation = curr;
					return ((mem_block*)((int)curr+sizeof(mem_block))); 
				} else if(curr_size_diff<minimum_size) { //restblock nicht groß genug
					curr->size |= 1; //setzt letztes bit von size (auf 1) -> belegt
					fill_memory(curr, c);
					last_allocation = curr;
					return ((mem_block*)((int)curr+sizeof(mem_block))); 
				} else if(curr->size>rounded_size){ //DEUTLICH größer!
					mem_block* old = separate_blocks(curr, rounded_size, c);
					last_allocation = old; 
					return ((mem_block*)((int)old+sizeof(mem_block))); 
				} 

			}
			if(curr->next==NULL){
				if(rewind_flag==1){
					return NULL;
				}
					rewind_flag=1;
					while(curr->prev != NULL){
						curr=curr->prev;			
				}
			} else {
				curr=curr->next;
			}
	}
	return NULL;
}
void fill_memory(mem_block* memory_to_fill, int value){
	size_t size = memory_to_fill->size;
	memset((mem_block*)((int)memory_to_fill  + sizeof(mem_block)), value&255 , size);
}


mem_block* separate_blocks(mem_block* curr, size_t rounded_size, int c) {
    mem_block* old = curr;
	//Verbleibende größe nach berechnung der anforderungen berechnen
    size_t remaining_size = old->size - (rounded_size + sizeof(mem_block));
    old->size = rounded_size;
    old->size |= 1;
	fill_memory(old, c);
    //neuen mem_block erstellen, Pointer setzen
    mem_block* new =memset((mem_block*)((int)old + sizeof(mem_block) + rounded_size), 0 , sizeof(mem_block));
	new->size = remaining_size;


    if(old->next != NULL){
		mem_block* temp = old->next;
        temp->prev = new;
    }
    new->next = old->next;
    old->next = new;
    new->prev = old;
    return old;
}

// 1 wenn belegt(oder null), 0 wenn frei
int check_if_occupied(mem_block* to_check){
	if(to_check==NULL){
		return 2;
	}
	if((to_check->size & 1) == 1){
		return 1;
	}
		return 0; 
	}

//Wird nur aufgerufen wenn bekannt ist, dass beide blöcke nicht null sind 
void* combine_blocks(mem_block* prev, mem_block* next){
	size_t updated_size = next->size + prev->size + sizeof(mem_block)-1; 
	prev->size=updated_size;

	mem_block* after_next = next->next; 
	if(after_next ==NULL) {
		prev->next=NULL; 
	} else {
		prev->next = after_next; 
		after_next->prev = prev; 
	}
	return prev; 
}

void my_free(void *ptr){
	if(ptr==NULL){
		return;
	}
	mem_block* curr = ((mem_block*)((int) ptr - sizeof(mem_block)));
	mem_block* prev_mem = curr->prev; 
	mem_block* next_mem = curr->next; 
	//Davor und danach belegt: 
	if((check_if_occupied(prev_mem)>=1) && (check_if_occupied(next_mem)>=1)){
		curr->size= curr->size&= ~(1<<0);
	
	} else if((check_if_occupied(prev_mem)==0) && (check_if_occupied(next_mem)==0)) {
		 //Davor und danach free
		int updated_size = prev_mem->size + curr->size + next_mem->size + 2*(sizeof(mem_block))-1; 
		prev_mem->size = updated_size; 
		if(next_mem->next==NULL){
			prev_mem->next=NULL; 
		} else {
			mem_block* after_next = next_mem->next; 
			prev_mem->next = after_next;
			after_next->prev=prev_mem;  
		}
		if(last_allocation==curr || last_allocation == next_mem){
			last_allocation=prev_mem;
		} 
	} else if((check_if_occupied(prev_mem)==0) && (check_if_occupied(next_mem)>=1)){ //Davor frei, danach belegt
		if(last_allocation==curr){
			last_allocation=prev_mem;
		}
		combine_blocks(prev_mem, curr);
		
	} else if((check_if_occupied(prev_mem)>=1) && (check_if_occupied(next_mem)==0)){ //Davor belegt, danach frei
		if(last_allocation==next_mem){
			last_allocation=curr; 
		}
		combine_blocks(curr, next_mem); 
	}

}