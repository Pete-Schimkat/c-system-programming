#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      3
#define STRATEGY        RR

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      3,      1,      'A'},
                                        {   4,      8,      4,      'B'},
                                        {   9,      7,      4,      'C'},
                                        {   13,     2,      4,      'D'},
                                        {   15,     4,      2,      'E'}};

    
    char* expected_result = "AAA BBBBBBCCCBBDDCCCEEECE";

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result,resulting_schedule)){
        fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result,resulting_schedule);
        free(resulting_schedule);
        exit(1);
    }
    printf("Passed.\n");

    free(resulting_schedule);
    exit(0);
}
