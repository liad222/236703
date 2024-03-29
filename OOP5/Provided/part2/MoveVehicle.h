//
// Created by Liad on 18/06/2019.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "GameBoard.h"
#include "TransposeList.h"

//The struct receives a list of BoardCells, CellType LType and an index in the list,
//and saves in the field "index" the first index in the list that has a BoardCell with the type LType.
//If a previous index had the required Type of vehicle then "index" will be the previous "index",
//otherwise, if the current index has the required Type of vehicle, "index" will be the current index.
//In other words - "index" is the leftmost position of an LType CellType in the list.
//If an LType CellType doesn't exist in the list, "index" is set to -1.
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

//The struct receives a list of BoardCells of size 1, CellType LType and the index 0,
//and saves in the field "index" 0 if the first index of the list has the required Type of vehicle, -1 otherwise.
template<typename... TT, CellType LType, CellType Type, Direction Dir, int Length>
struct FindInList<List<BoardCell<Type, Dir, Length>, TT...>, LType, 0> {
    static_assert(LType != EMPTY, "Can't find EMPTY!!");
    constexpr static int index = ConditionalInteger<
            (GetAtIndex<0, List<BoardCell<Type, Dir, Length>, TT...>>::value::type == LType), 0, -1>::value;
};


//The struct represents a move in the game - moving car Type #Amount cells in direction Dir.
template<CellType Type, Direction Dir, int Amount>
struct Move{
    static_assert(Type != EMPTY, "Move's Type can't be EMPTY!!");
    constexpr static CellType type = Type;
    constexpr static Direction direction = Dir;
    constexpr static int amount = Amount;
};


//the struct receives gameboard, CellType Ltype and the number of lines in the board (minus 1 because the first line is line 0),
//and saves in the fields "row" and "col" the "highest" row and the "leftmost" column that has the required Type of vehicle.
//If a previous row/col had the required Type of vehicle then row and col will be the previous row and col found.
//Otherwise, if the current row and col have the required Type of vehicle, row and col will be the current row and col.
//If the Vehicle of type Ltype is not found in the board, row and col are set to -1.
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

//The struct receives a gameboard, CellType Ltype and 0,
//and saves in the fields "row" and "col" the "leftmost" column that
//has the required Type of vehicle if the first row of the gameboard has the required Type of vehicle, -1 otherwise.
template<typename... UU, typename... TT, CellType LType,CellType Type, Direction Dir, int Length>
struct FindVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, LType, 0>{
    static_assert(LType != EMPTY, "Can't find EMPTY!!");
    constexpr static int col = ConditionalInteger<
            (FindInList<typename GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::board::head, LType, (GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::width-1)>::index != -1),
            FindInList<typename GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::board::head, LType, (GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::width-1)>::index, -1>::value;
    constexpr static int row = ConditionalInteger<(col != -1), 0, -1>::value;
};


//The struct receives a gameboard, row and col indexes and returns the BoardCell in line number row and index number col of the gameboard.
template<typename T, int row, int col>
struct GetCell{};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int row, int col>
struct GetCell<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, row, col>{
    typedef typename GetAtIndex<row, typename GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>::board>::value Row;
    typedef typename GetAtIndex<col, Row>::value Cell;
};


//The struct receives a gameboard, indexes R and C and Direction (Right or Left)
//and moves the car in line number R and index number C of the gameboard, one cell to the required Direction.
//Type new_board describes the gameboard after the move is made.
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
    static_assert(cell::direction == RIGHT || cell::direction == LEFT, "Expected to move RIGHT");
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
    static_assert(cell::direction == RIGHT || cell::direction == LEFT, "Expected to move LEFT");
    constexpr static int last_col = cell::length + C - 1;
    constexpr static int new_col = C - 1;
    static_assert(GetCell<b, R, new_col>::Cell::type == EMPTY, "Path is not clear!");
    typedef typename GetAtIndex<R, typename b::board>::value current_row;
    typedef typename SetAtIndex<new_col, cell, current_row>::list temp_row;
    typedef typename SetAtIndex<last_col, BoardCell<EMPTY, UP, 3>, temp_row>::list new_row;
    typedef typename SetAtIndex<R, new_row, typename b::board>::list new_board_list;
    typedef GameBoard<new_board_list> new_board;
};


//The struct receives a gameboard, indexes R and C, direction NDir and int CLen
//and changes the direction of the car in line number R, index number C to be NDir.
//CLen is the number of cells left to be changed.
template<typename T, int R, int C, Direction NDir, int CLen>
struct ChangeCells{};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C, Direction NDir, int CLen>
struct ChangeCells<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, NDir, CLen>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    typedef typename GetCell<b, R, C>::Cell cell;
    typedef typename GetAtIndex<R, typename b::board>::value current_row;
    typedef typename SetAtIndex<C, BoardCell<cell::type, NDir, cell::length>, current_row>::list new_row;
    typedef typename SetAtIndex<R, new_row, typename b::board>::list new_board_list;
    typedef GameBoard<new_board_list> new_board;
    typedef typename ChangeCells<new_board, R, C + 1, NDir, CLen - 1>::board board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, Direction NDir, int C>
