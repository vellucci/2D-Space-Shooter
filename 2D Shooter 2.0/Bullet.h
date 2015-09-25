#pragma once
#ifndef Bullet_H
#define Bullet_H
#include "SpriteResource.h"
#include "Player.h"
#include "SoundManager.h"
#include<vector>

class Bullet  
{
	public:
		Bullet();
		~Bullet();

		SpriteResource* resource; 
		std::vector<Bullet*> bullets; 
		Player* ship; 

		void LoadBulletMedia(SDL_Renderer* ren); //load bullet media and sound effects 
		void DrawBullet(SDL_Texture* tex, SDL_Renderer* ren, int x, int y); //draw a bullet
		void DrawBullets(SDL_Renderer* ren); //draws all the bullets in the vector (calls DrawBullet as vector is being looped through)
		void MoveBullet();

		void Shoot(Player& player); //add a bullet to vector
		void BulletInput(SDL_Event& e, Player& player); //bullet input

		void CleanUp();

		SDL_Rect box;
		bool isAlive; 

	private:
		//velotcities of bullet
		int xVel, yVel;	

		SDL_Texture* laser;
		Mix_Chunk *bullet_sound;  

		bool shooting;

		unsigned int lastTime;
		unsigned int currentTime; 
 
};
#endif
