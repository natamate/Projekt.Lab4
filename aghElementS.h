#ifndef AGHELEMENTS_H
#define AGHELEMENTS_H
#include <iostream>
using namespace std;

template<class T>
class ElementS{
protected:
    ElementS *nextElement;
public:
    T data;

    ElementS()
    {
        nextElement = NULL;
    }

    ElementS (T value)
    {
        nextElement = NULL;
        data = value;
    }

    ElementS(ElementS *next, T value)
    {
        nextElement = next;
        data = value;
    }

    ElementS* next()
    {
        return nextElement;
    }

    void setNext(ElementS* next)
    {
        nextElement = next;
    }

    T getValue()
    {
        return data;
    }

    void setValue(T value)
    {
        data = value;
    }

};
#endif // AGHELEMENTS_H
