import core
import random
import game
import components as comp

nx = 16
ny = 12
nm = 20
class Game(core.ScriptBase):
    def Init(self):
        self.freeze = False
        self.frozen = 0
        self.win = False

        self.GetGameObject().AddComponent(comp.CameraComponent(
            core.Rect(nx*50, ny*50, nx * 100, ny * 100)
        )).GetCameraComponent().SetActive()
        self.board = []
        #set cells
        for i in range(0, nx):
            self.board.append([])
            for j in range(0, ny):
                self.board[i].append(Cell(i, j, self))
        #set mines
        rands = []
        for i in range(0, nm):
            while True:
                rnd=random.randint(0,nx*ny-1)
                if rnd not in rands:
                    rands.append(rnd)
                    break
        for i in rands:
            self.board[i//ny][i%ny].mine = True
        #set neighbors
        for i in range(0, nx):
            for j in range(0, ny):
                cell = self.board[i][j]
                if (i>0):
                    cell.neighbors.append(self.board[i-1][j])
                    if (j>0):
                        cell.neighbors.append(self.board[i-1][j-1])
                    if (j<ny-1):
                        cell.neighbors.append(self.board[i-1][j+1])
                if (i<nx-1):
                    cell.neighbors.append(self.board[i+1][j])
                    if (j>0):
                        cell.neighbors.append(self.board[i+1][j-1])
                    if (j<ny-1):
                        cell.neighbors.append(self.board[i+1][j+1])
                if (j>0):
                    cell.neighbors.append(self.board[i][j-1])
                if (j<ny-1):
                    cell.neighbors.append(self.board[i][j+1])
        #set mine count
                for neigh in cell.neighbors:
                    if neigh.mine:
                        cell.adjCount+=1
    def Update(self):
        if self.freeze:
            self.frozen += 1
        else:#wincondition
            for i in range(0,nx):
                for j in range(0,ny):
                    if not (self.board[i][j].mine or self.board[i][j].clicked):
                        return
            self.freeze = True
            self.win = True
            for i in range(0,nx):
                for j in range(0,ny):
                    if self.board[i][j].mine:
                        self.board[i][j].label.AddComponent(comp.RectRenderComponent(core.Color(0, 160, 0)))
        if self.frozen > 240:
            game.LoadNextLevel()
            if not self.win:
                game.LoadNextLevel()

class Cell:
    def __init__(self, x, y, game):
        self.go = core.GameObject.Create(50+x*100, 50+y*100, 97, 97)
        self.label = core.GameObject.Create(50+x*100, 50+y*100, 60, 75)
        self.go.AddComponent(comp.RectRenderComponent(core.Color(170, 170, 170)))
        self.go.AddComponent(comp.ButtonComponent(self.click))
        self.mine = False
        self.clicked = False
        self.adjCount = 0
        self.neighbors = []
        self.game = game

    def click(self, gameobj):
        if self.clicked or self.game.freeze:
            return
        if self.mine:
            self.game.freeze = True
            self.label.AddComponent(comp.RectRenderComponent(core.Color(200, 0, 0)))
            return
        
        self.clicked = True
        self.go.AddComponent(comp.RectRenderComponent(core.Color(80, 80, 80)))
        if self.adjCount == 0:
            for c in self.neighbors:
                c.click(gameobj)
        else:
            self.label.AddComponent(comp.TextRenderComponent(core.Color(200, 200, 200),str(self.adjCount)))
