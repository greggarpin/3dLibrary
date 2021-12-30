#ifndef __genericApp2__Stack__
#define __genericApp2__Stack__

// TODO:: Should probably leverage List class
#include <assert.h>
#include "Util.h"

template <class T> class Stack
{
public:
    Stack(unsigned int sizeSeed = 100) : currSize(0), stackArray(NULL), index(0)
    {
        assert(sizeSeed > 0);

        growTo(sizeSeed);
    };

    virtual ~Stack()
    {
        delete [] stackArray;
    }

    void push(T item)
    {
        if (index >= currSize)
        {
            growTo(currSize + 1 + currSize/10);
        }
        stackArray[index++] = item;
    };

    T pop()
    {
        // TODO:: Probably execption instead of assertion
        assert(index > 0);
        return stackArray[--index];
    }

    unsigned int getNumItems() const { return index; };
private:
    void growTo(unsigned int newSize)
    {
        assert(newSize > currSize);

        T* newArray = new T[newSize];

        if (stackArray != NULL)
        {
            for (unsigned int i = 0; i <= index; i++)
            {
                newArray[i] = stackArray[i];
            }

            delete [] stackArray;
        }

        stackArray = newArray;
        currSize = newSize;
    };

    unsigned int currSize;
    T* stackArray;
    unsigned int index;
};

class StackTestSled : public TestSled
{
public:
    void test()
    {
        const unsigned int numElements = 26;
        unsigned char elements[numElements] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                                    'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                    'o', 'p', 'q', 'r', 's', 't', 'u',
                                    'v', 'w', 'x', 'y', 'z'};
        Stack<char> testStack(10);

        test_fail_if(testStack.getNumItems() != 0, "Expected 0 elements in empty stack");

        for (unsigned int i = 0; i < numElements; i++)
        {
            testStack.push(elements[i]);
            test_fail_if(testStack.getNumItems() != i + 1, "Wrong number of items in stack");
        }
        test_fail_if(testStack.getNumItems() != numElements, "Incorrect number of elements in populated stack");
        for (int i = numElements - 1; i >= 0; --i)
        {
            test_fail_if(testStack.pop() != elements[i], "Incorrect item found in stack");
            test_fail_if(testStack.getNumItems() != i, "Incorrect number of items in stack during pop test");
        }
        test_pass;
    }
};

#endif /* defined(__genericApp2__Stack__) */
