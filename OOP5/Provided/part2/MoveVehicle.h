//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "GameBoard.h"
#include "TransposeList.h"

template<typename T, CellType Type,int N>
struct FindInList{};

template<typename... TT, CellType LType, CellType Type, Direction Dir, int Length, int N>
struct FindInList<List<BoardCell<Type, Dir, Length>, TT...>, LType, N> {
    static_assert(LType != EMPTY, "Can't find EMPTY!!");
    constexpr static int previous =
            ConditionalInteger<(FindInList<List<BoardCell<Type, Dir, Length>, TT...>, LType, N-1>::index != -1),
                    FindInList<List<BoardCell<Type, Dir, Length>, TT...>, LType, N-1>::index, -1>::value;
    constexpr static int current =ConditionalInteger<
            (GetAtIndex<N, List<BoardCell<Type, Dir, Length>, TT...>>::value::type == LType), N, -1>::value;
    constexpr static int index = ConditionalInteger<(previous != -1), previous, current>::value;
};

template<typename... TT, CellType LType, CellType Type, Direction Dir, int Length>
struct FindInList<List<BoardCell<Type, Dir, Length>, TT...>, LType, 0> {
    static_assert(LType != EMPTY, "Can't find EMPTY!!");
    constexpr static int index = ConditionalInteger<
            (GetAtIndex<0, List<BoardCell<Type, Dir, Length>, TT...>>::value::type == LType), 0, -1>::value;
};




template<CellType Type, Direction Dir, int Amount>
struct Move{
    static_assert(Type != EMPTY, "Move's Type can't be EMPTY!!");
    constexpr static CellType type = Type;
    constexpr static Direction direction = Dir;
    constexpr static int amount = Amount;
};


template<typename U, CellType Type, int N>
struct FindVehicle{};

template<typename... UU, typename... TT, CellType LType, CellType Type, Direction Dir, int Length, int N>
struct FindVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, LType, N>{
    static_assert(LType != EMPTY, "Can't find EMPTY!!");
    constexpr static int previous_row = ConditionalInteger<(FindVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, LType, N-1>::row != -1),
            FindVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, LType, N-1>::row, -1>::value;
    constexpr static int previous_col = ConditionalInteger<(FindVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, LType, N-1>::col != -1),
            FindVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, LType, N-1>::col, -1>::value;
    constexpr static int current_col = ConditionalInteger<
            (FindInList<typename GetAtIndex<N, typename GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::board>::value, LType, (GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::width-1)>::index != -1),
            FindInList<typename GetAtIndex<N, typename GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::board>::value, LType, (GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::width-1)>::index, -1>::value;
    constexpr static int current_row = ConditionalInteger<(current_col != -1), N, -1>::value;
    constexpr static int row = ConditionalInteger<(previous_row != -1), previous_row, current_row>::value;
    constexpr static int col = ConditionalInteger<(previous_col != -1), previous_col, current_col>::value;
};

template<typename... UU, typename... TT, CellType LType,CellType Type, Direction Dir, int Length>
struct FindVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, LType, 0>{
    static_assert(LType != EMPTY, "Can't find EMPTY!!");
    constexpr static int col = ConditionalInteger<
            (FindInList<typename GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::board::head, LType, (GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::width-1)>::index != -1),
            FindInList<typename GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::board::head, LType, (GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::width-1)>::index, -1>::value;
    constexpr static int row = ConditionalInteger<(col != -1), 0, -1>::value;
};

template<typename T, int row, int col>
struct GetCell{};


template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int row, int col>
struct GetCell<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, row, col>{
    typedef typename GetAtIndex<row, typename GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::board>::value Row;
    typedef typename GetAtIndex<col, Row>::value Cell;
};

