#pragma once

/* Resource Managing related constants */

const string IMAGE_PATH = "./Resources/Graphics/";
const string IMAGE_EXTENSION = ".png";

const string MOVING_IMAGE_LAYER_PATH = "Backgrounds/";
const string STATIC_ELEMENTS_LAYER_PATH = "Sprites/";
const string STATIC_GRID_LAYER_PATH = "Tilesets/";
const string ANIMATED_ELEMENTS_LAYER_PATH = "AnimatedSprites/";

const string MUSIC_PATH = "./Resources/Audio/Music/";
const string MUSIC_EXTENSION = ".ogg";

const string SFX_PATH = "./Resources/Audio/SFX/";
const string SFX_EXTENSION = ".ogg";

const string FONT_PATH = "./Resources/Fonts/";
const string FONT_EXTENSION = ".ttf";

const string LEVEL_PATH = "./Resources/Levels/";
const string LEVEL_EXTENSION = ".txt";

const string LEVEL_CONFIGS = "/config";

const string ANIMATION_PATH = "./Resources/Graphics/AnimatedSprites/";


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

/* 91~99 - System-Related Constants */
const int PAUSE = 91;
const int QUIT = 92;
const int FULLSCREEN = 93;
const int SELECT = 94;

/* Game Presets */
const int WINDOW_SIZE_X = 1366;
const int WINDOW_SIZE_Y = 768;

/* Default Animation Speed, measured in Steps Per Second */
const float DEFAULT_ANIM_SPEED = 5; 

/* Enumeration dels diferents tipus d'estat */

const enum status {
	EMPTY, 
	TRAINLEFT,
	TRAINRIGHT,
	COLLISION,
	DOOR,
	DOORCOLLISION,
	DOORWITHTRAINLEFT,
	DOORWITHTRAINRIGHT,
	OPENINGDOOR,
	DOOROPENED
};

const int GRAPH_UP = 1;
const int GRAPH_DOWN = 2;
const int GRAPH_LEFT = 3;
const int GRAPH_RIGHT = 4;



