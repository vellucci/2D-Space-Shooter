#pragma once
#ifndef Player_H
#define Player_H
#include "SpriteResource.h"
#include "SoundManager.h"
#include<vector>
class Player 
{
	public:
		Player();
		~Player();
		
		SpriteResource* resource; //pointer to SpriteResource to load images

		//load player image and draw it
		void LoadPlayerMedia(SDL_Renderer* ren);
		void UpdatePlayer(SDL_Renderer* ren); 
		void DrawTexts(SDL_Renderer* ren);

		void HandlePlayerInput(SDL_Event& e, SDL_Renderer* ren);  //handles all player input
		void Move(); //moves the player
		
		//update TTF Textures for health and score to display the correct numbers
		void UpdateHealthTTF(SDL_Renderer* ren); 
		void UpdateScoreTTF(SDL_Renderer* ren);

		void CheckHighScore(SDL_Renderer* ren);
		
		void ResetScoreTTF(SDL_Renderer* ren); //reset the TTF texture of the health 
		void ResetHealthTTF(SDL_Renderer* ren); //reset TTF texture of the score 
		void Reset(SDL_Renderer* ren); //reset position/score/health when game over and calls ResetTTF functions

		//required texture
		SDL_Texture* player;
		SDL_Texture* hpTexture;
		SDL_Texture* scoreTexture; 
		SDL_Texture* highScoreTex; 

		string healthText; 
		string scoreText; 
		string highScoreSTR;

		int health;
		int updatedHealth; 

		int score;
		int updatedScore;
		int highScore; 


		SDL_Rect box; //used to keep track of movement

		//The box colliders
		SDL_Rect box_1; 
		SDL_Rect box_2; 
		
	private:

		//velocities for x and y axis and total speed and health
		int xVel, yVel;
		static const int speed = 10;	
	
		double shotCooldown; //timer so the player can't shoot every millisecond
		Mix_Chunk *player_impact;

		SDL_Surface* message; 
		TTF_Font *font;
		TTF_Font *menuFont;
		SDL_Color color;
};

#endif