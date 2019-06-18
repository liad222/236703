//
// Created by Liad on 18/06/2019.
//
#include "List.h"
#include <iostream>

template <int N>
struct Int{
    constexpr static int num = N;
};


template<typename>
struct Printer;



template<typename Head, typename... Tail>
struct Printer<List<Head, Tail...>>{
    static void print(std::ostream& output){
        Printer<Head>::print(output);
        output << " ";
        Printer<List<Tail...>>::print(output);
    }
};

template<>
struct Printer<List<>>{
    static void print(std::ostream& output){
        output << std::endl;
    }
};

template<int N>
struct Printer<Int<N>>{
    static void print(std::ostream& output){
        output << Int<N>::num;
    }
};
int main(){
    typedef List<Int<1>, Int<2>, Int<3>> list;
    list::head a;
    typedef typename list::next listTail;
    listTail b;
    //std::cout << list::size << std::endl;
    Printer<list>::print(std::cout);
    Printer<listTail>::print(std::cout);
    Printer<List<list::head>>::print(std::cout);
    return 0;
}
