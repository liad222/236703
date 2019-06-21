//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"


template<typename T, CellType Type,int N>
struct FindInList{};

template<typename... TT, CellType Type, Direction Dir, int Length, int N>
struct FindInList<List<BoardCell<Type, Dir, Length>, TT...>, Type, N> {
    constexpr static int previous =
            ConditionalInteger<(FindInList<List<BoardCell<Type, Dir, Length>, TT...>, Type, N-1>::index != -1),
                    FindInList<List<BoardCell<Type, Dir, Length>, TT...>, Type, N-1>::index, -1>::value;
    constexpr static int current = ConditionalInteger<
            (GetAtIndex<N, List<BoardCell<Type, Dir, Length>, TT...>>::value::type == Type), N, -1>::value;
    constexpr static int index = ConditionalInteger<(previous != -1), previous, current>::value;
};

template<typename... TT, CellType Type, Direction Dir, int Length>
struct FindInList<List<BoardCell<Type, Dir, Length>, TT...>, Type, 0> {
    constexpr static int index = ConditionalInteger<
            (GetAtIndex<0, List<BoardCell<Type, Dir, Length>, TT...>>::value::type == Type), 0, -1>::value;
};




template<CellType Type, Direction Dir, int Amount>
struct Move{
    static_assert(Type != EMPTY, "Move's Type can't be EMPTY!!");
    CellType type = Type;
    Direction direction = Dir;
    constexpr static int amount = Amount;
};


template<typename U, CellType Type, int N>
struct FindVehicle{};

template<typename T, typename... TT, CellType Type, int N>
struct FindVehicle<GameBoard<List<List<T>, TT...>>, Type, N>{
    static_assert(Type != EMPTY, "Can't find EMPTY!!");
    constexpr static int previous_row = ConditionalInteger<(FindVehicle<GameBoard<List<TT...>>, Type, N-1>::row != -1),
            FindVehicle<GameBoard<List<TT...>>, Type, N-1>::row, -1>::value;
    constexpr static int previous_col = FindVehicle<GameBoard<List<TT...>>, Type, N-1>::col;
    constexpr static int current_col = ConditionalInteger<
            (FindInList<typename GetAtIndex<N, GameBoard<List<List<T>, TT...>>>::value, Type, GameBoard<List<List<T>, TT...>>::width>::index != -1),
            FindInList<typename GetAtIndex<N, GameBoard<List<List<T>, TT...>>>::value, Type, GameBoard<List<List<T>, TT...>>::width>::index, -1>::value;
    constexpr static int current_row = ConditionalInteger<(current_col != -1), 0, -1>::value;
    constexpr static int row = ConditionalInteger<(previous_row != -1), previous_row, current_row>::value;
    constexpr static int col = ConditionalInteger<(previous_row != -1), previous_col, current_col>::value;
};

template<typename T, typename... TT, CellType Type>
struct FindVehicle<GameBoard<List<List<T>, TT...>>, Type, 0>{
    static_assert(Type != EMPTY, "Can't find EMPTY!!");
    constexpr static int col = ConditionalInteger<
            (FindInList<typename GetAtIndex<0, GameBoard<List<List<T>, TT...>>>::value, Type, GameBoard<List<List<T>, TT...>>::width>::index != -1),
            FindInList<typename GetAtIndex<0, GameBoard<List<List<T>, TT...>>>::value, Type, GameBoard<List<List<T>, TT...>>::width>::index, -1>::value;
    constexpr static int row = ConditionalInteger<(col != -1), 0, -1>::value;
};


#endif //OOP5_MOVEVEHICLE_H
