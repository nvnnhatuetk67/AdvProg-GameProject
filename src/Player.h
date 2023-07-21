#ifndef PLAYER_H_
#define PLAYER_H_
#include "CommonFunction.h"
#include "BaseObj.h"
#include <set>
#include <string.h>
#include <vector>

#define PLAYER_SPEED 5
#define BLANK_TILE 0
#define QUIZZ1 3
#define QUIZZ3 9
#define QUIZZ2 6
#define WRONG 7
#define TREASURE 4

class Player : public BaseObj
{
public:
	Player();
	~Player();
	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN = 3,

	};
	bool LoadImg(string path, SDL_Renderer* renderer);
	void show(SDL_Renderer* des);
	void getNum(int _n);
	void getFrame(int _f);
	void setclip();
	void set_renderquad();
	void setPos(float x, float y);
	float Get_ObjPosx();
	float Get_ObjPosy();
	void setWingame(bool check){
		winGame = check;
	}
	void setScore(int num){
		score = num;
	}
	void resetAnimation();
	int getScore(){
		return score;
	}
	bool getWingame(){
		return winGame;
	}

	void handleInputAction(SDL_Event e, SDL_Renderer* renderer);
	void DoPlayer(Map& mapdata);
	void CheckToMap(Map& mapdata);
	void setQuizz(SDL_Renderer* renderer);
	void showQuizz(SDL_Renderer* renderer, int num) ;
    bool checkLose(Map& mapdata);
	void resetBool();
	void setDisplayQuizz();
	void checkDisplayQuizz();

	SDL_Texture* getMute(){
		return mute_image;
	}
	void setMuteImage(SDL_Texture* image){
		mute_image = image;
	}

private:
	float x_val;
	float y_val;

	float xpos;
	float ypos;

	int widthframe;
	int heightframe;

	int score = 0;
	int n ;
	
	SDL_Rect FRAME_CLIP[15];
	Input input_type;
	int frame;
	int status;
	int frameSize;
	vector<int> selected_nums;
	
    bool winGame = 0;
    bool checkQuizz = 0;
    bool correct = 0;
	bool checkClick = 0;
	int cntQuizz = 0;
	SDL_Texture* mute_image;
    BaseObj quizz[20];
};
#endif