//
// Created by Liad on 22/06/2019.
//

#ifndef OOP5_RUSHHOUR_H
#define OOP5_RUSHHOUR_H

#include "MoveVehicle.h"

//The struct receives a gameboard, indexes R and C, and the number of cells left
//from the end of the red car to the exit. The field "result" is set to true if the red car's path
//to the exit is empty, and to false if the path is blocked by another car. The struct performs
//this check one cell at a time.
template<typename T, int R, int C, int Dif>
struct CheckWinAux{};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C, int Dif>
struct CheckWinAux<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, Dif>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> board;
    typedef typename GetCell<board, R, C+1>::Cell nextCell;
    constexpr static bool result = (nextCell::type == EMPTY)?(CheckWinAux<board, R, C+1, Dif-1>::result):false;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C>
struct CheckWinAux<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, 0>{
    constexpr static bool result = true;
};

//The struct receives a gameboard, and checks if it is solved, meaning the the red car's path
//to the exit is empty. The field "result" is set to true if the path is clear, and to false
//if not. The struct uses the struct CheckWinAux to do so. 
template<typename T>
struct CheckWin{};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length>
struct CheckWin<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> board;
    //Find the location of the red car of type X
    constexpr static int Xrow = FindVehicle<board, X, board::length-1>::row;
    constexpr static int Xcol = FindVehicle<board, X, board::length-1>::col;
    typedef typename GetCell<board, Xrow, Xcol>::Cell XCell;
    constexpr static int dif = board::width - Xcol - XCell::length;
    //Use CheckWinAux with the number of cells between the exis and the end of the red car
    constexpr static bool result = CheckWinAux<board, Xrow, Xcol + XCell::length - 1, dif>::result;
};

//The struct receives a gamebord and a list of moves, and performs them one by one (by performing the
//first move, and then recursivly using this struct with the rest of the moves list).
////Type board describes the gameboard after the moves are made.
template<typename T, typename U, int N>
struct CheckSolutionAux{};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, CellType MType, Direction MDir, int MAmount, typename... MM, int N>
struct CheckSolutionAux<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, List<Move<MType, MDir, MAmount>, MM...>, N> {
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    //Find the location of the car to be moved
    constexpr static int row = FindVehicle<b, MType, b::length-1>::row;
    constexpr static int col = FindVehicle<b, MType, b::length-1>::col;
    static_assert((row != -1 && col != -1), "Vehicle not on board!");
    //Perform the first move
    typedef typename MoveVehicle<b, row, col, MDir, MAmount>::board temp_board;
    //Perform the rest of the moves
    typedef typename CheckSolutionAux<temp_board, typename List<Move<MType, MDir, MAmount>, MM...>::next, N - 1>::board board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, CellType MType, Direction MDir, int MAmount, typename... MM>
struct CheckSolutionAux<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, List<Move<MType, MDir, MAmount>, MM...>, 1> {
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    //Find the location of the car to be moved
    constexpr static int row = FindVehicle<b, MType, b::length-1>::row;
    constexpr static int col = FindVehicle<b, MType, b::length-1>::col;
    static_assert((row != -1 && col != -1), "Vehicle not on board!");
    typedef typename MoveVehicle<b, row, col, MDir, MAmount>::board board;
};

//The struct receives a gameboard and a list of moves, and preforms them one by one usint the struct
//CheckSolutionAux. The field "result" is set to true if the series of moves solved the gameboard,
//and to false if not, using the struct CheckWin.
template<typename T, typename U>
struct CheckSolution{};


template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, CellType MType, Direction MDir, int MAmount, typename... MM>
struct CheckSolution<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, List<Move<MType, MDir, MAmount>, MM...>>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    typedef typename CheckSolutionAux<b, List<Move<MType, MDir, MAmount>, MM...>, List<Move<MType, MDir, MAmount>, MM...>::size>::board final_board;
    constexpr static bool result = CheckWin<final_board>::result;
};

#endif //OOP5_RUSHHOUR_H
