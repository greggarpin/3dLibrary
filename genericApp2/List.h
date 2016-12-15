//
//  List.h
//  genericApp2
//
//  Created by Arpin, Gregg on 6/24/16.
//  Copyright (c) 2016 Arpin, Gregg. All rights reserved.
//

#ifndef genericApp2_List_h
#define genericApp2_List_h

#include "Util.h"

template <class T> class List
{
public:
    List(unsigned int sizeSeed = 100) : currSize(0), listArray(NULL), index(0)
    {
        assert(sizeSeed > 0);

        growTo(sizeSeed);
    };

    virtual ~List()
    {
        delete [] listArray;
    }

    void append(T item)
    {
        if (index >= currSize)
        {
            growTo(currSize + 1 + currSize/10);
        }
        listArray[index++] = item;
    };

    const T getAt(unsigned int elIndex) const
    {
        // TODO:: Probably execption instead of assertion
        assert(index > elIndex);
        return listArray[elIndex];
    }

    unsigned int getNumItems() const { return index; };

    virtual void clear()
    {
        unsigned int oldSize = currSize;

        delete [] listArray;
        index = 0;
        currSize = 0;
        listArray = NULL;

        growTo(oldSize);
    }

private:
    void growTo(unsigned int newSize)
    {
        assert(newSize > currSize);

        T* newArray = new T[newSize];

        if (listArray != NULL)
        {
            for (unsigned int i = 0; i <= index; i++)
            {
                newArray[i] = listArray[i];
            }

            delete [] listArray;
        }

        listArray = newArray;
        currSize = newSize;
    };

    unsigned int currSize;
    T* listArray;
    unsigned int index;
};

#endif
