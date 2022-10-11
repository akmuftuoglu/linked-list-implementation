//
//  main.cpp
//  HW1
//
//  Created by Aral Muftuoglu on 10/3/22.
//


#include <string>
#include <iostream>
#include "list.h"

using namespace std;


Node::Node(string s)
{
    data = s;
    next = nullptr;     // initially a node's first and last would point to nullptr
    previous = nullptr;
}

List::List()
{
    first = nullptr;    // empty list has first and last point to nullptr
    last = nullptr;
}

void List::push_front(std::string data)
{
    // if the list is empty
    if (first == nullptr && last == nullptr)
    {
        Node* temp = new Node(data);
        
        first = temp;
        last = temp;
        
        first->next = nullptr;
        first->previous = nullptr;
        
        last->next = nullptr;
        last->previous = nullptr;
        
    }
    else // or if it has elements
    {
        Node* temp = new Node(data);
        
        temp->next = first;
        temp->previous = nullptr;
        
        first->previous = temp;
        first = temp;
    }
}

void List::reverse()
{
    // cant reverse an empty list
    if (first == nullptr && last == nullptr)
    {
        return;
    }
    
    Iterator iter;
    iter = this->begin();   // have an iterator point to the beginning
    
    Node* temp = nullptr;   // temp of iter.position
                        
    // iterate until the end
    while (iter.position != nullptr)
    {
        temp = iter.position->previous;
        iter.position->previous = iter.position->next;
        iter.position->next = temp;
        iter.position = iter.position->previous;    // follow previous since we switched the next and prev points
    }
    
    // swap first and last pointers of the node
    temp = first;
    first = last;
    last = temp;
    
    
}


void List::push_back(std::string data) {
    
    // if the list is empty
    if (first == nullptr && last == nullptr)
    {
        Node* temp = new Node(data);
        
        first = temp;
        last = temp;
        
        first->next = nullptr;
        first->previous = nullptr;
        
        last->next = nullptr;
        last->previous = nullptr;
        
    }
    else
    {
        Node* temp = new Node(data);
        Node* counter = first;
        
        while (counter->next != nullptr)
        {
            counter = counter->next;
        }
        
        counter->next = temp;
        temp->previous = counter;
        temp->next = nullptr;
        
        last = temp;
    }
}


void List::swap(Iterator iter1, Iterator iter2) {
    
    // cant swap nodes in an empty list
    if (first == nullptr && last == nullptr)
    {
        return;
    }
    
    // dont swap if swapping iterators pointing at the same node
    if (iter1.position == iter2.position)
    {
        return;
    }
    
    // if you are swapping consecutive nodes and iter1 is before iter2
    if (iter1.position->next == iter2.position)
    {
        Node* leftMost = iter1.position->previous;
        Node* rightMost = iter2.position->next;
        
        if (leftMost != nullptr)
        {
            leftMost->next = iter2.position;
        }
        else
        {
            this->first = iter2.position;
        }
        
        iter2.position->previous = leftMost;
        iter2.position->next = iter1.position;
        
        if (rightMost != nullptr)
        {
            rightMost->previous = iter1.position;
        }
        else
        {
            this->last = iter1.position;
        }
        
        iter1.position->previous = iter2.position;
        iter1.position->next = rightMost;
        
        return;

    }
    
    // same thing but if iter2 is before iter1
    if (iter2.position->next == iter1.position)
    {
        Node* leftMost = iter2.position->previous;
        Node* rightMost = iter1.position->next;
        
        if (leftMost != nullptr)
        {
            leftMost->next = iter1.position;
        }
        else
        {
            this->first = iter1.position;
        }
        
        iter1.position->previous = leftMost;
        iter1.position->next = iter2.position;
        
        if (rightMost != nullptr)
        {
            rightMost->previous = iter2.position;
        }
        else
        {
            this->last = iter2.position;
        }
        
        iter2.position->previous = iter1.position;
        iter2.position->next = rightMost;
        
        return;

    }
    
    // code for swapping non-consecutive nodes
    
    Node* prevOne = iter1.position->previous;
    Node* nextOne = iter1.position->next;
    
    Node* prevTwo = iter2.position->previous;
    Node* nextTwo = iter2.position->next;
    
    iter2.position->previous = prevOne;
    iter2.position->next = nextOne;
    
    iter1.position->previous = prevTwo;
    iter1.position->next = nextTwo;
    
    // need to check if the surrounding temp nodes point to nullptr
    // if so, an error will occur: nullptr cannot have a next or previous pointer
    if (prevOne != nullptr)
    {
        prevOne->next = iter2.position;
    }
    
    if (nextOne != nullptr)
    {
        nextOne->previous = iter2.position;
    }
    
    if (prevTwo != nullptr)
    {
        prevTwo->next = iter1.position;
    }
    
    if (nextTwo != nullptr)
    {
        nextTwo->previous = iter1.position;
    }

    if (nextTwo == nullptr)
    {
        this->last = iter1.position;
    }
    
    if (nextOne == nullptr)
    {
        this->last = iter2.position;
    }
    
    if (prevTwo == nullptr)
    {
        this->first = iter1.position;
    }
    
    if (prevOne == nullptr)
    {
        this->first = iter2.position;
    }
}

Iterator List::erase(Iterator iter) {
    
    // if there are no nodes = list is empty
    if (iter.position == nullptr)
    {
        return iter;
    }
    
    // erase first node
    if (iter.position == first)
    {
      
        Node* toBeDeleted = first;
        
        iter.position = iter.position->next;
        
        delete toBeDeleted;
        
        this->first = iter.position;
        iter.position->next = first->next;
        iter.position->previous = nullptr;
        
        return iter;
    }
    
    // erase last node
    if (iter.position == last)
    {
        Node* toBeDeleted = last;
        
        iter.position = iter.position->previous;
        
        delete toBeDeleted;
        
        this->last = iter.position;
        iter.position->previous = last->previous;
        iter.position->next = nullptr;
        
        return iter;
    }
    
    // else its a node in the middle
    
    Node* iter_prev = iter.position->previous;
    Node* iter_next = iter.position->next;
    Node* marker = iter.position;
    
    iter_prev->next = iter_next;
    iter_next->previous = iter_prev;
    
    iter.position = iter.position->next;
    
    delete marker;
    
    return iter;
}

Iterator List::begin()
{
    Iterator x;
    x.container = this;
    x.position = this->first;
    return x;
}

Iterator List::end()
{
    Iterator x;
    x.container = this;
    x.position = this->last->next;
    return x;
}


Iterator::Iterator() {
    
    container = nullptr;
    position = nullptr;
}

std::string Iterator::get() const {
    
    return position->data;
}

void Iterator::next() {
    
    if (position == this->container->last->next)
    {
        return;
    }
    
    position = position->next;
}


void Iterator::previous() {
    
    if (position == this->container->last->next)
    {
        position = this->container->last;
    }
    else if (position == this->container->first)
    {
        return;
    }
    else
    {
        position = position->previous;
    }
}


bool Iterator::equals(Iterator b) const
{
    if (this->position == b.position)
    {
        return true;
    }
    
    return false;
}



int main()
{
    return 0;
} // end of main

