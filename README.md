# Minigin
### Intro
This was a engine made for the Programming 4 in DAE.
It is made for developing 2D games and consists of two projects, an engine project and a game project. The final user is supposed to put all their code into the game project. We also had to remake Q-bert in our own engine for this course, I didn't manage to completely finish the game so there is still a half working version in this repository. Despite this I believe my engine is well made for the amount of time we had for this assignment and the experience I had back then.

### Implementation
##### GameObjects and Components
Minigin uses the traditional Gameobject Component approach. I generally follow "preffer composition over inheritance"-rule so I made sure that my GameObject implementation could not be inherited from, instead the user should inherit from the abstract Component class to implement behaviors and add these to their GameObjects.

##### Resource Managment
The project includes a resource manager which ensures resources are only loaded in once and can easily be accessed from anywhere in the project. I implemented the ResourceManager as a singleton to ensure that there is only one instance in existance.

##### Rendering
The rendering is done with SDL but this was already included in the framework we got from the teachers.

##### Sound
The sound uses the service locator pattern, this allows the user to easily change which sound system is used. There are already three sound system implementations in the engine:
1. NullSoundSystem
    * This is an empty implementation, this exists so the soundlocator won't cause errors if used before a sound system is added
2. SoundSystem
    * This is a very basic implementation of a sound system using FMOD. The user can play a sound by using the filename. The sound system stores the sounds it initiliazes internally, so it will only be created once.
3. SoundSystemLogger
    * This sound system exists for testing and debugging purposes, it contains another sound system and will just pass everything to that sound system while logging whatever sound is supposed to be playing.

The user can also override the BaseSoundSystem class to make their own version.


##### Events
There is a basic Event System in Minigin. It uses the observer pattern. I implemented this by writing a Observer class and Subject class. The Observer class has a virtual function OnNotify which the user should override with their desired behavior. The subject class contains function to add/remove observers, also containts a Notify function which passes a GameObject and an Event to all the observers it is subscribed to.


