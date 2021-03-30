from tetris import *

class CTetris(Tetris):
    nBlockTypes = 0
    nBlockDegrees = 0
    setOfBlockObjects = 0
    iScreenDw = 0

    def init(setOfBlockArrays):
        length=[]
        Tetris.nBlockTypes = len(setOfBlockArrays)
        Tetris.nBlockDegrees = len(setOfBlockArrays[0])
        Tetris.setOfBlockObjects = [[0] * Tetris.nBlockDegrees for _ in range(Tetris.nBlockTypes)]
        arrayBlk_maxSize = 0

        for i in range(Tetris.nBlockTypes):
            if arrayBlk_maxSize <= len(setOfBlockArrays[i][0]):
                arrayBlk_maxSize = len(setOfBlockArrays[i][0])
        
        Tetris.iScreenDw = arrayBlk_maxSize
        for i in range(Tetris.nBlockTypes):
            length.append(len(setOfBlockArrays[i][0][0]))

        for i in range(Tetris.nBlockTypes):
            for j in range(Tetris.nBlockDegrees):
                for m in range(length[i]):
                    for n in range(length[i]):
                        if(setOfBlockArrays[i][j][m][n]==1):
                            setOfBlockArrays[i][j][m][n]=i+1


        for i in range(Tetris.nBlockTypes):
            for j in range(Tetris.nBlockDegrees):
                Tetris.setOfBlockObjects[i][j] = Matrix(setOfBlockArrays[i][j])
                
        return

    def accept(self, key):
        self.state = TetrisState.Running
        if key >= '0' and key <= '6':
            if self.justStarted == False:
                self.deleteFullLines()
            self.iScreen = Matrix(self.oScreen)
            self.idxBlockType = int(key)
            self.idxBlockDegree = 0
            self.currBlk = Tetris.setOfBlockObjects[self.idxBlockType][self.idxBlockDegree]
            self.top = 0
            self.left = Tetris.iScreenDw + self.iScreenDx//2 - self.currBlk.get_dx()//2
            self.tempBlk = self.iScreen.clip(self.top, self.left, self.top+self.currBlk.get_dy(), self.left+self.currBlk.get_dx())
            self.tempBlk = self.tempBlk + self.currBlk
            self.justStarted = False
            print()
            if self.crush():
                self.state=TetrisState.Finished
            

            self.oScreen = Matrix(self.iScreen)
            self.oScreen.paste(self.tempBlk, self.top, self.left)
            return self.state
        elif key == 'q':
            pass
        elif key == 'a': # move left
            self.left -= 1
        elif key == 'd': # move right
            self.left += 1
        elif key == 's': # move down
            self.top += 1
        elif key == 'w': # rotate the block clockwise
            self.idxBlockDegree = (self.idxBlockDegree + 1) % Tetris.nBlockDegrees
            self.currBlk = Tetris.setOfBlockObjects[self.idxBlockType][self.idxBlockDegree]
        elif key == ' ': # drop the block
            while not self.crush():
               self.top += 1
               self.tempBlk = self.iScreen.clip(self.top, self.left, self.top+self.currBlk.get_dy(), self.left+self.currBlk.get_dx())
               self.tempBlk = self.tempBlk + self.currBlk

        else:
            print("Wrong Key!!!")

        self.tempBlk = self.iScreen.clip(self.top, self.left, self.top+self.currBlk.get_dy(), self.left+self.currBlk.get_dx())
        self.tempBlk = self.tempBlk + self.currBlk
        
        if self.crush():
            if key == 'a': # undo: move right
                self.left += 1
            elif key == 'd': # undo: move left
                self.left -= 1
            elif key == 's': # undo: move up
                self.top -= 1
                self.state = TetrisState.NewBlock
            elif key == 'w': # undo: rotate the block counter-clockwise
                self.idxBlockDegree = (self.idxBlockDegree - 1) % Tetris.nBlockDegrees
                self.currBlk = Tetris.setOfBlockObjects[self.idxBlockType][self.idxBlockDegree]
                
            elif key == ' ': # undo: move up
                self.top -= 1
                self.state = TetrisState.NewBlock

            self.tempBlk = self.iScreen.clip(self.top, self.left, self.top+self.currBlk.get_dy(), self.left+self.currBlk.get_dx())
            self.tempBlk = self.tempBlk + self.currBlk

        self.oScreen = Matrix(self.iScreen)
        self.oScreen.paste(self.tempBlk, self.top, self.left)

        return self.state

    def crush(self):
        dx=[]
        dy=[]
        count=0
        arr=self.currBlk.get_array()
        for i in range(len(arr)):
            for j in range(len(arr[i])):
                if(arr[i][j]!=0):
                    dx.append(i)
                    dy.append(j)
        arr_tmp=self.tempBlk.get_array()
        for i in range(len(dx)):
            a=dx[i]
            b=dy[i]

            if(arr_tmp[a][b]!=self.idxBlockType+1):
                return True
        return False
    def deleteFullLines(self):
        darray=self.oScreen.get_array()
        for i in range(self.oScreen.get_dy()-Tetris.iScreenDw):
            count=0
            for j in range(Tetris.iScreenDw, self.oScreen.get_dx()-Tetris.iScreenDw):
                if (darray[i][j]==0):
                    count+=1
            if(count==0):
                length=len(darray[i])
                del darray[i]
                darray.insert(0,[0]*length)
                self.iScreen=Matrix(darray)
                self.oScreen=Matrix(self.iScreen)
        return









