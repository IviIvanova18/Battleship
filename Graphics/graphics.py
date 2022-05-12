from cgitb import reset
import sys
import tkinter as tk
from tkinter import *
from tkinter.font import Font
from traceback import print_tb
from board import Board, read_board_from_file, popupmsg
from boat import Boat
import numpy as np

import graphics
from setuptools import Command


def rules():

    text = """Battleships also known as Bimaru is a logic puzzle in a square grid of 10 x 10 \nsmall squares with simple rules and challenging solutions.
    The rules of Battleships are simple:\n
    You have to find the location of the battleships hidden in the grid.\n
    The armada includes one battleship four squares long, two cruisers three squares long, three destroyers two squares long, and four submarines one square in size. \n
    Each ship occupies a number of contiguous squares on the grid, arranged horizontally or vertically. \n
    The ships are placed so that no ship touches any other ship, not even diagonally. \n
    The numbers outside the grid show the number of cells occupied by battleships on that col/column."""


    rulesWindow = Toplevel(root, height=700, width=700)
    rulesWindow.title("Rules")
    rulesWindow.config(bg="#ff9130")
    rulesLabel = Label(rulesWindow, text=text,bg="#ff9130",font='Arial 9 bold')
    rulesLabel.place(relx=0.5, rely=0.5, anchor=CENTER)
    closeButton = Button(rulesLabel, text="Close", command=rulesWindow.destroy)
    closeButton.place(x=225, y=400)

matchBoatToSize= {
    0 : 1,
    1 : 1,
    2 : 1,
    3 : 1,
    4 : 2,
    5 : 2,
    6 : 2,
    7 : 3,
    8 : 3,
    9 : 4
}
        
def placeTile(rootName,x,y,movables,size):
    
    for size in range(size):
        movables.append(Boat(x+size*33,y,rootName,rootName))

def placeBoats(rootName,x,y,b):
    global movables
    movables = []
    prev = -1
    count = 0
    for boat in range(b.startBoat,b.lastBoat):
        size = matchBoatToSize[boat]
        if prev != size:
            count = 0
        placeTile(rootName,x+count*20,y,movables,size)
        count +=1
        y +=40

def solvePuzzle(b):
    boatPlacement = read_solution_game(b)
    if isinstance(boatPlacement, int):
        return
    for tile in movables:
        item = boatPlacement.pop()
        x,y = item
        tile.placeTileInGrid(x,y)

def split(word):
    return [char for char in word if char != '\n']

def read_solution_game(b):
    f = open(sys.argv[2],'r')
    line = f.readline()
    if isinstance(line, int) and int(line) == -1:
        popupmsg("UNSAT",'Error')
        f.close()
        return -1
    else :
        row=0
        listTiles = list()
        col = 0 
        x = split(line)
        for c in x:
            if int(c) == 1:
                tile = (col,row)
                listTiles.append(tile)
            col +=1
        row +=1
        for line in f.readlines():
            col=0
            x = split(line)
            for c in x:
                if int(c) == 1:
                    tile = (col,row)
                    listTiles.append(tile)
                col +=1
            row +=1
        f.close()
        return listTiles


def checkModel(b):
    listTile =list()
    grid = np.zeros((b.height, b.width))
    for tile in movables:
        tilePositionCoordinates = tile.tileCoordinates()
        x,y = tilePositionCoordinates
        flag = True 
        if (x<0 or x>= b.height or y< 0 or y>=b.width) and flag:
            popupmsg("Put all the boats in the grid!",'Error')
            flag = False
        else:
            grid[x][y]=1
        listTile.append(tilePositionCoordinates)
    solution = read_solution_game(b)
    if isinstance(solution, int):
        return
    solutiongrid = np.zeros((b.height, b.width))
    for cell in solution:
        i,j = cell
        solutiongrid[j][i]=1
    if np.array_equal(solutiongrid,grid):
        popupmsg("Congrats YOU WON!!!","win")
    else :
        popupmsg("Try again!","lose")

def resetPuzzle():
    for tile in movables:
        tile.returnToOrigin()

def board(): 
    global board
    root.title("Board") 
    root.geometry('700x500') 
    root.config(bg="#a1f0ea")
    b = Board(0,0,None,None,None,0,0)
    b= read_board_from_file(b)
    

    board = list()
    for col in range(b.height):
        line=list()
        for x in range(b.width):
            line.append(None)
        line.append(str(b.listRow[col]))
        board.append(line)
    b.listColumn.append(None)
    board.append(b.listColumn)
   
    for widget in root.winfo_children():
        widget.destroy()
    boardWidth = boardHeight= 35*(b.height+1)
    boardFrame = Frame(root)
    boardFrame.place(x=30, y=40, width=boardWidth, height = boardHeight)

    squares = list()
    for i in range(b.height+1):
        for j in range(b.width+1):
            frame = Frame(boardFrame, bd=0.5,background="#0f3536")
            frame.place(x=i*35,y = j*35,width=35, height=35)
            if (i, j) in b.listRocks:
                color = "#858a99"
            elif j == b.width or i == b.height:
                color = "#d3eff0"
            else :
                color =  "#74ccf4"
            square = Label(frame,text=board[i][j], bg =color, height=30, width=30)   
            squares.append(square)
            squares[-1].pack(fill=X)
            frame.lift()
    font = Font(family='Helvitica', size=10)
    checkButton = Button(root, text = "Check",bg='#366d91',
        fg='#ffffff',
        bd=0.5,
        font=font, 
        relief = RAISED,
        command= lambda : checkModel(b))
    checkButton.place(x=110,y=boardHeight+80,height = 20, width= 100)
    solveButton = Button(root, text = "Solve",bg='#366d91',
        fg='#ffffff',
        bd=0.5,
        font=font, 
        relief = RAISED,command= lambda :solvePuzzle(b))
    solveButton.place(x=260,y=boardHeight+80,height = 20, width= 100)
    solveButton = Button(root, text = "Reset",bg='#366d91',
        fg='#ffffff',
        bd=0.5,
        font=font, 
        relief = RAISED,command=resetPuzzle)
    solveButton.place(x=410,y=boardHeight+80,height = 20, width= 100)
    placeBoats(root,boardWidth+50,40,b)



root = Tk()
root.resizable(True, True) 
root.geometry('450x200') 
root.config(bg="#a1f0ea")
font = Font(family='Helvitica', size=15)
welcomeFont = Font(family="Helvetica",size = 17, weight="bold",
                slant="italic")
welcomeLabel = Label(root, text = "Welcome to Battleship logic game!",background="#a1f0ea",font=welcomeFont)
rulesButton = Button(root, text = "Rules of the game",
    bg='#366d91',
    fg='#ffffff',
    bd=0.5,
    font=font, 
    relief = RAISED, command = rules)


playButton = Button(root, text="Play",
    bg='#366d91',
    fg='#ffffff',
    bd=0.5,
    font=font, 
    relief = RAISED, 
    command = board
)


exitButton = Button(root, text = "Exit", 
    bg='#366d91',
    fg='#ffffff',
    bd=0.5,
    font=font, 
    relief = RAISED,  
    command = root.quit)

root.title("Battleship")

welcomeLabel.place(x = 40, y = 10)
rulesButton.place(x = 120, y = 50)
playButton.place(x = 170, y = 100)
exitButton.place(x = 172, y = 150)

root.mainloop()