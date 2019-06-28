//
// Created by Liad on 28/06/2019.
//

#ifndef OOP5_SUBJECT_H
#define OOP5_SUBJECT_H

#include "OOP5EventException.h"
#include <vector>
#include "Observer.h"

//The struct represents a Subject, that can invoke methods in a set of Observers that it recognizes.
template<typename T>
class Subject{
    //The group of Observers the Subject recognizes
    std::vector<Observer<T>*> Observers;

public:
    Subject(){
        Observers = std::vector<Observer<T>*>();
    }

    //Sends T as a parameter to the methid handleEvent defined in each of the Observers
    void notify(const T& t){
        for(typename std::vector<Observer<T>*>::iterator it = Observers.begin(); it != Observers.end(); ++it){
            (*it)->handleEvent(t);
        }
    }

    //Add an Observer that the Subject recognizes. If it is already recognized, throw an exception
    void addObserver(Observer<T>& o){
        for(typename std::vector<Observer<T>*>::iterator it = Observers.begin(); it != Observers.end(); ++it){
            if(*it == &o){
                throw ObserverAlreadyKnownToSubject();
            }
        }
        Observers.push_back(&o);
    }

    //Remove an Observer that the Subject recognizes. If it is not recognized, throw an exception
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
