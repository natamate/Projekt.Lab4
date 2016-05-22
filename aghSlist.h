#include "aghContainer.h"
#include "aghElementS.h"
#include "aghException.h"
#ifndef AGHSLIST_H
#define AGHSLIST_H

template<class T>
class aghSlist:public aghContainer<T>{
    typedef ElementS<T>* Iterator;
protected:
    ElementS<T>* Head;
    ElementS<T>* Tail;
public:

    aghSlist()
    {
        Head = NULL;
        Tail = NULL;
    }

    ~aghSlist()
    {
        clear();
    }

    void clear()
    {
        while (Head != NULL)
        {
                ElementS<T>* tmp = Head;
                tmp = tmp -> next();
                delete(Head);
                Head = tmp;
        }
       // Head = NULL;
        Tail = NULL;
    }

    ElementS<T>* front()
    {
        return Head;
    }

    ElementS<T>* back()
    {
        if (Tail == NULL)
        {
            return Head;
        }
        else
        {
           return Tail;
        }
    }

    bool isEmpty()
    {
        if (Head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void append(T const& dodawanyElement)
    {
       if (Head == NULL)
        {
            Head = new ElementS<T>(dodawanyElement);
            Head -> setNext(Tail);
        }
        else if ((Head != NULL) && (Tail == NULL))
        {
            Tail = new ElementS<T>(dodawanyElement);
            Head -> setNext(Tail);
        }
        else //dodaj element na koniec
        {
            ElementS<T>* nowy = new ElementS<T>(dodawanyElement);
            Tail -> setNext(nowy);
            Tail = nowy;
        }
    }

    int size() const
    {
        int licznik = 0;
        if (Head == NULL)
        {
            return licznik;
        }
        Iterator i = Head;
        while (i != NULL)
        {
            licznik++;
            i = i -> next();
        }
        return licznik;
    }

    friend ostream& operator<<(ostream& os, aghSlist<T> const& right)
    {
        if (right.Head != NULL)
        {
            os << "Head: " << right.Head -> getValue() << " ... ";
            for (Iterator i = right.Head -> next(); i != NULL; i = i -> next())
            {
                os << i -> getValue() << ", ";
            }
            os << endl;
        }
        else
        {
            os << "Lista jest pusta" << endl;
        }
        return os;
    }

    bool insert(int place, T const& dodawanyElement)
    {
        if ((place >= 0) && (place <= size()))
        {
            if (place == 0)
            {
                if (isEmpty() == true)
                {
                    append(dodawanyElement);
                    return true;
                }
                ElementS<T>* tmp = Head;
                ElementS<T>* nowy = new ElementS<T>(dodawanyElement);
                nowy -> setNext(tmp);
                Head = nowy;
                if (tmp -> next() == NULL)
                {
                    Tail = tmp;
                }
                return true;
            }
            Iterator i = this -> front();
            int licznik = 1;
            while (licznik < place)
            {
                i = i -> next();
                licznik++;
            }
            if (i -> next() == NULL)
            {
                append(dodawanyElement);
                return true;
            }
            ElementS<T>* tmp = i;
            ElementS<T>* nowy = new ElementS<T>(dodawanyElement);
            ElementS<T>* tmp2 = tmp -> next();
            nowy -> setNext(tmp2);
            //nowy -> setPrev(tmp);
            //tmp2 -> setPrev(nowy);
            tmp -> setNext(nowy);
            if (nowy -> next() == NULL)
            {
                Tail = nowy;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

 T& at(int place) const
    {
        int licznik = 0;
        if ((place >= 0) && (place <= size()))
        {
            for (Iterator i = Head; i != NULL; i = i->next())
            {
                if (licznik == place)
                {
                    return i -> data;
                }
                licznik++;
            }
        }
        else
        {
            throw aghException(0, "Index out of range", __FILE__, __LINE__);
        }
    }

    aghSlist<T>& operator= (aghSlist<T> const& Source)
    {
        if (this == &Source)
		{
		    return *this;
		}
        else
        {
            if (isEmpty() != true)
            {
                 clear();
            }
            Iterator i = Source.Head;
            while (i != NULL)
            {
                this -> append(i -> getValue());
                i = i -> next();
            }
            return *this;
        }
    }

    aghSlist<T>(const aghSlist<T> & kopia)
    {
        if (isEmpty() != true)
        {
            //clear();
            Head = NULL;
        }
        for (Iterator i = kopia.Head; i != NULL; i = i -> next())
        {
            append(i -> getValue());
        }
    }

    aghSlist<T> (const aghContainer<T> &ToCopy)
    {
        int i = 0;
        Head = NULL;
        Tail = NULL;
        while (i < ToCopy.size())
        {
           append(ToCopy.at(i));
           i++;
        }
    }

    aghSlist<T>& operator<<(aghSlist<T> const& right)
    {
        clear();
        for (Iterator i = right.Head; i != NULL; i = i -> next())
        {
            append(i -> getValue());
        }
        return *this;
    }

    aghSlist<T>& operator<<(T const& dodawanyElement)
    {
        append(dodawanyElement);
        return *this;
    }

    bool replace(int place, T const& dodawanyElement)
    {
        if ((place >= 0) && (place <= size()))
        {
            int ktory = 0;
            Iterator i = this -> front();
            while (ktory < place)
            {
                i = i -> next();
                ktory++;
            }
            i -> setValue(dodawanyElement);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool remove(int place) // do poprawki ten remove podobnie jak insert (dziala ale za duzo tych warunkow... )
    {
        if (place >= 0 && place <= size())
        {
            if (isEmpty() == true)
            {
                return false;
            }
            else
            {
                if ((Head != NULL) && (Tail == NULL))
                {
                    Head = NULL;
                    return true;
                }
                else if ((Head != NULL) && (Head -> next() == Tail) && (Tail != NULL))
                {
                    Tail = NULL;
                    return true;
                }
                int n = 0;
                Iterator i = this -> front();
                while (n < place - 1)
                {
                    i = i -> next();
                    n++;
                }
                ElementS<T> *tmpPrevious = i;
                ElementS<T> *Usuwany = i -> next();
                ElementS<T> *tmpNext = Usuwany -> next();
                tmpPrevious -> setNext(tmpNext);
                delete Usuwany;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    bool contains(T const& _value, int _from = 0) const
    {
        for (Iterator i = Head; i != NULL; i = i -> next())
        {
            if (i -> getValue() == _value)
            {
                return true;
            }
        }
        return false;
    }

    bool operator==(aghSlist<T> const& right)
    {
        if (this -> size() != right.size())
        {
            return false;
        }
        else
        {
            Iterator j = right.Head;
            for (Iterator i = this -> front(); i != NULL; i = i -> next())
            {
                if (i -> getValue() != j -> getValue())
                {
                    return false;
                }
                j = j -> next();
            }
            return true;
        }
    }

    bool operator!=(aghSlist<T> const& right)
    {
        if (this -> size() != right.size())
        {
            return true;
        }
        else
        {
            Iterator j = right.Head;
            for (Iterator i = this -> front(); i != NULL; i = i -> next())
            {
                if (i -> getValue() != j -> getValue())
                {
                    return true;
                }
                j = j -> next();
            }
            return false;
        }
    }

    aghSlist<T>& operator+=(T const& element)
    {
        append(element);
        return *this;
    }

    aghSlist<T>& operator+=(aghSlist<T> const& right)
    {
        for (Iterator i = right.Head; i != NULL; i = i -> next())
        {
            append(i -> getValue());
        }
        return *this;
    }

    T& operator[](int n) const
    {
        if ((n >= 0) && (n <= size()))
        {
            return at(n);
        }
        else
        {
            throw aghException(0, "Index out of range", __FILE__, __LINE__);
        }
    }

    int indexOf(T const& _value, int _from) const
    {
        int licznik = 0;
        if(Head == NULL)
        {
            return -1;
        }
        Iterator i = Head;
        while (licznik < _from)
        {
            if (i -> next() != NULL)
            {
                i = i -> next();
            }
            licznik ++;
        }
        if (i -> getValue() == _value)
        {
            return licznik;
        }
        for (Iterator j = i; j != NULL; j = j -> next())
        {
            if (j -> getValue() == _value)
            {
                return licznik;
            }
            licznik++;
        }
        return -1;
    }
};
#endif // AGHSLIST_H
