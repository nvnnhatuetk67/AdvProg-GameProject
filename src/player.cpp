#include "Player.h"
#include <cmath>
#include <windows.h>
#include "sound.h"

int widthframe = 64;
int heightframe = 64;
Player::Player() {
    frame = 0;
	widthframe = 0;
	heightframe = 0;
	xpos = 0;
	ypos = 0;
	x_val = 0;
	y_val = 0;
	status = 0;
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;
	input_type.stayleft = 0;
	input_type.stayright = 0;
	
	
}

Player::~Player() {
	Free();
}
void Player :: resetAnimation(){
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;
}
void Player :: resetBool(){
	winGame = 0;
    checkQuizz = 0;
    correct = 0;
	checkClick = 0;
}
void Player::setPos(float x, float y)
{
    xpos = x;
    ypos = y;
}


//Load image at specified path
bool Player::LoadImg(string path, SDL_Renderer* renderer) {
	bool check = BaseObj::LoadImg(path, renderer);
	n = 3;
	if (check == true) {
		widthframe = rect.w/n;
		//8 is the number of frames in the image
		heightframe = rect.h;
	}
	return check;
}


//get number of frames showing the character's state
void Player::getNum(int _n){
	n=_n;
}

//Set clip of an object's state
void Player::setclip() {
	if (widthframe > 0 && heightframe > 0) {
		for(int i=0;i<15;i++){
		FRAME_CLIP[i].x = widthframe*i;
		FRAME_CLIP[i].y = 0;
		FRAME_CLIP[i].w = widthframe;
		FRAME_CLIP[i].h = heightframe;
		}
	}
}
void Player :: setDisplayQuizz(){
	srand(time(NULL));
	set<int> selected_numbers;
	int num;
	int cnt = 0;
	while( cnt < 14){
	do{
		num = rand()%14;
		
	}while (selected_numbers.count(num) ); 
	selected_numbers.insert(num);
	selected_nums.push_back(num);
	cnt++;
	}
	
}
//Show the object
void Player::show(SDL_Renderer* des) {
	if(status == WALK_LEFT){
		LoadImg("assets/char_left.png", des );
	}
	else if( status == WALK_RIGHT){
		LoadImg("assets/char_right.png", des);
	}
	else if(status == WALK_DOWN){
		LoadImg("assets/char_down.png", des);
	}
	else if(status == WALK_UP){
		LoadImg("assets/char_up.png", des);
	}
	
	if(input_type.left == 1 || input_type.right == 1|| input_type.up == 1 || input_type.down == 1){
		frame++;
	}
	else{
		frame = 0;
	}
	 	rect.x = xpos;
	 	rect.y = ypos;


	if(frame > n-1){
		frame = 0;
	}

 	SDL_Rect* currentclip = &FRAME_CLIP[frame];

	SDL_Rect renderQuad = { rect.x,rect.y, 49 , 49 };
// 	if (currentclip != NULL)
// 	{
// 		renderQuad.w = 3*currentclip->w;
// 		renderQuad.h = 3*currentclip->h;
// 	}

 	SDL_RenderCopy(des, texture, currentclip, &renderQuad);
	
	if(checkQuizz && !checkClick){
		
		quizz[selected_nums[cntQuizz]].Render(des,nullptr);
		if(cntQuizz > 13) cntQuizz = 0;
	}
}
void Player :: checkDisplayQuizz(){
	for(int i: selected_nums){
		cout <<i << " ";
	}
	cout << "\n";
}
void Player:: handleInputAction(SDL_Event e, SDL_Renderer* renderer)
{	
	
	if (e.type == SDL_KEYDOWN ) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:{
			
			status = WALK_RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			input_type.up = 0;
			input_type.down = 0;
			rect.x+= PLAYER_SPEED;
		}
			break;
		case SDLK_LEFT:{
			status = WALK_LEFT;
			input_type.right = 0;
			input_type.left = 1;
			input_type.up = 0;
			input_type.down = 0;
			rect.x -= PLAYER_SPEED;
		}
			break;
		case SDLK_UP:{
			status = WALK_UP;
			input_type.right = 0;
			input_type.left = 0;
			input_type.up = 1;
			input_type.down = 0;
			rect.y -= PLAYER_SPEED;
		}
			break;
		case SDLK_DOWN:{
			status = WALK_DOWN;
			input_type.right = 0;
			input_type.left = 0;
			input_type.up = 0;
			input_type.down = 1;
			rect.y += PLAYER_SPEED;
		}
			break;	
		default: break;	
		}
	}
	else if(e.type == SDL_KEYUP ){
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:{
			
			input_type.right = 0;
		}
			break;
		case SDLK_LEFT:{
			
			input_type.left = 0;
		}
			break;
		case SDLK_UP:{
			
			input_type.up = 0;
		}
		case SDLK_DOWN:{
			
			input_type.down = 0;
		}
		default: break;	
		}
	}
	

	if(e.type == SDL_MOUSEBUTTONDOWN){
         if(e.button.button == SDL_BUTTON_LEFT){
				
                int x, y;
                SDL_GetMouseState(&x, &y);
				if(fmod(selected_nums[cntQuizz],2) == 1){

				if( (704 < x && x < 832) && (y > 448 && y < 512) && !checkClick){
					checkClick = 1;
					correct = 0;
					checkQuizz = 0;
				}
				else if((960 < x && x < 1088) && (y > 448 && y < 512) && !checkClick){
					checkClick = 1;
					correct = 1;
					checkQuizz = 0;
				}
				else{
					checkClick = 0;
					
				}
				}
				else{
				if( (704 < x && x < 832) && (y > 448 && y < 512) && !checkClick){
					checkClick = 1;
					correct = 1;
					checkQuizz = 0;
				}
				else if((960 < x && x < 1088) && (y > 448 && y < 512) && !checkClick){
					checkClick = 1;
					correct = 0;
					checkQuizz = 0;
				}
				else{
					checkClick = 0;
					
				}
				}
				 mute_image = muteSound(renderer, mute_image, x, y);
			
   		 	}
			
   		}
	

}
void Player::DoPlayer(Map& mapdata) {
	x_val = 0;
	y_val = 0;
	if(!checkQuizz && !winGame){
	if (input_type.left == 1) {
		x_val -= PLAYER_SPEED;
	}
	if (input_type.right == 1) {
		x_val += PLAYER_SPEED;
	}
	if (input_type.up == 1) {
		y_val -= PLAYER_SPEED;
	}
	if (input_type.down == 1) {
		y_val += PLAYER_SPEED;
	}
}
	

	CheckToMap(mapdata);
	

}
void Player::CheckToMap(Map& mapdata) {
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;

	int y1 = 0;
	int y2 = 0;
	int y3 = 0;
	widthframe = 48;
	heightframe = 48;
	//check horizontal
	int height_min = (heightframe  < TILE_SIZE ? heightframe : TILE_SIZE);
	
	x1 = (xpos + x_val)/TILE_SIZE;//10
	x2 = (xpos + x_val + widthframe +10 )/ TILE_SIZE;//11
	//cout << x1 << " " << x2 << "\n";

	y1 = (ypos   ) / TILE_SIZE;//2
	y2 = (ypos + height_min  ) / TILE_SIZE;//3
	
	if (x1 >= 9 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (x_val > 0) // player moving to the right
		{	
			if (mapdata.tile[y1][x2] == QUIZZ1  ){ 
				checkQuizz = 1;
				
				if(checkClick){
					checkQuizz = 0;
					cntQuizz++;
					if(correct){
						playCorrect();
						score += 100;
						mapdata.tile[y1][x2] = 0;
						
					}
					else{
						playWrong();
						mapdata.tile[y1][x2] = 7;
						
					}
				}		
			}
			
			else if (mapdata.tile[y1][x2] == TREASURE ){ 
					playWinGame();
					score += 1000;
					winGame = 1;	
			}
			else{
				if (mapdata.tile[y1][x2] != BLANK_TILE  || mapdata.tile[y2][x2] != BLANK_TILE ) {
					
						xpos = (x2)*TILE_SIZE ;
						xpos -= widthframe + 10  ;
						if(xpos < 640 ){
							xpos = 640;
						}
						if (xpos > 1152) xpos = 1152;
						x_val = 0;
					
				}
					checkQuizz = 0;	
					correct = 0;
					checkClick = 0;
					
				
			}
		}
		else if (x_val < 0) //player move to the left
		{	
			if ( mapdata.tile[y1][x1]  == QUIZZ1 ){
			
				
				checkQuizz = 1;

				if(checkClick){
					checkQuizz = 0;
					cntQuizz ++;
					if(correct){
						playCorrect();
						score += 100;
						mapdata.tile[y1][x1] = 0;
						
					}
					else{
						playWrong();
						mapdata.tile[y1][x1] = 7;
						
					}
				}		
				
			}
			
			else if (mapdata.tile[y1][x2] == TREASURE ){ 
					playWinGame();
					score += 1000;
					winGame = 1;	
			}
			else{
				if(mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y2][x1] != BLANK_TILE) {
					xpos = (x2)*TILE_SIZE ;
					if(xpos < 640 ){
						xpos = 640;
					}
					if (xpos > 1152) xpos = 1152;
					x_val = 0;
				}
					checkQuizz = 0;	
					correct = 0;
					checkClick = 0;
				
			}
		}

	}
	
	//check vertical
	int width_min = widthframe < TILE_SIZE ? widthframe : TILE_SIZE;
	x1 = (xpos  ) / TILE_SIZE;
	x2 = (xpos + width_min ) / TILE_SIZE;

	y1 = (ypos + y_val  ) / TILE_SIZE;
	y2 = (ypos + y_val + heightframe + 10 ) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (y_val > 0) 
		{
			if ( mapdata.tile[y2][x1]  == QUIZZ1 ) {
				
				checkQuizz = 1;

				if(checkClick){
					checkQuizz = 0;
					cntQuizz ++;
					if(correct){
						playCorrect();
						score += 100;
						mapdata.tile[y2][x1] = 0;
						
					}
					else{
						playWrong();
						mapdata.tile[y2][x1] = 7;
						
					}
				}

				
			}
			
			else if (mapdata.tile[y2][x1] == TREASURE ){ 
					playWinGame();
					score += 1000;
					winGame = 1;	
			}
			else{
				if  (mapdata.tile[y2][x1] != BLANK_TILE || mapdata.tile[y2][x2] != BLANK_TILE) {
					ypos = (y2 ) * TILE_SIZE;
					ypos -= heightframe  + 10 ;
					if(ypos < 128 ) ypos = 128;
					if(ypos > 640) ypos = 640;
					y_val = 0;	
				}
				checkQuizz = 0;	
				correct = 0;
				checkClick = 0;
				
			}
		}
	
		else if (y_val < 0) //PLAYER JUMPS
		{

			

			if (mapdata.tile[y1][x1] == QUIZZ1  ) {
				
				checkQuizz = 1;

				if(checkClick){
					checkQuizz = 0;
					cntQuizz ++;
					if(correct){
						playCorrect();
						score += 100;
						mapdata.tile[y1][x1] = 0;
						
					}
					else{
						playWrong();
						mapdata.tile[y1][x1] = 7;
						
					}
				}
				
			
			
			}
			else if (mapdata.tile[y2][x1] == TREASURE ){ 
					playWinGame();
					score += 1000;
					winGame = 1;	
			}
			else{
			if (mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y1][x2] != BLANK_TILE) {
				ypos = (y2 )*TILE_SIZE;
				if(ypos < 128 ) ypos = 128;
				if(ypos > 640) ypos = 640;
				y_val = 0;
			}

				checkQuizz = 0;	
				correct = 0;
				checkClick = 0;
				
			
			}
		}
	}
	if(!checkQuizz && !winGame){
		xpos += x_val;
		ypos += y_val;
	}
	if (xpos < 0) {
		xpos = 0;
	}
	else if ((xpos + widthframe) > mapdata.maxx) {
		xpos = mapdata.maxx - widthframe -1;
	}

	if (ypos < 0) {
		ypos = 0;
	}
}
void Player :: setQuizz(SDL_Renderer* renderer){
	
	char file_img[60];
	FILE* fp =NULL;

	for (int i = 0;i < 20;i++) {
		sprintf_s(file_img, "assets/quizz%d.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL) {
			continue;
		}
		fclose(fp);

		quizz[i].LoadImg(file_img, renderer);
		quizz[i].SetEntireRect(640, 128, 512, 512);
	}

	
}
void Player :: showQuizz(SDL_Renderer* renderer, int num){
    quizz[num].Render(renderer, nullptr);
}
bool Player :: checkLose(Map& mapdata){
	if(mapdata.tile[4][11] == WRONG && mapdata.tile[3][12] == WRONG){
		playLoseGame();
		return true;
	}
	if(mapdata.tile[7][11] == WRONG && mapdata.tile[5][14] == WRONG && mapdata.tile[4][16] == WRONG){
		playLoseGame();
		return true;
	}
	if(mapdata.tile[8][15] == WRONG && mapdata.tile[7][16] == WRONG ){
		playLoseGame();
		return true;
	}
	//map2
	if(mapdata.tile[4][10] == WRONG && mapdata.tile[3][12] == WRONG && mapdata.tile[2][13] == WRONG){
		playLoseGame();
		return true;
	}
	if(mapdata.tile[9][12] == WRONG && mapdata.tile[7][12] == WRONG && mapdata.tile[5][14] == WRONG && mapdata.tile[4][16] == WRONG){
		playLoseGame();
		return true;
	}
	if(mapdata.tile[8][15] == WRONG && mapdata.tile[7][16] == WRONG && mapdata.tile[6][17] == WRONG){
		playLoseGame();
		return true;
	}
	//map3
	if(mapdata.tile[9][12] == WRONG && mapdata.tile[7][13] == WRONG && mapdata.tile[5][14] == WRONG && mapdata.tile[4][16] == WRONG){
		playLoseGame();
		return true;
	}
	if(mapdata.tile[9][15] == WRONG && mapdata.tile[8][16] == WRONG && mapdata.tile[7][17] == WRONG){
		playLoseGame();
		return true;
	}

	return false;
}