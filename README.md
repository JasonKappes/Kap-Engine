## 💡 Overview
**Kap Engine** is a 3D video game engine created with **C++**. It was built on top of a basic graphics package that supported rendering, texturing, shading, and input. This was a large-scale, 6 month software development project independently developed from Jan. 2020 - June 2020. 
* A user could create a 3D video game with this engine. 3D model, shading, and texturing is supported. What's unique about this engine is the world editor. If world editor mode is enabled, all objects currently in the game can be edited, and world data is de/serialized (saved) for the next run. 
* The player can receive callbacks for mouse and keyboard events. Different types of 3D collisions are supported, including 3D mouse/object collisions and terrain collisions. Additionally, the player can spawn terrain, receive timed callbacks (alarms), display 2D messages, utilize preset camera angles, and utilize the visualizer to display 3D collision volumes in-game. 
* Some high-level software design and linear algebra guidance was received from a DePaul professor.

## ❤️ Personal Note
I put my heart into this project, and I love every bit of it. This project was an incredible technical growing experience as I continually shattered my expectations as to what I thought I was capable of. This was created while I was a full-time student at DePaul University. ~30 hours of weekly development time was poured into the planning, programming, and testing of this engine. Although this program is not meant to be downloaded, feel free to pick through its contents as you please. A high-level overview for each system will follow below. It astounded me that, at the end of development I had acrued 8000+ lines of engine code (not including whitespaces, comments, braces). Although this number doesn't mean much by itself, I hope it sheds some light into the amount of work I put into it.

## 📘 High-Level Technical Takeaways
**(Scalability):** Because this was such a massive project, decoupling systems was very important. I focused on having as few interdependencies as possible. This also made it easier to debug errors as it minimized the amount of places where a bug could have occured. Consequently, encapsulation was relied on heavily to keep data as separate as possible.
  * This engine was made with an object-oriented design methodology. This also lent itself to the idea of maintainability as it was easier for me to keep a mental map of where information is kept. For example, any collision-related information for an object is held in the Collidable class. All Collidable object would only be managed in the Collidable manager. This pattern is consistent with the other engine systems.
  
**(Engine Performance):** An object could be de/registered from any system. Because of this, each system (collision manager, update manager, etc.) had a map chosen as a data structure. The reason being that an object could remove itself from any system with a O(1) erase because each object held onto it's iterator in every map. With a vector, there were multiple problems like iterator invalidation and re-growth. However, data locality was sacrificed heavily with this decision. (In hindsight, a vector holding fixed sized arrays could have avoided both of these problems)
  * For collisions, a bounding volume hierarchy was used to reduce the number of collision calculations every frame. Additionally, user objects could "register collision pairs". So if the player wanted to detect collisions with a tree, it would register a <Player, Tree> collision pair. This way, the engine would check for collision exclusively between all player and tree objects, and not between the player and all objects.
  * The same idea was used for mouse picking. An object would need to register itself for "Selection". Only objects registered for selection were considered in mouse-picking calculations. Without this, I would have had to measure a mouse collision against every object in the scene (highly inefficient). Any object "selected" by a mouse-click was given a callback.
  * Design patterns were utilized heavily in the engine. Strategy patterns were used to switch on/off whichever systems were being used depending on the mode running (world-edit mode or a regular game-run mode). Additionally, this was used to abstract complicated world editor object selection and input situations. The command pattern was used to implement the "Undo" feature in world-edit mode. Singleton Pattern was used to grant access to scene-independent systems (like Cursor). The visitor pattern was used to help keep simple collision code, but still resolve specific collisions. Object Pools were used for commands that were spawned heavily. 
  
**(User API):** This was a new problem for me, because I was never use to writing large-scale API's. Trying to step into the user's shoes grants a different perspective on your engine. Some things that seem clear, may not be. Additionally, there were common use cases (like specific camera angles) that I abstracted into usable methods and also other quality of life changes made along the way.


## ⭐ Game Engine Features

#### GameObject
* The **GameObject** class inherits from many parent classes with each adding unique capabilities for any **GameObject** to utilize. This is the entry point for any user. They simply inherit from the GameObject class, which allows the object to leverage different capabilities, depending on the user's needs.

#### World Editor
* The world editing mode allows the user to visually edit the world data associated with any GameObject. The user can change the position, rotation, and scale of any selected objects. An interactive GUI is displayed around the selected object. Position, rotation, and scale each utilize a different GUI that behaves intuitively with the changing of world data. Objects can also be duplicated or erased from the scene. Additionally any data changes on any GameObject can be "undone" simply with Z. This mode is able to be enabled/disabled depending on if the user wants to play the game regularly or edit the world. Any changes made with the world editor are saved and loaded for the next program run.

