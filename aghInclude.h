//File: aghDlist.h
// Plik zawiera deklaracje klasy i opis metod listy dwukierunkowej bazujacej na aghContainer
// Autor: N. Materek && A. Lisiecki
// v 1.2 do poprawki (powtorki kosu w niektorych metodach) bez wyciekow pamieci
// 21.05.2016
#include "aghContainer.h"
#include "aghElement.h"
#include "aghException.h"
#ifndef AGHDLIST_H
#define AGHDLIST_H

template <class T>
class aghDlist:public aghContainer<T>{
    //friend class Element<T>;
    typedef Element<T>* Iterator;
protected:
    Element<T> *Head;
    Element<T> *Tail;
public:

    aghDlist()
    {
        Head = NULL;
        Tail = NULL;
    }

    ~aghDlist()
    {
        clear();
    }

    Element<T>* front()
    {
            return Head;
    }

    Element<T>* back()
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

    void clear()
    {
        while (Head!= NULL)
        {
            Element<T>* tmp = this -> front();
            Element<T>* tmpNext = tmp -> next();
            delete tmp;
            Head = tmpNext;
        }
        Tail = NULL;
    }

    void append(T const& value)
    {
        if (Head == NULL)
        {
            Head = new Element<T>(value);
        }
        else if (Tail == NULL)
        {
            Tail = new Element<T>(Head, value);
            Head->setNext(Tail);
        }
        else //dodaj element na koniec
        {
            Element<T>* nowy = new Element<T>(Tail, value);
            Tail->setNext(nowy);
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
        else
        {
            for (Iterator i = Head; i != NULL; i = i->next())
            {
                licznik ++;
            }
            return licznik;
        }
    }

    T& at(int place) const // nie wiem czemu ale jak jest const przy funkcji to nie dziala this -> front() i musze pisac Head
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

    aghDlist<T>& operator= (aghDlist<T> const& Source)
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

    aghDlist<T>(const aghDlist<T> & kopia)
    {
        if (isEmpty() != true)
        {
            clear();
        }
        for (Iterator i = kopia.Head; i != NULL; i = i -> next())
        {
            append(i -> getValue());
        }
    }

    aghDlist<T> (const aghContainer<T> &ToCopy) //teraz dziala w sumie bo nie wylatuje nawet na codeblocksie
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

    aghDlist<T>& operator<<(aghDlist<T> const& right)
    {
        for (Iterator i = right.Head; i != NULL; i = i -> next())
        {
            append(i -> getValue());
        }
        return *this;
    }

    aghDlist<T>& operator<<(T const& dodawanyElement)
    {
        append(dodawanyElement);
        return *this;
    }

    bool insert(int place, T const& dodawanyElement) // strasznie dlugo wyszlo trzeba zrobic krotsza jakby sie dalo ta funkcje
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
                Element<T>* tmp = Head;
                Element<T>* nowy = new Element<T>(dodawanyElement);
                tmp -> setPrev(nowy);
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
            Element<T>* tmp = i;
            Element<T>* nowy = new Element<T>(dodawanyElement);
            Element<T>* tmp2 = tmp -> next();
            nowy -> setNext(tmp2);
            nowy -> setPrev(tmp);
            tmp2 -> setPrev(nowy);
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

    friend ostream& operator<<(ostream& os, aghDlist<T> const& right)
    {
        if (right.Head != NULL)
        {
            os << "Head: " << right.Head -> getValue() << endl;
        }
        for (Iterator i = right.Head -> next(); i != NULL; i = i -> next())
        {
            os << i -> getValue() << ", ";
        }
        if (right.Tail != NULL)
        {
            os << "Tail: " << right.Tail -> getValue() << endl;
        }
        os << endl;
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
            //uwaga prawdopodobnie wywali sie przy wywalaniu z zerowego miejsca albo place == size()
                while (n < place)
                {
                    i = i -> next();
                    n++;
                }
                Element<T> *Usuwany = i;
                Element<T> *tmpPrevious = Usuwany -> prev();
                Element<T> *tmpNext = Usuwany -> next();
                tmpPrevious -> setNext(tmpNext);
                tmpNext -> setPrev(tmpPrevious);
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

    bool operator==(aghDlist<T> const& right)
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

    bool operator!=(aghDlist<T> const& right)
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

    aghDlist<T>& operator+=(T const& element)
    {
        append(element);
        return *this;
    }

    aghDlist<T>& operator+=(aghDlist<T> const& right)
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
#endif // AGHDLIST_H