struct ChangeCells<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, NDir, 1>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    typedef typename GetCell<b, R, C>::Cell cell;
    typedef typename GetAtIndex<R, typename b::board>::value current_row;
    typedef typename SetAtIndex<C, BoardCell<cell::type, NDir, cell::length>, current_row>::list new_row;
    typedef typename SetAtIndex<R, new_row, typename b::board>::list new_board_list;
    typedef GameBoard<new_board_list> board;
};


//The struct that moves a car the required number of cells and in the required direction according to a move.
//If the required direction is right or left, the struct creates a new line with the car in her new position (if possible) with the help of struct MoveByOne.
//If the required direction is up or down, the struct does transpose to the gameboard,
//changes the direction of the cells of the car accordingly, moves the car right or left respectivly,
//changes the direction of the cells to the original direction and transposes back the gameboard.
//Type board describes the gameboard after the move is made.
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
    static_assert(cell::direction == RIGHT || cell::direction == LEFT, "Expected to move RIGHT");
    //Finding the uppermost leftmost cell of the vehicle to be moved
    constexpr static int true_row = FindVehicle<b, cell::type, b::length - 1>::row;
    constexpr static int true_col = FindVehicle<b, cell::type, b::length - 1 >::col;
    static_assert((true_row != -1 && true_col != -1), "Vehicle not on board!");
    typedef typename MoveVehicle<typename MoveByOne<b, true_row, true_col, RIGHT>::new_board, true_row, true_col +1 , RIGHT, A-1>::board board;
};

template<typename... UU, typename... TT,CellType Type, Direction Dir, int Length, int R, int C, int A>
struct MoveVehicle<GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>>, R, C, LEFT, A>{
    typedef GameBoard<List<List<BoardCell<Type, Dir, Length>,UU...>, TT...>> b;
    static_assert((R >= 0 && C >= 0 &&
                   R < b::length &&
                   C < b::width), "Out of Bounds!");
    typedef typename GetCell<b, R, C>::Cell cell;
    static_assert(cell::type != EMPTY, "Can't move EMPTY vehicle");
    static_assert(cell::direction == RIGHT || cell::direction == LEFT, "Expected to move LEFT");
    //Finding the uppermost leftmost cell of the vehicle to be moved
    constexpr static int true_row = FindVehicle<b, cell::type, b::length - 1>::row;
    constexpr static int true_col = FindVehicle<b, cell::type, b::length - 1>::col;
    static_assert((true_row != -1 && true_col != -1), "Vehicle not on board!");
    typedef typename MoveVehicle<typename MoveByOne<b, true_row, true_col, LEFT>::new_board, true_row, true_col - 1, LEFT, A-1>::board board;
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
    //Finding the uppermost leftmost cell of the vehicle to be moved
    constexpr static int true_row = FindVehicle<b, cell::type, b::length - 1>::row;
    constexpr static int true_col = FindVehicle<b, cell::type, b::length - 1>::col;
    static_assert((true_row != -1 && true_col != -1), "Vehicle not on board!");
    typedef typename Transpose<typename b::board>::matrix transposed_lists;
    typedef GameBoard<transposed_lists> transposed_board;
    constexpr static Direction Orignal_dir = cell::direction;
    typedef typename ChangeCells<transposed_board, true_col, true_row, RIGHT, cell::length>::board changed_board;
    typedef typename MoveVehicle<changed_board, true_col, true_row, RIGHT, A>::board temp_board;
    typedef typename ChangeCells<temp_board, true_col, true_row+A, Orignal_dir, cell::length>::board final_board;
    typedef typename Transpose<typename final_board::board>::matrix final_lists;
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
    //Finding the uppermost leftmost cell of the vehicle to be moved
    constexpr static int true_row = FindVehicle<b, cell::type, b::length - 1>::row;
    constexpr static int true_col = FindVehicle<b, cell::type, b::length - 1>::col;
    static_assert((true_row != -1 && true_col != -1), "Vehicle not on board!");
    typedef typename Transpose<typename b::board>::matrix transposed_lists;
    typedef GameBoard<transposed_lists> transposed_board;
    constexpr static Direction Orignal_dir = cell::direction;
    typedef typename ChangeCells<transposed_board, true_col, true_row, RIGHT, (cell::length)>::board changed_board;
    typedef typename MoveVehicle<changed_board, true_col, true_row, LEFT, A>::board temp_board;
    typedef typename ChangeCells<temp_board, true_col, true_row-A, Orignal_dir, (cell::length)>::board final_board;
    typedef typename Transpose<typename final_board::board>::matrix final_lists;
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
