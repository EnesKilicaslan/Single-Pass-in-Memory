/*
 * Created by Enes Kılıçaslan on 06/12/16.
 *
 *
 *
 */
#include "PostingList.h"
#include <sstream>

//we start with a 100 capasity and increase it when needed
PostingList::PostingList() :capacity(10), used(0)
{
    this->doc_ids = new long int[capacity];
}

// Copy constructer
PostingList::PostingList(const PostingList& PostingListObj)
        :capacity(PostingListObj.getCapacity( )), used(PostingListObj.getNumberUsed( ))
{
    this->doc_ids = new long int[capacity];

    for (int i =0; i < used; i++)
        doc_ids[i] = PostingListObj.doc_ids[i];
}

void PostingList::addDoc_id(long int doc_id)
{
    //check if the doc_id is aready exist
    if (used > 0)
        if (this->doc_ids[used - 1] == doc_id )
            return;
    if (this->full()) // if the array full we need to double the capacity
    {
        this->doubleCapacity();
    }

    this->doc_ids[used] = doc_id;
    used++;
}

// oeprator overload
long int& PostingList::operator[](int index)
{
    if (index >= used)
    {
        cout << "Illegal index. " << index << endl;
        exit(0);
    }

    return doc_ids[index];
}

PostingList& PostingList::operator =(const PostingList& rightSide)
{
    if (capacity != rightSide.capacity)
    {
        delete [] doc_ids;
        doc_ids = new long int[rightSide.capacity];
    }

    capacity = rightSide.capacity;
    used = rightSide.used;

    for (int i = 0; i < used; i++)
        doc_ids[i] = rightSide.doc_ids[i];

    return *this;
}

PostingList::~PostingList( )
{
    delete [] this->doc_ids;
}

void PostingList::doubleCapacity()
{
    long int * temp = new long int[this->getCapacity() * 2];
    this->capacity = this->capacity * 2;
    
    for (int i = 0; i < used; i++)
        temp[i] = this->doc_ids[i];

    delete [] this->doc_ids;

    this->doc_ids = temp;
}

string PostingList::toString() const
{
	string result = "";

    for (int i=0; i<used; i++)
    {
    	ostringstream oOStrStream;
 		oOStrStream << doc_ids[i];
        result += oOStrStream.str();

        if( i != used -1) //if i is the last element, don't add a space
        	result += " ";
    }

    return result;
}

/*
template <typename T>
string number_to_string(T pNumber)
{
 ostringstream oOStrStream;
 oOStrStream << pNumber;
 return oOStrStream.str();
}*/