template<typename T, int R, int C, Direction D>
struct MoveByOne{};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C>
struct MoveByOne<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, RIGHT> {
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    static_assert((R >= 0 && C >= 0 &&
                   R < b::length &&
                   C < b::width), "Out of Bounds!");
    typedef typename GetCell<b, R, C>::Cell cell;
    static_assert(cell::type != EMPTY, "Can't move EMPTY vehicle");
    //static_assert(cell::direction == RIGHT || cell::direction == LEFT, "Expected to move RIGHT");
    constexpr static int new_col = cell::length + C;
    static_assert(GetCell<b, R, new_col>::Cell::type == EMPTY, "Path is not clear!");
    typedef typename GetAtIndex<R, typename b::board>::value current_row;
    typedef typename SetAtIndex<new_col, cell, current_row>::list temp_row;
    typedef typename SetAtIndex<C, BoardCell<EMPTY, UP, 3>, temp_row>::list new_row;
    typedef typename SetAtIndex<R, new_row, typename b::board>::list new_board_list;
    typedef GameBoard<new_board_list> new_board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C>
struct MoveByOne<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, LEFT> {
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    static_assert((R >= 0 && C >= 0 &&
                   R < b::length &&
                   C < b::width), "Out of Bounds!");
    typedef typename GetCell<b, R, C>::Cell cell;
    static_assert(cell::type != EMPTY, "Can't move EMPTY vehicle");
    //static_assert(cell::direction == RIGHT || cell::direction == LEFT, "Expected to move LEFT");
    constexpr static int last_col = cell::length + C - 1;
    constexpr static int new_col = C - 1;
    static_assert(GetCell<b, R, new_col>::Cell::type == EMPTY, "Path is not clear!");
    typedef typename GetAtIndex<R, typename b::board>::value current_row;
    typedef typename SetAtIndex<new_col, cell, current_row>::list temp_row;
    typedef typename SetAtIndex<last_col, BoardCell<EMPTY, UP, 3>, temp_row>::list new_row;
    typedef typename SetAtIndex<R, new_row, typename b::board>::list new_board_list;
    typedef GameBoard<new_board_list> new_board;
};



template<typename T, int R, int C, Direction D, int A>
struct MoveVehicle{};


template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C, int A>
struct MoveVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, RIGHT, A>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    static_assert((R >= 0 && C >= 0 &&
                    R < b::length &&
                    C < b::width), "Out of Bounds!");
    typedef typename GetCell<b, R, C>::Cell cell;
    static_assert(cell::type != EMPTY, "Can't move EMPTY vehicle");
    //static_assert(cell::direction == RIGHT || cell::direction == LEFT, "Expected to move RIGHT");
    typedef typename MoveVehicle<typename MoveByOne<b, R, C, RIGHT>::new_board, R, C+1, RIGHT, A-1>::board board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C, int A>
struct MoveVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, LEFT, A>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    static_assert((R >= 0 && C >= 0 &&
                   R < b::length &&
                   C < b::width), "Out of Bounds!");
    typedef typename GetCell<b, R, C>::Cell cell;
    static_assert(cell::type != EMPTY, "Can't move EMPTY vehicle");
    //static_assert(cell::direction == RIGHT || cell::direction == LEFT, "Expected to move LEFT");
    typedef typename MoveVehicle<typename MoveByOne<b, R, C, LEFT>::new_board, R, C-1, LEFT, A-1>::board board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C>
struct MoveVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, RIGHT, 0>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C>
struct MoveVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, LEFT, 0>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C, int A>
struct MoveVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, DOWN, A>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    static_assert((R >= 0 && C >= 0 &&
                   R < b::length &&
                   C < b::width), "Out of Bounds!");
    typedef typename GetCell<b, R, C>::Cell cell;
    static_assert(cell::type != EMPTY, "Can't move EMPTY vehicle");
    static_assert(cell::direction == UP || cell::direction == DOWN, "Expected to move DOWN");
    typedef typename Transpose<typename b::board>::matrix transposed_lists;
    typedef GameBoard<transposed_lists> transposed_board;
    typedef typename MoveVehicle<transposed_board, C, R, RIGHT, A>::board temp_board;
    typedef typename Transpose<typename temp_board::board>::matrix final_lists;
    typedef GameBoard<final_lists> board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C, int A>
struct MoveVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, UP, A>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    static_assert((R >= 0 && C >= 0 &&
                   R < b::length &&
                   C < b::width), "Out of Bounds!");
    typedef typename GetCell<b, R, C>::Cell cell;
    static_assert(cell::type != EMPTY, "Can't move EMPTY vehicle");
    static_assert(cell::direction == UP || cell::direction == DOWN, "Expected to move UP");
    typedef typename Transpose<typename b::board>::matrix transposed_lists;
    typedef GameBoard<transposed_lists> transposed_board;
    typedef typename MoveVehicle<transposed_board, C, R, LEFT, A>::board temp_board;
    typedef typename Transpose<typename temp_board::board>::matrix final_lists;
    typedef GameBoard<final_lists> board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C>
struct MoveVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, UP, 0>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C>
struct MoveVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, DOWN, 0>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> board;
};

#endif //OOP5_MOVEVEHICLE_H
