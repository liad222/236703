//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"

//The struct represents the gameboard, which is a list of lists of BoardCells
template<typename... TT>
struct GameBoard{};

template<typename... UU, typename... TT>
struct GameBoard<List<List<UU...>, TT...>>{
    typedef List<List<UU...>, TT...> board;
    constexpr static int width = List<UU...>::size;
    constexpr static int length = sizeof...(TT)+1;

};

#endif //OOP5_GAMEBOARD_H
