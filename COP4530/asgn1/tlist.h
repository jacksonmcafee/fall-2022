#include <iostream>
#include <utility>
#include "tnode.h"
// **********************************************************
// * Name:  tlist.h.                                        *
// * Description:   Starter file for doubly-linked list.    *
// *    This is a templated list class designed to use the. *
// *    node class to store multiple occurances of the data *
// *    of type T.                                          *
// * Last Modifed by: Dr. David A. Gaitros                  *
// * Date: 12/8/2019                                        *
// **********************************************************

template <typename T>
class TList
{
   friend class TListIterator<T>;

public:
   // create empty linked list
   TList() {
      // set head / tail to nullptr because no nodes currently exist
      first = last = nullptr:
      size = 0;
   }

   // Create list with num copies of val
   TList(T val, int num) {
      // first node, set to head, prev to nullptr
      Node<T> * current_node = new Node<T>(val);
      first = current_node;
      current_node->prev = nullptr;

      // set size
      size = 1;

      for (int i = 0; i < num - 1; i++) {
         Node<T> * new_node = new Node<T>(val);
         current_node->next = new_node;
         new_node->prev = current_node;
         size++;
         current_node = new_node;
      }
      // last node, set to tail, next to nullptr
      current_node->next = nullptr;
      last = current_node;
   }

   // destructor
   ~TList() {
      // start from first node, move to second before deleting prior node
      Node<T> * node = first;
      while (node->next != nullptr) {
         node = node->next;
         delete node->prev;
      }
      // on final node, delete node
      delete node;
   }

   // copy constructor
   TList(const TList& L) {
    if ( L.first == nullptr)
        first = last = nullptr;
    else
    { 
        first = new Node<T>( L.first );      // allocate head and copy data
        Node<T> temp_L* = L.first->next;
        Node<T> temp* = last;
        while (temp_L != nullptr )
        {
         // doesnt work, needs to not be a cnostructor
            temp2 = new Node<T>(temp_L.data);
            temp2->next = nullptr;
            temp2->prev = temp;
            temp->next = temp2;
            temp = temp->next;
            temp_L = temp_L->next;
        }
        last = temp;
    } 
   }

   // copy assignment operator
   TList& operator=(const TList& L) {




   }


   TList(TList && L);			// Move constructor
   TList& operator=(TList && L);	// Move assignment operator

   // checks to see if list is empty
   bool IsEmpty() const {
      // could replace with return ( first == nullptr );
      if (size == 0) {
         return true;
      }
      else {
         return false;
      }
   }	

   // clear out list, reset to empty
   void Clear() {
      current_node = new Node<T>;
      current_node = first;
      while (current_node != nullptr) {
         current_node = current_node->next;
         delete current_node->prev;
      }
      delete current_node;

      first = last = nullptr;
      size = 0;
   }

   int GetSize() const { return size; }   // return the size of the list

   void InsertFront(const T& d);	// Insert data d as first element
   void InsertBack(const T& d);		// Insert data d as last element
   void RemoveFront();			// Remove first element of list
   void RemoveBack();			// Remove last element of list

   T& GetFirst() const { return *first; }			// Return first element of list
   T& GetLast() const { return *last; }			// Return last element of list

   TListIterator<T> GetIterator() const;    // Return iterator to first item
   TListIterator<T> GetIteratorEnd() const; // Return iterator to last item
// **********************************************************
// * Insert data element d just before item at pos position *
// **********************************************************

   void Insert(TListIterator<T> pos, const T& d);
// **********************************************************
// * Remove data item at position pos. Return iterator      *
// *  to the item.                                          * 
// *  that comes after the one being deleted.               *
// **********************************************************

   TListIterator<T> Remove(TListIterator<T> pos);
// **********************************************************
// * Print list contents in order, separated by given       *
// * delimiter.                                             *
// **********************************************************

   void Print(std::ostream& os, char delim = ' ') const;

private:
   Node<T>* first;		// pointer to first node in list
   Node<T>* last;		// pointer to last node in list
   int size;			// number of nodes in the list
   static T dummy;		// dummy object, for empty list data returns
   				//  assuming type T has default construction

};

template <typename T>
T TList<T>::dummy;		// initialization of static member
// **********************************************************
// *. Stand-alone function for concatenating two TList      *
// *  objects                                               *
// **********************************************************

template <typename T>
TList<T> operator+(const TList<T>& t1, const TList<T>& t2);


// **********************************************************
// Declaration of class TListIterator                       *
// **********************************************************


template <typename T>
class TListIterator
{
   friend class TList<T>;

public:
   TListIterator();			// default constructor
   bool HasNext() const;		// next item available?
   bool HasPrevious() const;		// previous item available?
   TListIterator<T> Next();		// advance to next item
   TListIterator<T> Previous();		// move to previous item
   T& GetData() const;			// return data element of current node

private:
   Node<T>* ptr;		// pointer to current list item
};

#include "tlist.hpp"		// bring in definition file here

