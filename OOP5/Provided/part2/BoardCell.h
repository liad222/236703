//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H

#include "Direction.h"
#include "CellType.h"

template<CellType Type, Direction Dir, int Length>
struct BoardCell{
    constexpr static CellType type = Type;
    constexpr static Direction direction = Dir;
    constexpr static int length = Length;
};

#endif //OOP5_BOARDCELL_H
