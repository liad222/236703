//
// Created by Liad on 18/06/2019.
//
#include "List.h"
#include "Utilities.h"
#include <iostream>
#include "MoveVehicle.h"

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
    typedef typename list::next listTail;
    std::cout << list::size << " first"<<std::endl;
    Printer<list>::print(std::cout);
    Printer<listTail>::print(std::cout);
    Printer<List<list::head>>::print(std::cout);
    typedef typename PrependList<Int<4>,list>::list newList;
    std::cout << newList::size << " second"<< std::endl;
    Printer<newList>::print(std::cout);
    GetAtIndex<0,list>::value a;
    GetAtIndex<2,list>::value b;
    typedef typename SetAtIndex<0, Int<5>, list>::list listA;
    std::cout << listA::size << " third"<< std::endl;
    Printer<listA>::print(std::cout);
    typedef typename SetAtIndex<2, Int<7>, list>::list listB;
    std::cout << listB::size << " fourth"<< std::endl;
    Printer<listB>::print(std::cout);

    int val = ConditionalInteger<(0 != 1), 0, 1>::value;
    std::cout << " fifth"<< std::endl << val << std::endl;
    val = ConditionalInteger<(0 == 1), 0, 1>::value;
    std::cout << " sixth"<< std::endl << val << std::endl;

    typedef typename Conditional<(0 != 1), Int<0>, Int<1>>:: value test1;
    typedef typename Conditional<(0 == 1), Int<0>, Int<1>>:: value test2;
    test1 c;
    test2 d;
    int amount = Move<X, UP, 1>::amount;
    std::cout << " seventh"<< std::endl << amount << std::endl;



    std::cout << " -------------------------------------------------"<< std::endl;

    typedef GameBoard< List<
            List < BoardCell<O, DOWN, 3>     , BoardCell<A, RIGHT, 2>    , BoardCell<A, RIGHT, 2>, BoardCell<EMPTY, UP, 3>, BoardCell< B , DOWN , 2>,  BoardCell< EMPTY, RIGHT , 0>>,
            List < BoardCell<O, DOWN, 3>     , BoardCell<C,    UP, 2>    , BoardCell<D, DOWN,  2>, BoardCell<EMPTY, UP, 3>, BoardCell< B , DOWN ,2 >,  BoardCell< P, UP ,        3>>,
            List < BoardCell<O, DOWN, 3>     , BoardCell<C,    UP, 2>    , BoardCell<D, DOWN,  2>, BoardCell<X,  RIGHT, 2>, BoardCell< X,  RIGHT, 2>,  BoardCell< P ,    UP,     3>>,
            List < BoardCell<Q, RIGHT,3>     , BoardCell<Q, RIGHT, 3>    , BoardCell<Q, RIGHT, 3>, BoardCell<E ,  UP  , 2>, BoardCell< EMPTY, UP, 0>,  BoardCell< P,     UP ,    3>>,
            List < BoardCell<EMPTY, RIGHT,0> , BoardCell<EMPTY, DOWN , 2>, BoardCell<F, UP ,   2>, BoardCell<E,   UP  , 2>, BoardCell< K, RIGHT , 2>,  BoardCell< K , RIGHT ,    2>>,
            List < BoardCell<H, RIGHT, 2>    , BoardCell<H, RIGHT, 2>    , BoardCell<F, UP    ,2>, BoardCell<I, RIGHT , 2>, BoardCell< I, RIGHT , 2>,  BoardCell< EMPTY, RIGHT , 2>>
    > > gameBoard;
    int Orow = FindVehicle<gameBoard, I, gameBoard::length-1>::row;
    int Ocol = FindVehicle<gameBoard, I, gameBoard::length-1>::col;

    std::cout << Orow << std::endl << Ocol << std::endl;

    std::cout << " GetCell-----------------------------------------------------"<< std::endl;
    CellType type = GetCell<gameBoard, 1, 3>::Cell::type;
    Direction dir = GetCell<gameBoard, 1, 3>::Cell::direction;
    int len = GetCell<gameBoard, 1, 3>::Cell::length;

    std::cout << type << std::endl << dir << std::endl<< len << std::endl;

    return 0;
}
