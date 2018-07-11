"""
Runs the python editor GUI interface.
All python code relevant to the editor is found here. 
"""

from appJar import gui
from PIL import ImageTk, Image
import exporter
import sys
import os

## Gets the current OS path.


def getPath():
    return os.path.dirname(os.path.abspath(sys.argv[0]))

## Opens the given file based on the OS


def osStartFile(file):
    if sys.platform == 'win32':
        os.startfile(file)
    elif sys.platform == 'darwin':
        os.system("open " + file)
    elif sys.platform.startswith('linux'):
        os.system("xdg-open " + file)


## The global object list
globalObjs = []
## The current selected object
selected = None
## The current level file name
curFileName = "temp.lvl"
## Stores sprites for later
spriteStore = []

## Resets all global variables


def resetGlobalVars():
    global globalObjs
    global selected
    global curFileName
    global spriteStore
    globalObjs.clear()
    selected = None
    curFileName = "temp.lvl"
    spriteStore.clear()


## Create the application window
app = gui("Eternal2DEditor", "1200x900")

# ||||||||||||| Menubar, Toolbar, and Statusbar ||||||||||||

## Opens the current level file.


def open():
    openPath = app.openBox("Open Level", getPath() + "/../Assets/Levels/")
    if not openPath:
        return
    resetGlobalVars()
    global globalObjs
    globalObjs = exporter.ImportLevel(openPath)
    refreshAll()

    global curFileName
    curFileName = os.path.basename(openPath)
    app.setStatusbar("Open Level: " + curFileName)

## Saves the current level file.


def save():
    exporter.ExportLevel(getPath() + "/../Assets/Levels/" +
                         curFileName, globalObjs)
    app.setStatusbar("Saved level: " + curFileName)

## Plays the current level file.


def play():
    if sys.platform == 'darwin':
        os.system(getPath() + "/../mac/eternal2d")
    elif sys.platform == 'win32':
        osStartFile(getPath() + "/../windows/eternal2d.exe")
    else:
        os.system(getPath() + "/../linux/eternal2d")

## Gets the level order config file name.


def levelOrderConfig():
    osStartFile(getPath() + "/../Config/levels.txt")

## Changes the level name.


def changeLevelName():
    newName = app.textBox("Change Level Name", "Enter New Level Name:")
    if not newName:
        app.warningBox("Empty Level Name",
                       "Empty name given, level name not changed")
        return
    global curFileName
    curFileName = newName
    app.setStatusbar("Open Level: " + curFileName)

## Checks for duplicates of the current name in global objects.
# Will append -dup if there is a duplicate.

def checkNameDups(name):
    for obj in globalObjs:
        if obj.name == name:
            return checkNameDups(name + "-dup")
    return name

## Creates a new game object.

def createGameObject():
    newObj = exporter.LevelObject()
    newObj.name = checkNameDups("GameObject")
    newObj.x = 0
    newObj.y = 0
    newObj.w = 10
    newObj.h = 10
    newObj.permanent = False
    globalObjs.append(newObj)
    global selected
    selected = newObj
    refreshAll()

## Opens the currently selected game object's script file.


def openGameObjectScript():
    if not selected:
        return
    osStartFile(getPath()+"/../Assets/Scripts/"+selected.scriptName+".py")

## Duplicates the currently selected game object.


def dupGameObject():
    if not selected:
        return
    newObj = exporter.LevelObject()
    newObj.name = checkNameDups(selected.name)
    newObj.x = selected.x
    newObj.y = selected.y
    newObj.w = selected.w
    newObj.h = selected.h
    newObj.className = selected.className
    newObj.scriptName = selected.scriptName
    newObj.spriteName = selected.spriteName
    newObj.permanent = selected.permanent
    globalObjs.append(newObj)
    refreshAll()


app.addMenuList("File", ["Open", "Save", "ChangeLevelName"], [
                open, save, changeLevelName])
app.addMenuList("Level", ["Edit Level Order",
                          "Play"], [levelOrderConfig, play])
app.addMenuList("GameObject", ["Create New GameObject", "Open GameObject Script", "Duplicate GameObject"], [
                createGameObject, openGameObjectScript, dupGameObject])
app.addToolbar(["Open", "Save", "Create New", "Duplicate"], [
               open, save, createGameObject, dupGameObject], findIcon=True)
app.setToolbarPinned(pinned=True)
app.addStatusbar(fields=1)
app.setStatusbar("Open Level: " + curFileName)


# ||||||||||||| Scene View Canvas |||||||||||||

app.startPanedFrame("canvas")
## The title of the main canvas.
canvasTitle = "Scene View"
## Main canvas with images of GameObjects.
canvas = app.addCanvas(canvasTitle, 0, 0)
canvas.scan_dragto(110, 700, gain=1)

## Selects an object based on the cursor position.


