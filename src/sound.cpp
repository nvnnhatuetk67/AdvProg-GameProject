#include"sound.h"
#include<windows.h>

bool checkMute = false;

Mix_Music*  loadMusic(string filePath,Mix_Music* music ){
    if(SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    }
    // Initialize SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    // Load MP3 file
     music = Mix_LoadMUS(filePath.c_str());//"sound/sound1.mp3"
    if(music == NULL) {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return music;
}
void playMusic(Mix_Music* music){

    Mix_PlayMusic( music, -1 );
    Mix_VolumeMusic(20);
    
}
void playCorrect(){
    soundPointing =  Mix_LoadWAV("sounds/correct.wav");
   
    Mix_VolumeChunk(soundPointing, 200);
    Mix_PlayChannel(-1, soundPointing, 0);
    
}
void playWrong(){
    soundWrong = Mix_LoadWAV("sounds/incorrect.wav");
    Mix_VolumeChunk(soundWrong, 200);
    Mix_PlayChannel(-1,soundWrong,0);
   
}
void playLoseGame(){
    Mix_Chunk* soundLose = Mix_LoadWAV("sounds/gameover.wav");
    Mix_PlayChannel(-1,soundLose,0);
    Mix_VolumeChunk(soundLose, 200);
}
void playWinGame(){
    Mix_Chunk* soundWin = Mix_LoadWAV("sounds/win.wav");
    Mix_PlayChannel(-1,soundWin,0);
    Mix_VolumeChunk(soundWin, 200);
}
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer){
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        cout<<"Unable to  load image " << path << " SDL_image Error: "
        << IMG_GetError() << endl;
    }
    else{
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == nullptr)
            cout<<"Unable to create texture from " << path << " SDL Error: "
                << SDL_GetError()<< endl;
                SDL_FreeSurface( loadedSurface);
    }
    return newTexture;
}
SDL_Texture* muteSound(SDL_Renderer* renderer,  SDL_Texture* mute, int x, int y ){
        
        if(!checkMute){
                if((x >= 10 && x <= 70)&&( y >= 10 && y <= 70)){
                    Mix_PauseMusic();
                    mute = loadTexture("assets/music_off.png", renderer);
                    checkMute = true;
                    }
                }
        else{
            if((x >= 10 && x <= 70)&&( y >= 10 && y <= 70)){
             Mix_ResumeMusic();

            mute = loadTexture("assets/music.png", renderer);
            checkMute = 0;
            }
                }
    return mute;
}
