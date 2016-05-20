#include "aghContainer.h"
#include "aghElement.h"
#ifndef AGHDLIST_H
#define AGHDLIST_H

template <class T>
class aghDlist:public aghContainer<T>{
    friend class Element<T>;
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
            Element<T>* b = Head;
            Element<T>* c = Head -> next();
            delete b;
            Head = c;
        }
        Tail = NULL;
    }
  /*  void append(T const& value)
    {
        if ((Head == NULL) && (Tail == NULL))
        {
            Head = new Element<T>(value);
            Tail = Head;
        }
        else if ((Head != NULL) && (Tail == NULL))
        {
            Element<T> *tmp = new Element<T>(Head, value);
            Tail = tmp;
        }
        else
        {
            Element<T>* nowy = new Element<T>(Tail, value);
            Tail -> setNext(nowy);
            nowy -> setPrev(Tail);
            Tail = nowy;
        }
    }*/

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
        else
        {
            Element<T>* nowy = new Element<T>(Tail, value);
            Tail->setNext(nowy);
            Tail = nowy;
        }
    }

    int size() const
    {
        int licznik = 0;
        if ((Head == NULL) && (Tail == NULL))
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

    T& at(int place) const
    {
        int licznik = 0;
        if ((place >= 0) && (place <= size()))
        {
            for (Iterator i = Head; i != NULL; i = i->next())
            {
                if (licznik == place)
                {
                    //cout << i -> getValue() << " ... " ;
                    return i -> data;
                }
                licznik++;
            }
        }
        else
        {
            //wywal wyjatek
            cout << "poza zakresem" << endl;
        }
       // return Head -> getValue();
    }

    aghDlist& operator= (aghDlist const& Source)
    {
        if (this == &Source)
		{
		    return *this;
		}
        else
        {
            if (Head!=NULL)
            {
                 clear();
            }
            Iterator i = Source.Head;
            while (i != NULL)
            {
                this -> append(i -> data);
                i = i -> next();
            }
            return *this;
        }
    }

    aghDlist<T>(const aghDlist<T> & kopia)
    {
        if (Head != NULL)
        {
            clear();
        }
        Iterator j = this -> front();
        for (Iterator i = kopia.Head; i != NULL; i = i -> next())
        {
            append(i -> data);
            j = j -> next();
        }
    }

    aghDlist<T> (const aghContainer<T> &ToCopy)
    {
        clear();
        int j = 0;
        while (j < ToCopy.size())
        {
            append(ToCopy.at(j));
            j++;
        }
        /*int rozmiar = ToCopy.size();
        Iterator i = this -> front();
        while (this -> size() < rozmiar)
        {
            append(ToCopy.at(this->size()));
            i = i -> next();
        }*/
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

    bool insert(int place, T const& dodawanyElement)
    {
        if ((place >= 0) && (place <= size()))
        {
            if (Head == NULL)
            {
                append(dodawanyElement);
                return true;
            }
            else
            {
                if (place == 0)
                {
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
    for (Iterator i = right.Head; i != NULL; i = i -> next())
    {
        os << i -> getValue() << ", ";
    }
    if (right.Tail != NULL)
    {
        os << "Tail: " << right.Tail -> getValue() << endl;
    }
    os << endl;
}

};
#endif // AGHDLIST_H
