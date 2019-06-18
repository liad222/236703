//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"

template<typename... TT>
struct GameBoard{};

template<typename T, typename... TT>
struct GameBoard<List<List<T>, TT...>>{
    typedef List<List<T>, TT...> board;
    constexpr static int width = List<T>::size;
    constexpr static int length = sizeof...(TT)+1;

};

#endif //OOP5_GAMEBOARD_H
