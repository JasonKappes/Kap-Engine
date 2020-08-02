## 💡 Overview
**Kap Engine** is a 3D video game engine created with **C++**. It was built on top of a basic graphics package that supported rendering, texturing, shading, and input. This was a large-scale, 6 month software development project independently developed from Jan. 2020 - June 2020. 
* A user could create a 3D video game with this engine. 3D model, shading, and texturing is supported. What's unique about this engine is the world editor. If world editor mode is enabled, all objects currently in the game can be edited, and world data is de/serialized (saved) for the next run. 
* The player can receive callbacks for mouse and keyboard events. Different types of 3D collisions are supported, including 3D mouse/object collisions and terrain collisions. Additionally, the player can spawn terrain, receive timed callbacks (alarms), display 2D messages, utilize preset camera angles, and utilize the visualizer to display 3D collision volumes in-game. 
* Some high-level software design and linear algebra guidance was received from a DePaul professor.

## ❤️ Personal Note
I put my heart into this project, and I love every bit of it. This project was an incredible technical growing experience as I continually shattered my expectations as to what I thought I was capable of. This was created while I was a full-time student at DePaul University. ~30 hours of weekly development time was poured into the planning, programming, and testing of this engine. Although this program is not meant to be downloaded, feel free to pick through its contents as you please. A high-level overview for each system will follow below. It astounded me that, at the end of development I had acrued 8000+ lines of engine code (not including whitespaces, comments, braces). Although this number doesn't mean much by itself, I hope it sheds some light into the amount of work I put into it.

## 📘 High-Level Technical Takeaways
* **(On --> maintainability, scalability):** Because this was such a massive project, decoupling systems was very important. I focused on having as few interdependencies as possible. This also made it easier to debug errors as it minimized the amount of places where a bug could have occured. Consequently, encapsulation was relied on heavily to keep data as separate as possible.
  * This engine was made with an object-oriented design methodology. This also lent itself to the idea of maintainability as it was easier for me to keep a mental map of where information is kept. For example, any collision-related information for an object is held in the Collidable class. All Collidable object would only be managed in the Collidable manager. This pattern is consistent with the other engine systems.
* **(On --> performance):** An object could be de/registered from any system. Because of this, each system (collision manager, update manager, etc.) had a map chosen as a data structure. The reason being that an object could remove itself from any system with a O(1) erase because each object held onto it's iterator in every map. With a vector, there were multiple problems like iterator invalidation and re-growth. However, data locality was sacrificed heavily with this decision. (In hindsight, a vector holding fixed sized arrays could have avoided both of these problems)
  * For collisions, a bounding volume hierarchy was used to reduce the number of collision calculations every frame. Additionally, user objects could "register collision pairs". So if the player wanted to detect collisions with a tree, it would register a <Player, Tree> collision pair. This way, the engine would check for collision exclusively between all player and tree objects, and not between the player and all objects.
  * The same idea was used for mouse picking. An object would need to register itself for "Selection". Only objects registered for selection were considered in mouse-picking calculations. Without this, I would have had to measure a mouse collision against every object in the scene (highly inefficient). Any object "selected" by a mouse-click was given a callback.
  * Design patterns were utilized heavily in the engine. Strategy patterns were used to switch on/off whichever systems were being used depending on the mode running (world-edit mode or a regular game-run mode). Additionally, this was used to abstract complicated world editor object selection and input situations. The command pattern was used to implement the "Undo" feature in world-edit mode. Singleton Pattern was used to grant access to scene-independent systems (like Cursor). The visitor pattern was used to help keep simple collision code, but still resolve specific collisions. Object Pools were used for commands that were spawned heavily. 
* **(On --> user api):** This was a new problem for me, because I was never use to writing large-scale API's. Trying to step into the user's shoes grants a different perspective on your engine. Some things that seem clear, may not be. Additionally, there were common use cases (like specific camera angles) that I abstracted into usable methods and also other quality of life changes made along the way.


## ⭐ Game Engine Features

## 🚀 User API Examples

## -- This is a Work in Progress -- 


  



