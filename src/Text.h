#pragma once
#include "CommonFunction.h"
using namespace std;
class Text
{
public:
	Text();
	~Text();

	enum TextColor {
		WHITE=0,
		BLACK=1,
		PINK=2,
		YELLOW = 3,
		GREEN = 4,
		ORANGE = 5,

	};
	bool LoadFont(TTF_Font* font, SDL_Renderer* renderer);

	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int color);
	
	void RenderText(SDL_Renderer* renderer, int xpos, int ypos, SDL_Rect* clip=NULL,double angle = 0.0,SDL_Point* center=NULL,SDL_RendererFlip flip=SDL_FLIP_NONE);
	void SetRect(const int& xp,const int& yp);
	void SetSizeText(const int& wp,const int& hp){
		wtext = wp;
		htext = hp;
	}
	SDL_Rect GetRect() const;

	int getwidth() { return wtext; };
	int getheight() { return htext; };

	void SetText(const string& text) {
		str = text;
	}
	string GetText() const{
		return str;
	}



private:
	SDL_Rect rec;
	string str;
	SDL_Color textcolor;
	SDL_Texture* texture;
	int xtext;
	int ytext;
	int wtext;
	int htext;
};

