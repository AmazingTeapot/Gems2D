Gems2D
======

An engine for 2D games based on SFML


Version History:

v0.0.1 ~ v0.9.0: Unfortunately there are no documentation about the first steps of the engine. Trough this first steps some basic functionalities were implemented: Definition, integration with SFML, layer types creation, resource handlers, wrappings, animation handlers, external events, camera, etc...

v1.0.0: Backup Dump (12/2/2013): Here we get a dump of a backup generated after the Global Game Jam 2013. There is a lot of code to clean, lot of classes to repair (legated code that has to be drained).

v1.0.1: Clean-up, Screen Delimitation and Anchor Points (14/2/2013): All the code has been commented and cleaned, trying to get an stable version of all the functionalities implemented until the moment. Added screen delimitation: Now is not possible to get out of the screen. Added too the concept of Anchor Point. Now is possible to set an Anchor Point to a Sprite, so we can apply all the transformations over this point.

v1.0.2: Still Cleaning and Formatting (29/3/2013): Now all the code is commented using the same format rules. The functions are explained, and everything is documented.

v1.1.0: DeltaTime and Updates (15/04/2013): Added the concept of deltaTime: Now all the movement in the game is defined by the time passed between each iteration of the gameLoop (and not set by a fixed constant). With this, we can assure that all the movement is done at a constant speed, no matter how the performance of the PC goes. The same goes for the step time of the animations.
