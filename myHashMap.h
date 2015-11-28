#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H

#include <string>

/* 
 * Create a type definition of unsigned int. 
 * Use unsigned representation instead of signed to make most use of bits. 
 */

typedef unsigned int uint32_t;

/*
 * Node will store key/value pairs.
 */

typedef struct Node_
{
	char *key;	// key
	void *value;	// value of entry
	struct Node_ *next;	// pointer to next node

} Node;

/*
 * Bucket will have a pointer to the front of a linked list.
 */

typedef struct Bucket_
{
	Node *front;	// front of the linked list

} Bucket;

/*
 * class myHashMap
 */
class myHashMap
{
public:
	myHashMap(uint32_t size);		// Constructor
	~myHashMap(void);				// Destructor 

	uint32_t hashFunction(char *key);			// return an index for the key 

	bool set(char *key, void *value);			// store key/value pair in hashMap
	void * get(char *key);						// get value given key
	void * deleteit(char *key);					// delete value given key
	float load(void);							// return the load factor 


private:
	const uint32_t size;						// size of the hashMap does not change
	uint32_t count;								// number of current entries in the map
	Bucket *map;								// pointer to map (implemented as an array of buckets)

	bool searchBucket(Bucket *currBucket, char *key);		// search a Bucket for a key
	void freeBucket(Node *currNode);						// free the linked list attached to a Bucket
	void freeHashMap(void);									// free entire map
};


#endif