def selectFromCanvas(event):
    x = canvas.canvasx(event.x)
    y = canvas.canvasy(event.y)
    for obj in globalObjs:
        if (x >= obj.x - obj.w / 2 and x <= obj.x + obj.w / 2 and
                y >= -obj.y - obj.h / 2 and y <= -obj.y + obj.h / 2):
            global selected
            selected = obj
            redrawObjects()
            refreshFields()
            break

## Begins moving the canvas based on the mouse position.


def canvasMoveStart(event):
    selectFromCanvas(event)
    canvas.scan_mark(event.x, event.y)


canvas.bind("<Button-1>", canvasMoveStart)

## Moves the canvas based on the mouse position.


def canvasMouseMove(event):
    canvas.scan_dragto(event.x, event.y, gain=1)


canvas.bind("<B1-Motion>", canvasMouseMove)

## Deletes the selected game object.


def deleteSelected(key):
    global selected
    if not selected:
        return
    globalObjs.remove(selected)
    selected = None
    refreshAll()


canvas.bind("<BackSpace>", deleteSelected)

## Draws the given image to the canvas.


def drawImage(path, obj):
    im = Image.open(os.path.join(getPath()+"/../Assets/Sprites/", path)).convert(
        "RGB").resize((obj.w, obj.h), resample=Image.BILINEAR)
    sprite = ImageTk.PhotoImage(im)
    spriteStore.append(sprite)
    canvas.create_image(obj.x, -obj.y, image=sprite)

## Redraws all game objects on the canvas.


def redrawObjects():
    app.clearCanvas(canvasTitle)
    spriteStore.clear()
    # axes
    canvas.create_line(-2000, 0, 2000, 0, fill="black")
    canvas.create_line(0, -2000, 0, 2000, fill="black")
    for i in range(-20, 21):
        canvas.create_line(-5, i*100, 5, i*100, fill="black")
        canvas.create_line(i*100, -5, i*100, 5, fill="black")

    for obj in globalObjs:
        if (selected and selected == obj):
            canvas.create_rectangle(obj.x - obj.w / 2 - 1, -obj.y - obj.h / 2 - 1,
                                    obj.x + obj.w / 2 + 1, -obj.y + obj.h / 2 + 1, fill="green")
        elif not obj.spriteName:
            canvas.create_rectangle(obj.x - obj.w / 2, -obj.y - obj.h / 2,
                                    obj.x + obj.w / 2, -obj.y + obj.h / 2, fill="red")
        if obj.spriteName:
            drawImage(obj.spriteName, obj)



# |||||||||||| "Inspector" Section ||||||||||||
app.startPanedFrame("inspector")

# Editable parts of object
app.startFrame("fields", 0, 0)
## The label for the namefield.
nameField = "Name"
app.addLabelEntry(nameField, 0, 0, 2, 1)
## The label for the x coordinate field.
xField = "X"
app.addLabelNumericEntry(xField, 1, 0)
## The label for the y coordinate field.
yField = "Y"
app.addLabelNumericEntry(yField, 1, 1)
## The label for the width field.
wField = "W"
app.addLabelNumericEntry(wField, 2, 0)
## The label for the height field.
hField = "H"
app.addLabelNumericEntry(hField, 2, 1)
## The label for the permanent field.
permanentField = "Permanent"
app.addCheckBox(permanentField, 3, 0)

## The label for the module name field.
moduleNameField = "Module Name"
scriptEntry = app.addLabelEntry(moduleNameField, 4, 0, 2, 1)
## The label for the class name field.
classNameField = "Class Name"
app.addLabelValidationEntry(classNameField, 5, 0, 2, 1)
## The label for the sprite name field.
spriteNameField = "Sprite Name"
app.addLabelFileEntry(spriteNameField, 6, 0, 2, 1)

## Sets the currently selected game object to be layered one layer up.


def layerUpFunc():
    if not selected:
        return
    for i in range(len(globalObjs)):
        if selected == globalObjs[i] and i != 0:
            temp = globalObjs[i]
            globalObjs[i] = globalObjs[i-1]
            globalObjs[i-1] = temp
            refreshAll()
            break


## The label for the layer up name field.
layerUp = "Move Up"
app.addNamedButton(layerUp, layerUp, layerUpFunc, 7, 0)

## Sets the currently selected game object to be layered one layer down.


def layerDownFunc():
    if not selected:
        return
    for i in range(len(globalObjs)):
        if selected == globalObjs[i] and i != len(globalObjs)-1:
            temp = globalObjs[i]
            globalObjs[i] = globalObjs[i+1]
            globalObjs[i+1] = temp
            refreshAll()
            break


## The label for the layer down name field.
layerDown = "Move Down"
app.addNamedButton(layerDown, layerDown, layerDownFunc, 7, 1)

app.stopFrame()

