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

#endif //OOP5_RUSHHOUR_H
