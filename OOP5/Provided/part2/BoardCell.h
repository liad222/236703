//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H

#include "Direction.h"
#include "CellType.h"

//The struct represents a cell in the gameboard - either empty or with car Type, placed in
//direction Dir, with a certain length
template<CellType Type, Direction Dir, int Length>
struct BoardCell{
    constexpr static CellType type = Type;
    constexpr static Direction direction = Dir;
    constexpr static int length = Length;
};

#endif //OOP5_BOARDCELL_H
