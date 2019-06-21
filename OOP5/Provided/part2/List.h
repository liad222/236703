//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_LIST_H
#define OOP5_LIST_H

#include "Utilities.h"


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

template<typename T, typename U>
struct PrependList{};

template<typename T, typename... TT>
struct PrependList<T, List<TT...>>{
    typedef List<T,TT...> list;
};

template<typename T>
struct PrependList<T,List<>>{
    typedef List<T> list;
};


template<int N, typename T>
struct GetAtIndex{};

template<int N, typename T, typename... TT>
struct GetAtIndex<N, List<T,TT...>>{
    typedef typename GetAtIndex<N-1, List<TT...>>::value value;
};

template<typename T, typename... TT>
struct GetAtIndex<0,List<T, TT...>>{
    typedef T value;
};



template<int N, typename U, typename T>
struct SetAtIndex{};

template<int N, typename U, typename T, typename... TT>
struct SetAtIndex<N, U, List<T,TT...>>{
    typedef typename PrependList<T, typename SetAtIndex<N-1, U, List<TT...>>::list>::list list;
};

template<typename U, typename T, typename... TT>
struct SetAtIndex<0, U, List<T, TT...>>{
    typedef typename PrependList<U,List<TT...>>::list list;
};



#endif //OOP5_LIST_H
