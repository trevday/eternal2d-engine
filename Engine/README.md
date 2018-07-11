Website Link: https://zilby.github.io/GameBuildingEngine/

# Eternal2D Engine

The Eternal2D engine is a component-based 2D game engine for Mac and Linux written in C++
that includes support for Python scripting. It was written from scratch for CS4850 except 
for the Physics engine, [Box2D](http://box2d.org/).

## Running the Engine 

Everything you need to run the Eternal2D engine is in the Eternal2D directory. If you wish 
to recompile the engine for yourself, you can do so using the Makefile and source code
provided to compile the source code and ThirdParty libraries into the Eternal2D directory.

Run `make` to rebuild the engine itself, or `make editor` to rebuild the C++ level serialization
modules used by the Eternal2D Editor. 

If you have completed the above steps or do not wish to recompile, simply launch the executable
located at `<yourplatform>/eternal2d`. The game's levels will be loaded from `Assets/Levels` in 
the order specified by the `Config/levels.txt` file. You can provide a different filename within 
the Config directory to use as the level list by passing it as a command line argument when
launching the engine.


## Eternal2DEditor
The Eternal2DEditor was built in Python3 using [Pillow](http://python-pillow.org/) 
and [appJar](http://appjar.info/). The appJar library is included with Eternal2D.

### Setup
To use the editor, you must first install python (version 3.5 or above). 

Next, you must install pillow for python3. To do this, you can run `sudo pip3 install pillow` 
in a terminal. 

If this fails try `sudo -H pip3 install pillow` or install manually. 

Finally, use python3 to run the python executable at `/Eternal2D/Editor/eternal2Deditor.py`. 


### Using the editor 
When you open the editor, you will be presented with a blank canvas and an empty detail panel.
You can drag the panels to your preferred size and drap the canvas around until the origin is 
where you prefer.

You can open an existing level file with `File>Open` or the folder icon.

You can change the name of the open level with `File>ChangeLevelName`. The default level name
is `temp.lvl`.

You can save your level with `File>Save` or the save icon. The editor will use the current name
as the file, so make sure to change it first if you don't want to save it at the defailt location.

You can edit the level list configuration with `Level>Edit Level Order`.

You can launch your game using `Level>Play`. 

- Note: Both of the previous features assume you use the default level list, `levels.txt`. If you wish
  to use a different, or more than one, level list, you will need to set them up manually.

You can create new GameObjects by clicking the "Create New" button, or using 
`GameObject>Create New GameObject`.

You can select an existing object by clicking it in the canvas or double-clicking it in the list
of objects.

You can edit an existing object by selecting it, and editing the fields in the inspector panel.
- Name: the name displayed in the list view
- X & Y: the postition of the center of the GameObject
- W & H: the width and height of the GameObject
- Permanent: whether the GameObject should persist through level loads (this will create multiple 
  copies if the level is reloaded)
- Module Name: The file name of the python script for this object, excluding `.py`. The script 
  should be placed in `Assets/Scripts/`
- Class Name: The name of the python class for this object. It should extend from `core.ScriptBase`
  - These can be left blank and no script will be loaded, but you should not leave only one filled in.
- Sprite Name: The name of the sprite image to use to render this object, if desired. The sprites
  should be places in `Assets/Sprites/`

You can use the "Move Up" and "Move Down" buttons to move the selected object up and down in the list.

You can duplicate an existing object and all of its attributes by selecting it, and clicking the 
"Duplicate" button, or by with `GameObject>Duplicate GameObject` 

If the Module Name is set correctly, you can open the script for the currently selected GameObject
with `GameObject>Open GameObject Script`

## Python Scripting Interface

You can import the following modules (all lowercase) into your python scripts.
Scripts should be placed in the `Assets/Scipts` directory.

### Core 
- Color
  - constructed with RGB or RGBA values between 0 and 255, or no arguments
  - `r`, `g`, `b`, `a` fields
- Rect:
  - constructed with x position, y position, width, and height, or no arguments
  - `x`, `y`, `w`, `h` fields
- Vector2:
  - constructed with x and y, or no arguments
  - `x`, `y` fields
- GameObject
 - Created with the static Create(x, y, width, height, isUI, isPermanent)
   - x & y are the center of the GameObject
   - isUI: if set to true, the GameObject will be rendered in screen space (x & y are pixels from 
       the tom left corner, +y is down) rather than game space (x & y are arbitrary units, +y is up)
   - isPermanent: if set to true, the GameObject will persist through level load
     - Both above flags can be omitted and default vales of false will be assumend. However, if you
       want to specify one you must specify the other as well 
 - AddComponent(component) function that adds the given Camera-, Button-, Physics- or RenderComponent
   to the GameObject that it is called on
 - Get___Component() function that returns the specified component that is attached to the GameObject
   it is called on
   - The blank can be either `Camera`, `Button`, `Physics`, or `Render`
 - position Vector2 that holds the x & y position of the GameObject's center
 - scale Vector2 that holds the GameObject's width and height in its x & y
- ScriptBase
  - Base class that Python script classes should inherit from
  - Init() is called when the component is added to a game object
  - Update() is called every frame
    - Both are required, even if they simply just return
  - Can only be added to GameObjects via the Eternal2DEditor (see below)
- Animation
  - Constructed with the source rect's x and y coordinates, width, and height, the number of frames for this animation, the
    horizontal distance between each frame on the sprite sheet, and the frames per second of this animation. 
- DeltaTime() method that returns the number of milliseconds the last frame took to Update and Render

### Components   
- CameraComponent
  - Constructed with a Rect specifying the Game Area to capture (x & y = center), and
    a Rect specifying the screen region to render to (x & y = topleft). If the latter
    or both of these are omitted, the screens' resolution will be assumed instead.
  - SetActive() function that tells the engine to use this camera for rendering.
  - SetCaptureArea(Rect) function that specifies a new game area for the camera to capture
- ButtonComponent
  - Constructed with a funtion that will be called when a Left-Click is detected on the 
    GameObject
  - The function must take in the game object that was clicked. This means the functon
    can be entirely separate from the script component
- PhysicsComponent 
  - Constructed with a body type (Dynamic, Kinematic, or Static), either a vector<Vector2> of four points to determine the 
    shape or a width and a height to determine the shape, the density (default 1), the friction (default 1), the restitution 
    (bounciness, default 1), and whether or not this GameObject is managed by physics. 
  - SetActive() function that sets the physics body to be active. 
  - ApplyForce(Vector2, Vector2) function that applies the given force to the given point relative to this object
  - ApplyForceToCenter(Vector2) function that applies the given force to the center of this object
  - GetLinearVelocity() funciton that gets the linear velocity of this object
  - SetLinearVelocity(Vector2) function that sets the linear velocity of this object
  - SetManagedByPhysics(bool) function that sets whether this object is managed by physics
- RenderComponents
  - A single GameObject can only have one of these at a time.
  - Any relevant images will be stretched to fit the GameObject.
  - AnimationRenderComponent
    - Constructed with a map of integer state IDs (eg: walking, jumping, standing) to individual animations ie: 
      unordered_map<unsigned int, Animation>
    - SwitchState(int) function that switches the current animation to that of the given state. 
  - ImageRenderComponent
    - Constructed with the name of the file within the `Assets/Sprites/` directory
  - TextRenderComponent
    - Constructed with a Color that the Text will be drawn in, and an optional initial string
    - ChangeText(string) function that updates the string
  - RectRenderComponent
    - Constructed with a Color that the GameObject will be drawn in

### Game
- LoadNextLevel() funciton load the next level after the current frame is finished
  - This can be called mutiple times in a frame to skip over levels
- ReloadLevel() function reloads and resets the current level
- GetActiveObjects() function returns a list of all the active GameObjects in the current level

### Physics
- BodyType enum (DYNAMIC, STATIC, or KINEMATIC) specifying behavior for a PhysicsComponent
- SetGravity(x, y) method to set the gravity in the x & y direction (e.g. earth is (0, -9.8))

### Sound
- LoadSound(pathath) function returns the sound loaded from the supplied path within `Assets/Sounds/`
- PlaySound(sound, times) function that plays a sound. 
  - Set times to -1 to loop playback.

### Translation
- Lookup(key) Lookup a value for the key set from the loaded locale
  - The `Config/lang.txt` file specifies the locale file to use from `Assets/Locales`.
  - e.g. "en" in lang.txt specifies to load `Assets/Locales/en.txt`
  - Locale files are of the form "keystring:value string", with each pair on its own line
  
