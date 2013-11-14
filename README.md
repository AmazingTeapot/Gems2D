Gems2D
======

What is Gems2D?

Gems2D is an engine that will try to help users who want to make their own 2D Games.
It is build wrapping SFML as a base.
The main idea is to have a tool that could allow the player to build its game by programming only the logics.

This engine allows you to load resources (images, textures, fonts, sounds...) easily. 
It works drawing the elements on different layers, which can be tile-based layers, layers with static elements, layers with animations, background layers (supporting parallax too), etcétera.
It supports animations, scrolling, interaction with periferics, among others.
It also has an integration with Box2D to simulate the physics (this is something I have been working on, so it's not finished).
All the resources needed will be loaded via txt (soon will all be loaded via xml or similar).

By now there is a sample project (a pseudo-port of Vampire Killer of MSX) I had to build as a college practice. It shows some of
the functionalities of the engine, and it's pretty nice.
Almost all the functions are well-documented, so it shouldn't be hard to use.

I hope you find this useful, and don't forget to check for new versions, since this is unfinished.

Next Goals:

* Make the physics module a solid module.
* Reorganize the way of reading the resources (an interface to auto-generate all of it).

Version History:

v0.0.1 ~ v0.9.0: Unfortunately there are no documentation about the first steps of the engine. Trough this first steps some basic functionalities were implemented: Definition, integration with SFML, layer types creation, resource handlers, wrappings, animation handlers, external events, camera, etc...

v1.0.0: Backup Dump (12/2/2013): Here we get a dump of a backup generated after the Global Game Jam 2013. There is a lot of code to clean, lot of classes to repair (legated code that has to be drained).

v1.0.1: Clean-up, Screen Delimitation and Anchor Points (14/2/2013): All the code has been commented and cleaned, trying to get an stable version of all the functionalities implemented until the moment. Added screen delimitation: Now is not possible to get out of the screen. Added too the concept of Anchor Point. Now is possible to set an Anchor Point to a Sprite, so we can apply all the transformations over this point.

v1.0.2: Still Cleaning and Formatting (29/3/2013): Now all the code is commented using the same format rules. The functions are explained, and everything is documented.

v1.1.0: DeltaTime and Updates (15/04/2013): Added the concept of deltaTime: Now all the movement in the game is defined by the time passed between each iteration of the gameLoop (and not set by a fixed constant). With this, we can assure that all the movement is done at a constant speed, no matter how the performance of the PC goes. The same goes for the step time of the animations.

v1.2.0: Game Testing (06/04/2013 - 27/08/2013): The engine was used for the first time to make a full game. This game is "Game&Bud", developed in a one night stand, and the results were sucessful. The game was made in a separate repository and during the developement a few more features were added, and some bugs were fixed (06/04/2013). This features were merged and polished on the engine on 27/08/2013.
A few attempts to work with physics have been made. We are trying to integrate Box2D, a physics library. The first tests are positive, but by now this branch of the project is paused.