#### Scene Management
* The user can create multiple scenes, each with different assets and objects. A scene loads level data pertanent to itself.

#### Rendering and Updating
* This game engine provides the basic foundation of 3D object rendering and updating. The **Drawable** and **Updatable** class are responsible for defining behavior for these features. An object can de/register itself from both systems at any time, allowing for a complete GameObject lifecycle.

#### Object Collision
* The **Collidable** class has collision behavior and is a parent class for **GameObject**. A GameObject has a sphere collision volume as default, but can also choose an axis-aligned bounding box (AABB) or an oriented bounding box (OBB). The radius and position of any collision volume is updated every frame depending on the GameObject's position. Collisions calculations can be performed between all three collision volumes. If a collision occurs between two objects, each GameObject receives a callback.

#### Terrain
* The user can use a heightmap and texture to generate terrain. Any object type can also be registered for collision against terrain. Terrain collision calculations work correctly against any type of collision volume.

#### Asset Management
* The user can load textures, models, terrain, and shaders and also use these assets for any GameObject. The exact texture, modeling, and shading code is done with a pre-built graphics package. The user is notified upon duplicate or invalid asset insertion. Default assets are provided for each one of these areas.

#### Keyboard Input, Mouse Input, and Object Selection
* The **Inputable** and **Touchable** class define the behavior to register for various input events. Any object can register itself to receive callbacks for a key press, release, or hold. Additionally, an object can receive mouse press and release callbacks along with cursor directional movement callbacks. Any **Touchable** object can receive callbacks if an object is selected. The **Selectable** class defines the behavior for an object that can be selected. Objects can be de/registered from selection at any time.

#### Other Features
* The User can register "alarms" for any class, which is just a callback after a certain amount of time. The user can display 2D messages on screen. There are a few preset camera angles the user can use to get started with their game. There is a visualizer which allows the user to visualize all of the collision volumes on screen, useful during world editing mode.

## 🚀 User API Examples:

### Example Object Constructor
```
void Player(){

#enable object world data (of this type) to be de/serialized for world editing
SetSerializableGroup<FirstPersonPlayer>();

#Receive callbacks to overriden draw() function
Drawable::SubmitDrawRegistration();

#Receive callbacks to overriden update() function
Updatable::SubmitUpdateRegistration();

#Set model, shader, and texture for this object
transform->SetGraphicsObject(
new GraphicsObject_TextureFlat(ModelManager::Get("sphere.azul"),
	ShaderManager::Get("textureFlatRender"), 
TextureManager::Get("metal_rust.tga")));

	Collidable::SubmitCollisionRegistration();                                                 //This object registers itself for collision
	Collidable::SetColliderModel(transform->object->getModel(), Collidable::Volume::OBB);      //This object sets it's collision model and volume
	Collidable::SetCollidableGroup<FirstPersonPlayer>();                                       //This object sets it's collision group

	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, EVENT_TYPE::HELD_DOWN);                  //This object will receive callbacks for WASD press every frame
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, EVENT_TYPE::HELD_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, EVENT_TYPE::HELD_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, EVENT_TYPE::HELD_DOWN);

	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::PRESS);                  //This object will receive callbacks for space press

	Touchable::SubmitMouseRegistration(AZUL_MOUSE::BUTTON_LEFT, MOUSE_EVENT_TYPE::PRESS);      //This object will receive callbacks for Left click press
	Touchable::SubmitMouseRegistration(AZUL_MOUSE::BUTTON_LEFT, MOUSE_EVENT_TYPE::RELEASE);    //This object will receive callbacks for Left click release
```

### Example Scene
```
void Level1::Initialize()                 //Called at the start of the scene
{
   SetTerrain("Desert");                   //Spawns a pre-loaded terrain for the level
  
	 SetCollisionPair<Grunt, Player>();      //Tells the scene to check for collisions between Grunt and Player objects every frame. (Indiv. callbacks upon collision)
  SetCollisionPair<Bullet, Grunt>();   
  SetCollisionSelf<Grunt, Grunt>();       //Tells the scene to check for collisions between Grunt objects every frame (Indiv. callbacks upon collision)
  
  SetCollisionTerrain<Player>();          //Tells the scene to check for collisions between Player objects every frame
  SetCollisionTerrain<Grunt>();

  this->enemy_boss = new EnemyBoss();
}

void Level1::SceneEnd()                   //Allows the user to cleanup memory
{
  delete this->enemy_boss;
}
```
