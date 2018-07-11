import core
import input
import physics
import sound
import render
import components

screenWidth = 1000
screenHeight = 800
bally = 0
scoreL = 0
scoreR = 0


class Camera(core.ScriptBase):
    def Init(self):
        area = core.Rect(0,  0, screenWidth, screenHeight)
        cam = components.CameraComponent(area)
        self.GetGameObject().AddComponent(cam)
        cam.SetActive()
        physics.SetGravity(0, 0)
        sound.PlaySound(sound.LoadSound("Sounds/bensound-funkyelement.wav"), 0)

    def Update(self):
        return

class Paddle(core.ScriptBase):
    paddleSpeed = 8

    def Init(self):
        self.phys = components.PhysicsComponent(physics.BodyType.KINEMATIC, 
                                        self.GetGameObject().scale.x, 
                                        self.GetGameObject().scale.y, 
                                        1, 0.5, 1, True)
        self.GetGameObject().AddComponent(self.phys)
        self.phys.SetActive(True)


    def Update(self):
        return

    def Move(self, i):
        self.phys.SetLinearVelocity(core.Vector2(0, i))

    def CanMoveUp(self): 
        return self.GetGameObject().position.y < (screenHeight / 2) - (self.GetGameObject().scale.y / 2)

    def CanMoveDown(self): 
        return self.GetGameObject().position.y > (screenHeight / -2) + (self.GetGameObject().scale.y / 2)

class LPaddle(Paddle): 
    def __init__ (self):
        Paddle.__init__ (self)

    def Update(self): 
        if input.GetActionHeld(input.inputs.UP) and self.CanMoveUp():
            self.Move(self.paddleSpeed)
        elif input.GetActionHeld(input.inputs.DOWN) and self.CanMoveDown():
            self.Move(-self.paddleSpeed)
        else:
            self.Move(0)

class RPaddle(Paddle): 
    def __init__ (self):
        Paddle.__init__ (self)
        self.paddleSpeed = 4

    def Update(self): 
        y = self.GetGameObject().position.y
        if bally > y and self.CanMoveUp():
            self.Move(self.paddleSpeed)
        elif bally < y and self.CanMoveDown():
            self.Move(-self.paddleSpeed)
        else:
            self.Move(0)

class Ball(core.ScriptBase):
    phys = None
    lastVect = None

    def Init(self):
        self.ResetPhys()
        self.bounce = sound.LoadSound("Sounds/Jump.wav")
        self.score = sound.LoadSound("Sounds/Kill.wav")
        self.lose = sound.LoadSound("Sounds/GameOver.wav")

    def Update(self):
        vect = self.phys.GetLinearVelocity()
        if (self.lastVect != None and (self.lastVect.x != vect.x or self.lastVect.y != vect.y)) :
            sound.PlaySound(self.bounce, 0)
        self.lastVect = vect

        global bally
        bally = self.GetGameObject().position.y
        if ((bally > (screenHeight / 2) - (self.GetGameObject().scale.y / 2) and vect.y > 0) or
            (bally < (screenHeight / -2) + (self.GetGameObject().scale.y / 2) and vect.y < 0)) :
            self.phys.SetLinearVelocity(core.Vector2(vect.x, -vect.y))

        if (vect.x < 2 and vect.x >= 0):
            self.phys.SetLinearVelocity(core.Vector2(2, vect.y))
        elif (vect.x > -2 and vect.x < 0):
            self.phys.SetLinearVelocity(core.Vector2(-2, vect.y))


        if (self.GetGameObject().position.x > (screenWidth / 2) or 
            self.GetGameObject().position.x < (screenWidth / -2)):
            if self.GetGameObject().position.x > (screenWidth / 2): 
                sound.PlaySound(self.score, 0)
                global scoreL
                scoreL += 1
            else: 
                sound.PlaySound(self.lose, 0)
                global scoreR
                scoreR += 1
            self.ResetPhys()
        

    def ResetPhys(self):
        self.GetGameObject().position = core.Vector2(300, 300)
        self.phys = components.PhysicsComponent(physics.BodyType.DYNAMIC, 
                                        self.GetGameObject().scale.x,
                                        self.GetGameObject().scale.y,  
                                        1, 0.05, 1.2, True)
        self.GetGameObject().AddComponent(self.phys)
        self.phys.SetActive(True)
        self.phys.SetLinearVelocity(core.Vector2(-4, -5))

class Score(core.ScriptBase):
    score = 0

    def Init(self):
        self.text = components.TextRenderComponent(core.Color(255, 255, 255, 255))
        self.UpdateText()
        self.GetGameObject().AddComponent(self.text)

    def Update(self):
        self.UpdateText()

    def UpdateText(self):
        self.text.ChangeText(str(self.score))

class ScoreL(Score):
    def Update(self): 
        global scoreL
        self.score = scoreL
        Score.Update(self)

class ScoreR(Score):
    def Update(self): 
        global scoreR
        self.score = scoreR
        Score.Update(self)