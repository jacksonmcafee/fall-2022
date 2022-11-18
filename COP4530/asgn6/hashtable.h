#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <cstdlib>
#include <iostream>
#include <fstream>

// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;

// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;
 
namespace cop4530 {
	template <typename K, typename V> class HashTable {
		public:
			// constructor and destructor
			HashTable(size_t size = 101);
			~HashTable();

			// check if key K is contained in table
			bool contains(const K& k);

			// check if key-value pair K,V is contained in table
			bool match(const std::pair<K, V> &kv); 

			// insert key-value pair K,V if not currently within table
			bool insert(const std::pair<K, V> & kv);
			// move alternative to insert
			bool insert(std::pair<K, V> && kv);
		
			// remove key-value pair associated with k
			bool remove(const K& k);

			// clear values contained in table
			void clear();

			// load content from text file to hashtable
			bool load(const char* filename);

			// print out table contents
			void dump();

			// write contents of hashtable to file
			bool write_to_file(const char* filename);

			// accesses size data for hashtable
			int getSize();

		private:
			// delete all elements in hashtable, clear() calls this
			void makeEmpty();

			// call when elements > vec.size()
			void rehash();

			// return vector index in which k is stored
			size_t myhash(const K& k);

			// when rehashing vector size, call prime_below(size);
			// use that size as the proper vector size
			unsigned long prime_below (unsigned long n);
			void setPrimes(std::vector<unsigned long>& vprimes);

			// hashtable object, vector of lists of pairs
			std::vector<std::list<std::pair<K,V>>> table;

			// stores size of hashtable
			size_t size;
	};
}


// include class definitions
#include "hashtable.hpp"

#endif