app.setFont(20)
## The label for the scene hierarchy
listBox = "Scene Hierarchy"
## Side list with all objects
lb = app.addListBox(listBox, [], 1, 0)
lb.bind("<BackSpace>", deleteSelected)

app.stopAllPanedFrames()

## Refreshes all of the fields.


def refreshFields():
    if not selected:
        app.clearEntry(nameField)
        app.clearEntry(xField)
        app.clearEntry(yField)
        app.clearEntry(wField)
        app.clearEntry(hField)
        app.clearEntry(moduleNameField)
        app.clearEntry(classNameField)
        app.clearEntry(spriteNameField)
        app.setCheckBox(permanentField, ticked=False)
        return
    app.setEntry(nameField, selected.name)
    app.setEntry(xField, str(selected.x))
    app.setEntry(yField, str(selected.y))
    app.setEntry(wField, str(selected.w))
    app.setEntry(hField, str(selected.h))
    app.setEntry(moduleNameField, selected.scriptName)
    app.setEntry(classNameField, selected.className)
    actualSpriteName = ""
    if(selected.spriteName != "" and selected.spriteName != None):
        actualSpriteName = os.path.join(getPath(), selected.spriteName)
    app.setEntry(spriteNameField, actualSpriteName)
    app.setCheckBox(permanentField, ticked=selected.permanent)

## Refreshes the list of game objects.


def refreshList():
    app.clearListBox(listBox)
    for obj in globalObjs:
        app.addListItem(listBox, obj.name)

## Selects a game object from the list.


def selectInList(event):
    if app.getListBox(listBox):
        objName = lb.selection_get()
        for obj in globalObjs:
            if objName == obj.name:
                global selected
                selected = obj
                redrawObjects()
                refreshFields()
                break


lb.bind("<Double-1>", selectInList)
lb.bind("<Return>", selectInList)

## Sets the name via name field input.


def setName():
    global selected
    if not selected:
        return
    newName = checkNameDups(app.getEntry(nameField))
    selected.name = newName
    refreshList()


app.setEntrySubmitFunction(nameField, setName)

## Sets the x coordinate via x field input.


def setX():
    global selected
    if not selected:
        return
    newX = app.getEntry(xField)
    if(newX == None):
        intX = 0
    else:
        intX = int(newX)
    if selected.x != intX:
        selected.x = intX
        redrawObjects()


app.setEntryChangeFunction(xField, setX)

## Sets the y coordinate via y field input.


def setY():
    global selected
    if not selected:
        return
    newY = app.getEntry(yField)
    if(newY == None):
        intY = 0
    else:
        intY = int(newY)
    if selected.y != intY:
        selected.y = intY
        redrawObjects()


app.setEntryChangeFunction(yField, setY)

## Sets the width via width field input.


def setW():
    global selected
    if not selected:
        return
    newW = app.getEntry(wField)
    if(newW == None):
        intW = 0
    else:
        intW = int(newW)
    if selected.w != intW:
        selected.w = intW
        redrawObjects()


app.setEntryChangeFunction(wField, setW)

## Sets the height via height field input.


def setH():
    global selected
    if not selected:
        return
    newH = app.getEntry(hField)
    if(newH == None):
        intH = 0
    else:
        intH = int(newH)
    if selected.h != intH:
        selected.h = intH
        redrawObjects()


app.setEntryChangeFunction(hField, setH)

## Sets the script name via script field input.


def setScriptName():
    global selected
    if not selected:
        return
    newScriptName = app.getEntry(moduleNameField)
    if newScriptName != selected.scriptName:
        selected.scriptName = newScriptName


app.setEntryChangeFunction(moduleNameField, setScriptName)

## Sets the class name via class field input.


def setClassName():
    global selected
    if not selected:
        return
    newClassName = app.getEntry(classNameField)
    if newClassName != selected.className:
        selected.className = newClassName


app.setEntryChangeFunction(classNameField, setClassName)

## Sets the sprite name via sprite field input.


def setSpriteName():
    global selected
    if not selected:
        return
    newSpriteName = app.getEntry(spriteNameField)
    if(newSpriteName != "" and newSpriteName != None):
        actualSpriteName = os.path.basename(newSpriteName)
    else:
        actualSpriteName = newSpriteName
    if actualSpriteName != selected.spriteName:
        selected.spriteName = actualSpriteName
        redrawObjects()


app.setEntryChangeFunction(spriteNameField, setSpriteName)

## Sets the permanent field via permanent field input.


def setPermanentField():
    global selected
    if not selected:
        return
    selected.permanent = app.getCheckBox(permanentField)


app.setCheckBoxChangeFunction(permanentField, setPermanentField)

## Refreshes everything.


def refreshAll():
    refreshList()
    refreshFields()
    redrawObjects()


refreshAll()
app.go()
