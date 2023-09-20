# c-system-programming
This project was part of an assignment during my studies and consisted of 2 separate tasks. The first was to create a selfmade version of the calloc-function, the other was to reproduce multiple scheduling procedures. The headers and some of the tests were provided as a template.

## Features
### Memory Allocation
The functions in _calloc.c_ were developed to enable a similar behavior to the C-inherent functions _calloc_ and _free_. It features a pre-defined memory-block that can be partially reserved for memory allocations. It checks whether the requested memory size is available and frees the memory slot correctly when it is no longer needed. 

### Scheduling
Multiple scheduling procedures that were tested with a mock-scheduler were implemented. In order to test them, the scheduler received multiple mock-threads that needed to be correctly scheduled according to the tested scheduling procedure.
the _scheduler.c_ file was provided as part of the template. 
