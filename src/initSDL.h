#ifndef INITSDL_H_INCLUDED
#define INITSDL_H_INCLUDED
#include "CommonFunction.h"


using namespace std;



void logSDLError(std::ostream& os, const std::string &msg, bool fatal);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);


void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

#endif // INITSDL_H_INCLUDED
