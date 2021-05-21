from game import *
from matrix import *
from tetris import *
import logging
##################################################
### ColorDecorator for Tetris Class
##################################################

class ColorDecorator(Tetris,Game):
    setOfCBlockObjects=0
    def initCBlocks(self,setOfBlockObjects):
        super(ColorDecorator,self).__init__(self.game.iScreenDy,self.game.iScreenDx)
       # Tetris.init(setOfBlockObjects)
        ColorDecorator.setOfCBlockObjects=[[0]* Tetris.nBlockDegrees for _ in range(Tetris.nBlockTypes)]

        for i in range(Tetris.nBlockTypes):
            for j in range(Tetris.nBlockDegrees):
                obj=Matrix(setOfBlockObjects[i][j])
                obj.mulc(i+1)
                ColorDecorator.setOfCBlockObjects[i][j]=obj
            ### initialize self.setOfCBlockObjects
        return
		
    def __init__(self, game):
        self.game = game  #tetris객체가져옴
        self.initCBlocks(game.setOfBlockObjects)
        arrayScreen = game.createArrayScreen()
        self.iCScreen = Matrix(arrayScreen)
        self.oCScreen = Matrix(self.iCScreen)
       # self.justStarted=True
        return
	
    def accept(self, key):
        if key>='0' and key<='6':
            if self.justStarted==False:
                self.deleteFullLines()
            self.iCScreen=Matrix(self.oCScreen)

        state=Tetris.accept(self,key)

        self.currCBlk=ColorDecorator.setOfCBlockObjects[self.idxBlockType][self.idxBlockDegree]
        tempBlk=self.iCScreen.clip(self.top,self.left,self.top+self.currCBlk.get_dy(),self.left+self.currCBlk.get_dx())
        tempBlk=tempBlk+self.currCBlk

        self.oCScreen=Matrix(self.iCScreen)
        self.oCScreen.paste(tempBlk, self.top, self.left)

        return state
	
    def getScreen(self):
        return self.oCScreen

    def deleteFullLines(self):
        nDeleted=0
        nScanned=Tetris.deleteFullLines(self)


        zero=Matrix([[0 for x in range(0, (self.iScreenDx-2*Tetris.iScreenDw))]])
        for y in range(nScanned-1, -1, -1):
            cy=self.top+y+nDeleted
            line=self.oCScreen.clip(cy,0,cy+1,self.oCScreen.get_dx())
            line=line.binary()
            if line.sum()==self.oCScreen.get_dx():
                temp=self.oCScreen.clip(0,0,cy,self.oCScreen.get_dx())
                self.oCScreen.paste(temp,1,0)
                self.oCScreen.paste(zero,0,Tetris.iScreenDw)
                nDeleted+=1
        return
        #Tetris.deleteFullLines(self)
        #self.oCScreen.paste(self.game.oScreen,0,0)
        #self.oCScreen=Matrix(self.game.oScreen)
        #self.oCScreen=self.oScreen
        #return

