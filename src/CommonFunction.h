#pragma once
#include <Windows.h>
#include <fstream>
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
using namespace std;

static SDL_Window* gwindow = NULL;
static SDL_Renderer* gscreen = NULL;
static SDL_Event event;

static Mix_Music* background_music;
static Mix_Music* menu_music;
static Mix_Music* gameover_music;
static Mix_Music* winner_music;

static Mix_Chunk* sound[50];

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;
const string WINDOW_TITLE = "Mystery Journey";

const int FRAME_PER_SECOND = 25;
const int ColorKeyRed = 167;
const int ColorKeyGreen = 175;
const int ColorKeyBlue = 180;

#define QUIT 2
#define SPACE 10
#define TILE_SIZE 64
 
#define MAP_MAP_X 20
#define MAP_MAP_Y 12





typedef struct Input {
	int left;
	int right;
	int stayleft;
	int stayright;
	int up;
	int down;
};

typedef struct Map {
	//vị trí của ảnh
	int startx;
	int starty;
	// chỉ số của ô trong mảng
	int maxx;
	int maxy;

	int tile[MAP_MAP_Y][MAP_MAP_X];
	const char* mapfile;
}Map;
