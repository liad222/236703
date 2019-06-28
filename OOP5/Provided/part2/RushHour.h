//
// Created by Liad on 22/06/2019.
//

#ifndef OOP5_RUSHHOUR_H
#define OOP5_RUSHHOUR_H

#include "MoveVehicle.h"


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


template<typename T>
struct CheckWin{};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length>
struct CheckWin<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> board;
    constexpr static int Xrow = FindVehicle<board, X, board::length-1>::row;
    constexpr static int Xcol = FindVehicle<board, X, board::length-1>::col;
    typedef typename GetCell<board, Xrow, Xcol>::Cell XCell;
    constexpr static int dif = board::width - Xcol - XCell::length;
    constexpr static bool result = CheckWinAux<board, Xrow, Xcol + XCell::length - 1, dif>::result;
};


template<typename T, typename U, int N>
struct CheckSolutionAux{};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, CellType MType, Direction MDir, int MAmount, typename... MM, int N>
struct CheckSolutionAux<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, List<Move<MType, MDir, MAmount>, MM...>, N> {
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    constexpr static int row = FindVehicle<b, MType, b::length-1>::row;
    constexpr static int col = FindVehicle<b, MType, b::length-1>::col;
    typedef typename MoveVehicle<b, row, col, MDir, MAmount>::board temp_board;
    typedef typename CheckSolutionAux<temp_board, typename List<Move<MType, MDir, MAmount>, MM...>::next, N - 1>::board board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, CellType MType, Direction MDir, int MAmount, typename... MM>
struct CheckSolutionAux<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, List<Move<MType, MDir, MAmount>, MM...>, 1> {
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    constexpr static int row = FindVehicle<b, MType, b::length-1>::row;
    constexpr static int col = FindVehicle<b, MType, b::length-1>::col;
    typedef typename MoveVehicle<b, row, col, MDir, MAmount>::board board;
};



template<typename T, typename U>
struct CheckSolution{};


template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, CellType MType, Direction MDir, int MAmount, typename... MM>
struct CheckSolution<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, List<Move<MType, MDir, MAmount>, MM...>>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    typedef typename CheckSolutionAux<b, List<Move<MType, MDir, MAmount>, MM...>, List<Move<MType, MDir, MAmount>, MM...>::size>::board final_board;
    constexpr static bool result = CheckWin<final_board>::result;
};

#endif //OOP5_RUSHHOUR_H
