//
// Created by Liad on 28/06/2019.
//

#ifndef OOP5_OBSERVER_H
#define OOP5_OBSERVER_H

//The struct represents an Observer, which can handle events once triggered by the Subject.
template<typename T>
class Observer{
public:
    Observer(){}
    virtual void handleEvent(const T& t) = 0;
    virtual ~Observer() {};
};


#endif //OOP5_OBSERVER_H
