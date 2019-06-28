//
// Created by Liad on 28/06/2019.
//

#ifndef OOP5_OBSERVER_H
#define OOP5_OBSERVER_H

template<typename T>
class Observer{
public:
    Observer(){}
    virtual void handleEvent(const T& t) = 0;
    bool operator==(const Observer<T>& t){
        return this == t;
    }
};


#endif //OOP5_OBSERVER_H
