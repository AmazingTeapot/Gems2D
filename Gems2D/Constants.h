#pragma once
#include <map>
#include <set>
#include <vector>
#include "Tile.h"
#include "Structs.h"
#include <SFML/Graphics.hpp>

/* Typedefs */


/* Resource Managing related constants */

const std::string IMAGE_PATH = "./Resources/Graphics/";
const std::string IMAGE_EXTENSION = ".png";

const std::string MOVING_IMAGE_LAYER_PATH = "Backgrounds/";
const std::string STATIC_ELEMENTS_LAYER_PATH = "Sprites/";
const std::string STATIC_GRID_LAYER_PATH = "Tilesets/";
const std::string ANIMATED_ELEMENTS_LAYER_PATH = "AnimatedSprites/";

const std::string MUSIC_PATH = "./Resources/Audio/Music/";
const std::string MUSIC_EXTENSION = ".ogg";

const std::string SFX_PATH = "./Resources/Audio/SFX/";
const std::string SFX_EXTENSION = ".ogg";

const std::string FONT_PATH = "./Resources/Fonts/";
const std::string FONT_EXTENSION = ".ttf";

const std::string LEVEL_PATH = "./Resources/Levels/";
const std::string LEVEL_EXTENSION = ".txt";

const std::string LEVEL_CONFIGS = "/config";

const std::string ANIMATION_PATH = "./Resources/Graphics/AnimatedSprites/";


/* Animation Names */

const int STANDBY_RIGHT = 0;
const int STANDBY_LEFT = 1;
const int WALKING_RIGHT = 2;
const int WALKING_LEFT = 3;
const int CROUCH_RIGHT = 4;
const int CROUCH_LEFT = 5;
const int STAIRS_RIGHT_UP = 6;
const int STAIRS_LEFT_UP = 7;
const int STAIRS_RIGHT_DOWN = 8;
const int STAIRS_LEFT_DOWN = 9;
const int WHIP_RIGHT = 10;
const int WHIP_LEFT = 11;
const int WHIP_CROUCHING_RIGHT = 12;
const int WHIP_STAIRS_RIGHT_UP = 13;
const int WHIP_STAIRS_RIGHT_DOWN = 14;
const int WHIP_CROUCHING_LEFT = 15;
const int WHIP_STAIRS_LEFT_UP = 16;
const int WHIP_STAIRS_LEFT_DOWN = 17;


/* States */ 

const int LEFT_INERTIA = 0;
const int RIGHT_INERTIA = 1;
const int JUMPING = 2;
const int FALLING = 3;
const int ON_FLOOR = 4;
const int CROUCHING = 5;
const int ATTACKING = 6;
const int LEFT_STAIRS = 7;
const int RIGHT_STAIRS = 8;

/* Event catching and handling related constants. Any constants can be added if needed.
   Some constants can be renamed if wanted to more specific constants, they are applied to the whole game */

/* 0~10 - Movement Constants */
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

/* 11~20 - Action Constants */
const int ACTION_RUN = 11;
const int ACTION_JUMP = 12;
const int ROTATE_LEFT = 13;
const int ROTATE_RIGHT = 14;

/* 21~30 - Physical Attacks Constants */
const int ATTACK_1 = 21;
const int ATTACK_2 = 22;
const int ATTACK_3 = 23;
const int ATTACK_4 = 24;

/* 31~40 - Magical Attacks Constants */
const int MAGIC_1 = 31;
const int MAGIC_2 = 32;
const int MAGIC_3 = 33;
const int MAGIC_4 = 34;

/* 81~89 - Peripherials Related Constants */
const int LEFT_CLICK = 81;
const int RIGHT_CLICK = 82;
const int CENTER_CLICK = 83;

/* 91~99 - System-Related Constants */
const int PAUSE = 91;
const int QUIT = 92;
const int FULLSCREEN = 93;
const int SELECT = 94;

/* Game Presets */
const int WINDOW_SIZE_X = 1366;
const int WINDOW_SIZE_Y = 768;

/* Default Animation Speed, measured in Steps Per Second */
const float DEFAULT_ANIM_SPEED = 8; 

/* Game Specifics */

