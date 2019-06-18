//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_UTILITIES_H
#define OOP5_UTILITIES_H

template<bool g, typename T, typename F>
struct Conditional{
    typedef T value;
};

template<typename T, typename F>
struct Conditional<false, T, F>{
    typedef F value;
};


template<bool g, int T, int F>
struct ConditionalInteger{
    constexpr static int value = T;
};

template<int T, int F>
struct ConditionalInteger<false, T, F>{
    constexpr static int value = F;
};

#endif //OOP5_UTILITIES_H
