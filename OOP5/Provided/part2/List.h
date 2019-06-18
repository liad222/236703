//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_LIST_H
#define OOP5_LIST_H


template<typename... TT>
struct List{};

template <typename T, typename... TT>
struct List<T, TT...>{
    typedef T head;
    typedef List<TT...> next;
    constexpr static int size = sizeof...(TT)+1 ;
};

template<>
struct List<>{
    constexpr static int size = 0;
};

#endif //OOP5_LIST_H
