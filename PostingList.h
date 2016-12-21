//
// Created by Enes Kılıçaslan on 06/12/16.
//

#ifndef SPIMI1_POSTINGLIST_H
#define SPIMI1_POSTINGLIST_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

/**
 * this class contains a dinamicly sized long int array (Actually they are doc_id
 * when the array is full, it doubles its capacity itself no need to acumulate from outside
 */
class PostingList {

public:
    PostingList(); // constructer no need argument
    PostingList(const PostingList& postingListObj);
    void addDoc_id(long int doc_id);

    //this will give us an ability that we can use an PostingList object again and again
    //so we don't need to create an instance every time, just call emtyList method
    void emptyList( ){ used = 0; }

    long int& operator[](int index);
    //Read and change access to elements 0 through numberUsed - 1.

    string toString( ) const;

    PostingList& operator =(const PostingList& rightSide);

    //Destructer for the class, because we have a pointer inside (BIG-3 rule)
    ~PostingList( );

private:
    long int * doc_ids;

    //these variables for the dynamic array
    int capacity; //for the size of the array.
    int used; //for the number of array positions currently in use.

    void  doubleCapacity();
    bool full( ) const { return (capacity == used); }//Returns true if the array is full, false otherwise.
    int getCapacity( ) const { return capacity; }
    void setCapacity(long int newCapacity ) { this->capacity = newCapacity; }
    int getNumberUsed( ) const { return used; }

};




#endif //SPIMI1_POSTINGLIST_H
