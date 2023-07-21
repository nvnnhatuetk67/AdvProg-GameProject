#include "CommonFunction.h"
#include "BaseObj.h"
#include "initSDL.h"
#include "gamemap.h"
#include "Player.h"
#include "ImpTimer.h"
#include "Text.h"
#include "sound.h"

using namespace std;
BaseObj gbackground;
BaseObj floor;
TTF_Font* font = TTF_OpenFont("fonts/04B_19__.TTF", 64);
Mix_Music* music = loadMusic("sounds/bgm.wav", music);
Mix_Music* musicMenu = loadMusic("sounds/bgm.wav", musicMenu);
Mix_Music* musicIngame = loadMusic("sounds/ingame.wav", musicIngame);
bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
int main(int arcs, char* argv[]) {

    ImpTimer fps_timer;
	//Create game screen

    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* texture = NULL;
    initSDL(window, renderer);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("fonts/04B_19__.ttf", 28);
    SDL_SetRenderDrawColor(renderer, 10, 10, 10 ,255 );
    SDL_RenderClear(renderer);

    gbackground.LoadImg("assets/BG.png", renderer);
    gbackground.SetSizeRect(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    floor.LoadImg("assets/floor.png", renderer);
    floor.SetRect(640,128);
    floor.SetSizeRect(512,512);
    BaseObj scoreTable;
    scoreTable.LoadImg("assets/scoring.png", renderer);
    scoreTable.SetEntireRect(64,64, 448, 640 );

    Player player;
    player.LoadImg("assets/char_right.png", renderer);
    player.setPos(640, 128);
    player.setclip();
    player.setQuizz(renderer);
    player.setDisplayQuizz();
    //player.checkDisplayQuizz();
    
    if(font == nullptr){
        cout << "Cann't load font!\n";
    }

    GameMap game_map;
    game_map.LoadMap("map/map1.txt");
    game_map.LoadTiles(renderer);
    Map mainMap = game_map.getMap();
    Text time_game;
    time_game.SetColor(Text ::GREEN);
    Text score_game;
    score_game.SetColor(Text :: GREEN);
    Text time_result;
    time_result.SetColor(Text :: BLACK);

    playMusic(music);
    BaseObj menu;
    menu.LoadImg("assets/menu.png", renderer);
    menu.SetEntireRect(448, 64, 448, 640);
    BaseObj playButton;
    playButton.LoadImg("assets/play.png", renderer);
    playButton.SetEntireRect(610, 355, 128, 128);
    BaseObj about;
    about.LoadImg("assets/about.png", renderer);
    about.SetEntireRect(516,547, 90 , 90);

    BaseObj tutorial;
    tutorial.LoadImg("assets/tutorial.png", renderer);
    tutorial.SetEntireRect(192, 64, 896, 640 );
    BaseObj back;
    back.LoadImg("assets/prew.png", renderer);
    back.SetEntireRect(256, 110, 64, 64);

    BaseObj rank;
    rank.LoadImg("assets/rank.png", renderer);
    rank.SetEntireRect(620, 547, 90, 90);
    BaseObj rankTable;
    rankTable.LoadImg("assets/ranktable.png", renderer);
    rankTable.SetEntireRect(192, 64, 896, 640 );

    Text highScore;
    highScore.SetColor(Text :: ORANGE);
    Text time_hScore;
    time_hScore.SetColor(Text ::ORANGE );
    
    BaseObj closeGame;
    closeGame.LoadImg("assets/closeGame.png",renderer);
    closeGame.SetEntireRect(726, 547, 90 ,90);
    BaseObj wingame;
    wingame.LoadImg("assets/winGame.png", renderer);
    wingame.SetEntireRect(448, 64, 448, 640);
    BaseObj reload;
    reload.LoadImg("assets/reload.png", renderer);
    reload.SetEntireRect(516,547, 90 , 90);
    BaseObj Lose;
    Lose.LoadImg("assets/losegame.png", renderer);
    Lose.SetEntireRect(448, 64, 448, 640);

    //Set mute image
    BaseObj Mute;
    Mute.SetEntireRect(10, 10, 60, 60);
    mute = loadTexture("assets/music.png", renderer);
    player.setMuteImage(mute);

    bool running = 1;
    bool checkMenu = 1;
    bool checkWin = 0;
    bool checkIntro = 0;
    bool loseGame = 0;
    bool checkRanking = 0;
    
   
    // Time to play game
    Uint32 start_time = SDL_GetTicks()/1000;
    Uint32 val_time = 300;
    Uint32 time_val;
    int sec;
    int min;
    SDL_Event eMute;
    while(running){
        // render background
        checkWin = player.getWingame();
        gbackground.Render(renderer, nullptr);
        Mute.setTexture(mute);
        Mute.Render(renderer, nullptr);
        //--------------------------------------------
        //------------------Menu----------------------
        //--------------------------------------------
        if(checkMenu ){
            
            if(!Mix_PlayingMusic()){
                
                playMusic(music);
            }
            menu.Render(renderer, nullptr);
            playButton.Render(renderer, nullptr);
            about.Render(renderer, nullptr);
            rank.Render(renderer, nullptr);
            closeGame.Render(renderer, nullptr);
            if(checkIntro ){
                tutorial.Render(renderer, nullptr);
                back.Render(renderer, nullptr);
            }
            if(checkRanking ){
               
                rankTable.Render(renderer, nullptr);
                back.Render(renderer, nullptr);

                // Show highscore
                ifstream infile("map/game_save.txt");
                int score, min , sec ;
                infile >> score;
                string scoreText = to_string(score);
                highScore.SetText(scoreText);
                highScore.LoadFont(font, renderer);
                highScore.SetSizeText(128, 64);
                highScore.RenderText(renderer, 576,256);

                infile >> min;
                infile >> sec;
                string str_min = min < 10 ? "0" + to_string(min) : to_string(min) ;
                string str_sec = sec < 10 ? "0" + to_string(sec) : to_string(sec);
                string str_time = "Time: " + str_min + " : " + str_sec;
                time_hScore.SetText(str_time);
                time_hScore.LoadFont(font, renderer);
                time_hScore.RenderText(renderer, 544 ,384);
                infile.close();

            }
            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_QUIT){
                    running = 0;
                    
                }
                
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    if(event.button.button == SDL_BUTTON_LEFT){
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        //(610, 355, 128, 128)
                        if((x > 610 && x < 738 )&&( y > 355 && y < 483)){
                            checkMenu = 0;
                        }
                        //(256, 110, 64, 64)
                        if(!checkIntro && ! checkRanking){
                            if((x > 516 && x < 606 )&&( y > 547 && y < 637)){
                                checkIntro = 1;
                                checkRanking = 0;
                                
                            }
                        }
                        else{
                             if((x > 256 && x < 320 )&&( y > 110 && y < 174)){
                                checkIntro = 0;
                            }
                        }
                         if(!checkRanking && !checkIntro){
                            if(CheckFocusWithRect(x , y, rank.getRect())){
                                checkRanking = 1;
                                checkIntro = 0;
                               
                            }
                        }
                        else{
                             if(CheckFocusWithRect(x , y, back.getRect())){
                                checkRanking= 0;
                            }
                        }
                        //(726, 547, 90 ,90
                        if((x > 726 && x < 816 )&&( y > 547 && y < 637)){
                            running = 0; 
                             
                        }
                        //update mute image
                        mute = muteSound(renderer, mute, x, y);
                    }
                }
             }
        }
        //----------------------------
        //----------Ingame------------
        //----------------------------
        else{
            if(!checkWin && !loseGame){
                //isGamePlaying

                if(!Mix_PlayingMusic() ){
                    playMusic(music);
                }
                //timer
                fps_timer.start();
                while(SDL_PollEvent(&event)) {
                    if(event.type == SDL_QUIT){
                        running = 0;
                       
                    }
                  
                   
                    player.handleInputAction(event, renderer);         
                }   
                    mute = player.getMute();

                    floor.Render(renderer, nullptr);
                    scoreTable.Render(renderer, nullptr);
                    
                    Map mapdata = game_map.getMap();
                    player.DoPlayer(mapdata);
                    loseGame = player.checkLose(mapdata);
                    game_map.SetMap(mapdata);
                    game_map.DrawMap(renderer);

                    player.show(renderer);
                    //Show score 
                    int score = player.getScore();
                    string str_score = score < 10 ? "0" + to_string(score) : to_string(score) ;
                    score_game.SetText(str_score);
                    score_game.LoadFont(font, renderer);
                    score_game.SetSizeText(120, 90);
                    score_game.RenderText(renderer, 230, 320);
                    
                
                    
                    //Handle game time
                    string str_time ;

                    time_val = SDL_GetTicks()/1000;
                    val_time = 300 - (time_val - start_time);
                    min = val_time / 60;
                    sec = val_time % 60;

                    if(val_time <=0 ){
                        // if time run out, you lose.
                        loseGame = 1;
                    }
                    else {
                        string str_min = min < 10 ? "0" + to_string(min) : to_string(min) ;
                        string str_sec = sec < 10 ? "0" + to_string(sec) : to_string(sec);
                        str_time = "Time: " + str_min + " : " + str_sec;
                        time_game.SetText(str_time);
                        time_game.LoadFont(font, renderer);
                        time_game.RenderText(renderer, 192 , 578);

                        string str_mins = 4 - min < 10 ? "0" + to_string(4 - min) : to_string(4 - min) ;
                        string str_secs = 60 - sec < 10 ? "0" + to_string(60 - sec) : to_string(60 - sec);
                        string str_times = "Your Time: " + str_mins + " : " + str_secs;
                        time_result.SetText(str_times);
                        time_result.LoadFont(font, renderer);
                    }
            }
        }
        //----------------------------
        //----------Win Game----------
        //----------------------------
        if(checkWin){
                
                // Reset time
                start_time = SDL_GetTicks()/1000;
                val_time = 300;

                // Show wingame screen
                wingame.Render(renderer, nullptr);
                closeGame.Render(renderer,nullptr);
                reload.Render(renderer, nullptr);
                score_game.RenderText(renderer, 605, 380 );

                // Save socre and time 
                ifstream infile("map/game_save.txt");
                int score, mins , secs ;
                if(infile.is_open()){
                    infile >> score;
                    infile >> mins;
                    infile >> secs ;
                    infile.close();

                }
                ofstream outfile("map/game_save.txt");
                if(outfile.is_open()){
                    int s ,m;
                    int num = score < player.getScore() ? player.getScore()  : score ;
                    if(score == player.getScore()){
                     s = secs < 60 - sec ? secs : (60 - sec);
                     m = mins < 4 - min ? mins :( 4 - min);
                    }else {
                        s = 60 - sec;
                        m =  4 - min;
                    }
                    outfile << num << "\n";
                    outfile << m << "\n";
                    outfile << s << "\n";
                    outfile.close();
                }
                else{
                    cout << "Error to open file!\n";
                }
               

                time_result.RenderText(renderer, 550, 520);
                SDL_Event e;
                while(SDL_PollEvent(&e)) {
                    if(e.type == SDL_QUIT){
                        running = 0;
                        
                    }
                    if(e.type == SDL_MOUSEBUTTONDOWN){
                        if(e.button.button == SDL_BUTTON_LEFT){
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            player.setDisplayQuizz();
                            //(516,547, 90 , 90)
                            if((x > 516 && x < 606 )&&( y > 547 && y < 637)){
                                player.resetAnimation();
                                player.setPos(640, 128);
                                game_map.SetMap(mainMap);
                                player.setWingame(0);
                                player.setScore(0);
                                checkMenu = 1;
                                
                              
                               
                            }
                            //(726, 547, 90 ,90)
                            if((x > 726 && x < 816 )&&( y > 547 && y < 637)){
                                running = 0;
                                
                                
                            }
                            mute = muteSound(renderer, mute, x, y);
                        }
                    }
             }
        }
         //----------------------------
        //----------Lose Game----------
        //----------------------------
        if(loseGame){
                
                 player.resetBool();
                //Reset time
                start_time = SDL_GetTicks()/1000;
                val_time = 300;
                // Show lose screen
                Lose.Render(renderer, nullptr);
                closeGame.Render(renderer,nullptr);
                reload.Render(renderer, nullptr);
                score_game.RenderText(renderer, 605, 430 );
                SDL_Event e;
                while(SDL_PollEvent(&e)) {
                    if(e.type == SDL_QUIT){
                        running = 0;
                        
                    }
                    if(e.type == SDL_MOUSEBUTTONDOWN){
                        if(e.button.button == SDL_BUTTON_LEFT){
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                             player.setDisplayQuizz();
                            //(516,547, 90 , 90)
                            if((x > 516 && x < 606 )&&( y > 547 && y < 637)){
                                player.resetAnimation();
                                player.setPos(640, 128);
                                game_map.SetMap(mainMap);
                                loseGame = 0;
                                player.setScore(0);
                                checkMenu = 1;
                               
                            }
                            //(726, 547, 90 ,90)
                            if((x > 726 && x < 816 )&&( y > 547 && y < 637)){
                                running = 0;
                                
                            }
                            mute = muteSound(renderer, mute, x, y);
                        }
                    }
             }
        }

        //Show all
        SDL_RenderPresent(renderer);
            //Timer
        int real_inp_time = fps_timer.get_tick();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if(real_inp_time < time_one_frame){
            int delay_time = time_one_frame - real_inp_time;
            if(delay_time >= 0)
                SDL_Delay(delay_time);
        }

    }
    Mix_FreeMusic(musicIngame);
    Mix_FreeMusic(musicMenu);
    
	//waitUntilKeyPressed();
    quitSDL(window, renderer);
	return 0;
}
bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}
