//
// Created by Liad on 28/06/2019.
//

#ifndef OOP5_SUBJECT_H
#define OOP5_SUBJECT_H

#include "OOP5EventException.h"
#include <vector>
#include "Observer.h"

template<typename T>
class Subject{
    std::vector<Observer<T>*> Observers;

public:
    Subject(){
        Observers = std::vector<Observer<T>*>();
    }

    void notify(const T& t){
        for(typename std::vector<Observer<T>*>::iterator it = Observers.begin(); it != Observers.end(); ++it){
            (*it)->handleEvent(t);
        }
    }

    void addObserver(Observer<T>& o){
        for(typename std::vector<Observer<T>*>::iterator it = Observers.begin(); it != Observers.end(); ++it){
            if(*it == &o){
                throw ObserverAlreadyKnownToSubject();
            }
        }
        Observers.push_back(&o);
    }


    void removeObserver(Observer<T>& o){
        for(typename std::vector<Observer<T>*>::iterator it = Observers.begin(); it != Observers.end(); ++it){
            if(*it == &o){
                Observers.erase(it);
            }
        }
        throw ObserverUnknownToSubject();
    }


    Subject<T>& operator+=(Observer<T>& o){
        this->addObserver(o);
        return *this;
    }


    Subject<T>& operator-=(Observer<T>& o){
        this->removeObserver(o);
        return *this;
    }

    Subject<T>& operator()(const T& t){
        this->notify(t);
        return *this;
    }

    ~Subject(){};

};



#endif //OOP5_SUBJECT_H
