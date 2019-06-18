import sys

def main():
    boardOutput = 'typedef GameBoard< List< \n\t'
    movesOutput = 'typedef List< \n\t'
    try:
        with open(sys.argv[1], 'r') as boardFile:
            boardArray = []

            for row in boardFile:
                if not row.strip():
                    continue
                if row.startswith("Moves"):
                    break
                
                boardArray.append([])
                rowSplit = list(row.replace(' ', '').rstrip())

                for cell in rowSplit:
                    boardArray[-1].append(cell)

            # Moves Processing
            first = True
            for line in boardFile:
                move = line.rstrip().split(' ')
                movesOutput += ', ' if not first else '' 
                first = False
                movesOutput += 'Move < ' + move[0] + ', ' + move[1] + ', ' + move[2] + ' > '

            for y in range(0, len(boardArray)):
                boardOutput += ' List < '
                for x in range(0, len(boardArray[y])):
                    cell = boardArray[y][x]
                    length = 1 if cell != '_' else 0
                    direction = 'RIGHT'
                    if cell != '_':
                        if y > 0:
                            ySearch = y - 1
                            while ySearch >= 0 and boardArray[ySearch][x] == cell:
                                direction = 'UP'
                                ySearch -= 1
                                length += 1
                        
                        if y < len(boardArray) - 1:
                            ySearch = y + 1
                            while ySearch < len(boardArray) and boardArray[ySearch][x] == cell:
                                direction = 'DOWN'
                                ySearch += 1
                                length += 1

                        if x > 0:
                            xSearch = x - 1
                            while xSearch >= 0 and boardArray[y][xSearch] == cell:
                                direction = 'LEFT'
                                xSearch -= 1
                                length += 1
                        
                        if x < len(boardArray[y]) - 1:
                            xSearch = x + 1
                            while xSearch < len(boardArray[y]) and boardArray[y][xSearch] == cell:
                                direction = 'RIGHT'
                                xSearch += 1
                                length += 1

                    boardOutput += ', ' if x != 0 else ''
                    boardOutput += 'BoardCell< ' + ('EMPTY' if cell == '_' else cell) + ' , ' + direction + ' , ' + str(length) + '>'
                boardOutput += ' >, \n\t' if y != len(boardArray) - 1 else ' >  \n'

    except IOError:
        print 'Could not open file ' + sys.argv[1]

    boardOutput += '\t > > gameBoard;\n'
    movesOutput += '\n\t > moves;\n'

    print boardOutput
    print movesOutput

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print 'Not enough arguments!'
        sys.exit(-1)
        
    main()