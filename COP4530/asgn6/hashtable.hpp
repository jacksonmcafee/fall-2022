#include "hashtable.h"

template <typename K, typename V>
// default constructor
cop4530::HashTable<K,V>::HashTable(size_t size) {
  // set contained value counter size to zero
  tSize = 0;

  // resize table using prime_below()
  table.resize(prime_below(size));
}

template <typename K, typename V>
// destructor
cop4530::HashTable<K,V>::~HashTable() {
  // call clear() to delete table contents 
  clear();
}

template <typename K, typename V>
// check if key K is contained in table
bool cop4530::HashTable<K,V>::contains(const K& k) {
  // get list that contains k
  auto &list = table[myhash(k)];
  
  // iterate through list and check pair.first for each
  // if pair.first == k, return true
  // itr should be of type Pair<K,V>
  for (auto itr = list.begin(); itr != list.end(); ++itr) {
    if (itr->first == k) {
      return true;
    }
  }

  // else, return false
  return false;
}

template <typename K, typename V>
// check if key-value pair K,V is contained in table
bool cop4530::HashTable<K,V>::match(const std::pair<K, V> &kv) {
  // extremely similar to contains, just check for entire pair
  K k = kv.first;
  auto &list = table[myhash(k)];

  // iterate through list and check if pair == kv for each
  // if pair == kv, return true
  // itr should be of type Pair<K,V>
  for (auto itr = list.begin(); itr != list.end(); ++itr) {
    if (*itr == kv) {
      return true;
    }
  }

  // else, return false
  return false;
}

template <typename K, typename V>
// insert key-value pair K,V if not currently within table
bool cop4530::HashTable<K,V>::insert(const std::pair<K, V> & kv) {
  // verify that !match(kv)
  if (!match(kv)) {      
      // locate list preemptively, needed either way
      auto &list = table[myhash(kv.first)];

      // verify that !contains(k)
      if (!contains(kv.first)) {
        // if size+1 is greater than current size, rehash table
        if (tSize++ > table.size()) {
          rehash();
          tSize--;
        }

        // insert pair normally
        list.push_back(kv);
      }
      else {
        // no need to check for rehash since we are swapping, not inserting
        // k already exists, locate and swap pair.second with v
        for (auto itr = list.begin(); itr != list.end(); ++itr) {
          if (itr->first == kv.first) {
            itr->second = kv.second;
          }
        }
      }
      tSize++;
      return true;
  }
  // kv already exists in table, return false
  return false;
}

template <typename K, typename V>
// move alternative to insert
bool cop4530::HashTable<K,V>::insert(std::pair<K, V> && kv) {
  // verify that !match(kv)
  if (!match(kv)) {      
      // locate list preemptively, needed either way
      auto &list = table[myhash(kv.first)];

      // verify that !contains(k)
      if (!contains(kv.first)) {
        // if size+1 is greater than current size, rehash table
        if (tSize++ > table.size()) {
          rehash();
          tSize--;
        }

        // insert pair normally
        list.push_back(move(kv));
      }
      else {
        // no need to check for rehash since we are swapping, not inserting
        // k already exists, locate and swap pair.second with v
        for (auto itr = list.begin(); itr != list.end(); ++itr) {
          if (itr->first == kv.first) {
            itr->second = kv.second;
          }
        }
      }
      tSize++;
      return true;
  }
  // kv already exists in table, return false
  return false;
}

template <typename K, typename V>
// remove key-value pair associated with k
bool cop4530::HashTable<K,V>::remove(const K& k) {
  // verify that contains(k)
  if (contains(k)) {
    // get list k is in
    auto &list = table[myhash(k)];

    // locate the position of the pair containing k
    for (auto itr = list.begin(); itr != list.end(); ++itr) {
      // iterate through list until k is located
      if (itr->first == k) {
        // erase itr from list, return true
        list.erase(itr);
        tSize--;
        return true;
      }
    }
  }
  // k was not in table, return false
  return false;
}

template <typename K, typename V>
// clear values contained in table
void cop4530::HashTable<K,V>::clear() {
  makeEmpty();
}

template <typename K, typename V>
// load content from text file to hashtable
bool cop4530::HashTable<K,V>::load(const char* filename) {
  // create ifstream then open file filename
  std::ifstream file;
  file.open(filename);

  if (!file) {
    // return false if file did not open for any reason
    return false;
  }

  // declare key and val, read lines into std::pair<K,V>
  K key;
  V val;
 
  while(!file.eof()) {
    // loop until end of file is reached
    file >> key >> val;
    insert(make_pair(key, val));
  }

  // close stream and return true 
  file.close();
  return true;
}      


template <typename K, typename V>
// print out table contents
void cop4530::HashTable<K,V>::dump() {
  // iterate through each list in table
  for (size_t i = 0; i < table.size(); ++i) {
    auto &list = table[i];
    auto itr = list.begin();

    if (list.empty()) {
      // if this bucket is empty, continue to next list
      continue;
    }
    else {
      // bucket isn't empty, print key-val pair and endline
      std::cout << itr->first << " " << itr->second << std::endl;
      while (++itr != list.end()) {
        // if there are more pairs within list, keep printing
        std::cout << itr->first << " " << itr->second << std::endl;
      }
    }
  }
}

template <typename K, typename V>
// write contents of hashtable to file
bool cop4530::HashTable<K,V>::write_to_file(const char* filename) {
  // create ifstream then open file filename
  std::ofstream file;
  file.open(filename);

  if (!file) {
    // return false if file did not open for any reason
    return false;
  }

  for (size_t i = 0; i < table.size(); ++i) {
    // iterate through each list in table
    auto &list = table[i];
    auto itr = list.begin();

    if (list.empty()) {
      // if this bucket is empty, continue to next list
      continue;
    }
    else {
      // bucket isn't empty, print key-val pair and endline
      file << itr->first << " " << itr->second << std::endl;
      while (++itr != list.end()) {
        // if there are more pairs within list, keep printing
        file << itr->first << " " << itr->second << std::endl;
      }
    }
  }
  // close stream and return true
  file.close();
  return true;
}

template <typename K, typename V>
// accesses size data for hashtable
int cop4530::HashTable<K,V>::getSize() {
  return tSize;
}

template <typename K, typename V>
// delete all elements in hashtable, clear() calls this
void cop4530::HashTable<K,V>::makeEmpty() {
  // set size back to zero
  tSize = 0;
  
  // iterate through each value in table 
  // use built in list.clear() to empty  
  for (auto &x : table) {
    x.clear();
  }
}

template <typename K, typename V>
// call when elements > vec.size()
void cop4530::HashTable<K,V>::rehash() {
  // move data from table to old_table
  // allows for old_table to be destroyed after rehash
  auto old_table = table;

  // resize and clear table
  table.resize(prime_below(2 * table.size()));
  makeEmpty();

  // take old_table data and insert it into table
  // for each pair in each list in table, 
  // insert that pair into table
  for (auto &list : old_table) {
    for (auto &p : list) {
      insert(move(p));
    }
  }
}

template <typename K, typename V>
// return vector index in which k is stored
size_t cop4530::HashTable<K,V>::myhash(const K& k) {
  // get hash h
  std::hash<K> h;

  // select bucket with hash(key) % (# of buckets)
  return h(k) % table.size();
}

template <typename K, typename V>
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
unsigned long cop4530::HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

template <typename K, typename V>
// sets all prime number indexes to 1. Called by method prime_below(n) 
void cop4530::HashTable<K,V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

