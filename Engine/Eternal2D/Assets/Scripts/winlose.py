import translation
import core
import game
import components as comp

class End(core.ScriptBase):
    def __init__(self, key, color):
        super().__init__()
        self.key = key
        self.color = color
    
    def Init(self):
        core.GameObject.Create(0,0,300,120).AddComponent(
            comp.TextRenderComponent(self.color, translation.Lookup(self.key)))
        camera = comp.CameraComponent(core.Rect(0,0,400,300))
        core.GameObject.Create(0, 0, 400, 300).AddComponent(
            camera
        ).AddComponent(
            comp.ButtonComponent(self.Swap)
        )#.GetComponent<core.CameraComponent>().SetActive()
        camera.SetActive()
    def Swap(self, GameObject_):
        game.LoadNextLevel()
        if self.key == "win":
            game.LoadNextLevel()


    def Update(self):
        return

class Win(End):
    def __init__(self):
        super().__init__("win", core.Color(0, 150, 0))

class Lose(End):
    def __init__(self):
        super().__init__("lose", core.Color(200, 0, 0))

