#ifndef SOUNDEFFECT_H_INCLUDED
#define SOUNDEFFECT_H_INCLUDED
#include "BaseObj.h"
#include "CommonFunction.h"
extern bool checkMute;
static SDL_Texture* mute = nullptr;
static Mix_Chunk *soundPointing = nullptr;
static Mix_Chunk *soundWrong =  nullptr;
static Mix_Chunk *soundNext = nullptr;

Mix_Music* loadMusic(string filePath,Mix_Music* music );
void playMusic(Mix_Music* music );
void playCorrect();
void playWrong();
void playLoseGame();
void playWinGame();

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);
SDL_Texture* muteSound(SDL_Renderer* renderer, SDL_Texture* mute, int x, int y );
    


#endif // SOUNDEFFECT_H_INCLUDED
