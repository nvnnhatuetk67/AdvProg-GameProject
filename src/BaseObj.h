#pragma once
#include "CommonFunction.h"

using namespace std;
class BaseObj
{
public:
	BaseObj();
	~BaseObj();
	void SetRect(const int& x, const int& y) {
		rect.x = x;
		rect.y = y;
	}
	void SetSizeRect(const int& w, const int& h){
		rect.w = w;
		rect.h = h;
	}
	void SetEntireRect(const int& x, const int& y,const int& w, const int& h){
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}
	void setTexture(SDL_Texture* tex){
		texture = tex;
	}
	SDL_Rect getRect() const {
		return rect;
	}
	SDL_Texture* gettexture() const {
		return texture;
	}

	virtual bool LoadImg(string file_path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* texture;
	SDL_Rect rect;

};


