//
//  list.h
//  HW1
//
//  Created by Aral Muftuoglu on 10/3/22.
//

#ifndef list_h
#define list_h

#include <string>
#include <iostream>

class List;
class Iterator;

class Node
{
    public:
        /**
          Constructs a node with a given data value.
          @param s the data to store in this node
          */
        Node(std::string s);
    private:
        std::string data;
        Node* previous;
        Node* next;
        friend class List;
        friend class Iterator;
};

class List
{
    public:
        /**
          Constructs an empty list;
          */
        List();
        /**
          Appends an element to the list.
          @param data the value to append
          */
        void push_front(std::string data);
        /**
          Insert an element to the list in the beginning.
          @param data the value to insert
          */
        void push_back(std::string data);
        /**
          Reverse the list
          */
        void reverse();
        /**
          Swap two nodes in the list.
          @param iter1 iter2 the positions to swap
          @iterators point to the old nodes after swapping
          */
        void swap(Iterator iter1, Iterator iter2);
        /**
          Removes an element from the list.
          @param iter the position to remove
          @return an iterator pointing to the element after the
          erased element
          */
        Iterator erase(Iterator iter);
        /**
          Gets the beginning position of the list.
          @return an iterator pointing to the beginning of the list
          */
        Iterator begin();
        /**
          Gets the past-the-end position of the list.
          @return an iterator pointing past the end of the list
          */
        Iterator end();
    private:
        Node* first;
        Node* last;
        friend class Iterator;
};

class Iterator
{
    public:
        /**
          Constructs an iterator that does not point into any list.
          */
        Iterator();
        /**
          Looks up the value at a position.
          @return the value of the node to which the iterator points
          */
        std::string get() const;
        /**
          Advances the iterator to the next node.
          */
        void next();
        /**
          Moves the iterator to the previous node.
          */
        void previous();
        /**
          Compares two iterators
          @param b the iterator to compare with this iterator
          @return true if this iterator and b are equal
          */
        bool equals(Iterator b) const;
    private:
        Node* position;
        List* container;
        friend class List;
};



#endif /* list_h */
