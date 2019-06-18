//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "CellType.h"
#include "Direction.h"

template<CellType Type, Direction Dir, int Amount>
struct Move{
    static_assert(Type != EMPTY, "Move's Type can't be EMPTY!!");
    CellType type = Type;
    Direction direction = Dir;
    constexpr static int amount = Amount;
};


#endif //OOP5_MOVEVEHICLE_H
