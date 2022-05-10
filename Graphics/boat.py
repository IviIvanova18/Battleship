import tkinter as tk
from tkinter import *
# from board import Board, read_board_from_file
# import graphics
# from setuptools import Command


class Boat():
    def  __init__(self,x,y,root,frame):
        self.x = x
        self.y = y
        self.root = root
        self.Rframe = frame
        self.L = 4
        self.M = 3
        self.S = 2
        self.T = 1
        self.drawSection(32)
        self.movables = []
        self.boardWidth = 385
        self.boardHeight = 385
        self.boardX, self.boardY = 30, 30
        self.originX = x
        self.originY = y
       



    def drawSection(self,size):
        self.frame = Frame(self.Rframe,bd=1, relief = RIDGE,background="#10170e")
        self.frame.place(x=self.x, y=self.y, width=size, height=size)
        self.label = Label(self.frame, bd=1, relief=RAISED, height=size, width=size, bg="black")
        self.label.pack(padx=1,pady=1)
        self.frame.lift()
        self.label.bind('<ButtonPress-1>', self.startMoveTile)
        self.label.bind('<B1-Motion>', self.MoveTile)
        self.label.bind('<ButtonRelease-1>', self.placementCheck)

    def startMoveTile(self, event):
        """Gets the last position when the tile is clicked"""
        self.lastX = event.x_root
        self.lastY = event.y_root

    def MoveTile(self, event):
        """Moves the tile with the mouse; event is mouse motion"""
        self.root.update_idletasks()
        self.x += event.x_root - self.lastX
        self.y += event.y_root - self.lastY
        # The tile can't go of the board
        if self.x > 560: self.x = 560 
        if self.y > 650: self.y = 650
        if self.x < 0: self.x = 0
        if self.y < 0: self.y = 0

        self.lastX, self.lastY = event.x_root, event.y_root
        self.frame.place_configure(x=self.x, y=self.y)

        self.frame.lift()

    def placementCheck(self, *event):
        tilePosition = (self.x, self.y)
        #If the tile is touching the board, it goes to the nearest square 
        #If the tile is not touching the board, it goes to its origin point
        if not(self.isInBoard(tilePosition, (self.boardX, self.boardY),
                          self.frame.winfo_width(), self.frame.winfo_height(),
                          self.boardWidth, self.boardHeight)):
            self.returnToOrigin()
        else:
            self.goToBoard()


    def placeTileInGrid(self,x,y):
        self.x = x*35+30
        self.y = y*35+40
        self.frame.place_configure(x=x*35+30,y=y*35+40)

    def returnToOrigin(self):
        self.x = self.originX
        self.y = self.originY
        self.frame.place_configure(x=self.x, y=self.y)

    def tileCoordinates(self):
        return (int((self.y-40)/35)),(int((self.x-30)/35))

    def goToBoard(self):
        """Go to the nearest square on the board"""
        self.labels_positionList = {}
        for i in range(16):
            for j in range(16):
                self.labels_positionList[(i*35)+30, (j*35)+40] = (j, i)
        tilePosition = [self.x, self.y]
        for labelPosition in self.labels_positionList:
            if self.isInBoard(tilePosition, labelPosition, self.frame.winfo_width(), self.frame.winfo_height(),32, 32):
                if self.isEmpty(): 
                    self.frame.place_configure(x=labelPosition[0], y=labelPosition[1])
                    self.x = labelPosition[0]
                    self.y = labelPosition[1]
                    tilePosition = [self.x, self.y]
                    tilePositionCoordinates = self.tileCoordinates()

                else:
                    self.returnToOrigin()



    def isEmpty(self):
        #Checks if the place is empty so the tile can't be place in the same position as another tile
        #TO DO...
        return True


    def isInBoard(self, positionTile, positionBoard, widthTile, heightTile, widthBoard, heightBoard):
        #check if the tile is in the board, if it's in the board or touching in returns True
        if ((positionTile[0] > positionBoard[0]) or (positionTile[0] > (positionBoard[0] + widthTile))) and \
           ((positionTile[1] > positionBoard[1]) or (positionTile[1] > (positionBoard[1] + heightTile))) and \
           ((positionTile[0] < (positionBoard[0] + widthBoard)) and (positionTile[1] < (positionBoard[1] + heightBoard))):
            return True
        else:
            return False