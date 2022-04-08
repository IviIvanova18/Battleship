import sys

class Board :
    def  __init__(self,height,width,listColumn,listRow,list_rocks):
        self.listRocks = list_rocks
        self.height = height
        self.width = width
        self.listColumn = listColumn
        self.listRow = listRow


def read_board_from_file(board):
    f = open(sys.argv[1],'r')
    h, w = [int(x) for x in next(f).split()]
    list_cols = [int(ch) for ch in f.readline() if ch != '\n' if ch != ' ' ]
    list_rows = [int(ch) for ch in f.readline() if ch != '\n' if ch != ' ' ]
    list_rocks = list()
    for line in f.readlines():
        x, y = [int(x) for x in line.split()]
        rock = (x,y)
        list_rocks.append(rock)
    f.close()
    board = Board(h,w,list_cols,list_rows,list_rocks)
    return board




# b = Board()
# b= read_board_from_file(b)
# n,m=b.height,b.width
# board = list()
# for row in range(b.height):
#     line=list()
#     for x in range(b.width):
#         line.append('-')
#     line.append(str(b.listRow[row]))
#     board.append(line)
# board.append(b.listColumn)