README.txt by Augustus Chang

Notes:
/* a test1.cpp file has been included to test the functionalities of hashMap */
1. enter ‘make’ in the command line to run the instructions in the Makefile
2. enter ‘./test1’ to run the executable program
3. enter ‘make clean’ to clean the object files and executable

The prompt says to only use primitive types so I was unsure if strings were permitted. I decided against using strings since they’re technically objects. So strings are effectively implemented as null terminating character arrays.

This was my first program in C++ . I knew C, the parent, and Java, the child. 

- - - - - - - - - - - -
Unsigned ints are used when possible, to make efficient use of memory since there should be no use of negative numbers when referring to size, count, or location in the HashMap. 

Linked list Big-O is as follows:
	Insertion        : O(n) - since a linear search is done to prevent duplicates
	Search/Deletion  : O(n)
But because the hashMap size is fixed, load factor <=1. In other words, on average, each bucket should have 1 key/value entry at most, so search and deletion will on average not be costly. 

What are the data structures used in myHashMap? :

Node : Key/value entries are stored in Nodes. Because load factor <= 1, conflict resolution “daisy chaining” i	efficient enough.
  
Bucket : A bucket has a pointer to a Node.

Map: Included in the hashMap class, a map is simply an array of Buckets.

- - - - - - - - - - - -


