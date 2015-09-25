#pragma once
#ifndef Explosions_H
#define Explosions_H
#include "SpriteResource.h"
#include "SoundManager.h"
#include "Player.h"

class Explosions
{
	public:
		Explosions();
		~Explosions(); 
		
		std::vector<Explosions*> expVector;
		std::vector<Explosions*> playerExpVector; 

		SpriteResource* resource;
		void LoadExplosions(SDL_Renderer* ren);
		void DrawExplosion(SDL_Renderer* ren, SDL_Texture* tex, int x, int y, SDL_Rect* clip);

		//will call the draw function and do the animations
		void UpdateEnemyExplosion(SDL_Renderer* ren, Player& player);

		//adds a new explosion to the vector
		void ExplosionHandler(int posX, int posY, int expType);

		//specifies explosion position, used for player explosions and bullet collisions
		void ExplosionPos(int x, int y);

		void CleanUp();	
		int frame; 
		SDL_Rect box;
	private:
		SDL_Texture* spriteSheet; 
		
		SDL_Rect spriteClips[13];

		SDL_Rect* currentClip; 
		int explosionType; 

};

#endif