#pragma once
#ifndef EnemyShip1_H
#define EnemyShip1_H
#include "SpriteResource.h"
#include "Enemy1Bullet.h"
#include "EnemyMissile.h"
#include "SoundManager.h"
#include<vector>
class EnemyShip1 
{
	public:
		EnemyShip1();
		~EnemyShip1();

		SpriteResource* resource;

		std::vector<EnemyShip1*> enemies;
		std::vector<EnemyShip1> shit;

		void LoadEnemyShip1(SDL_Renderer* ren);
		void DrawEnemyTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y);
		void DrawEnemies(SDL_Renderer* ren, Enemy1Bullet &bullet, EnemyMissile &missile);//calls enemyHandler and draws enemies
		void MoveEnemy(EnemyShip1* ship);
		void EnemyHandler(); //creates enemies and puts them into vector

		void ShootBullet(SDL_Renderer* ren, int posX, int posY, Enemy1Bullet &bullets);
		void ShootMissile(SDL_Renderer* ren, int posX, int posY, EnemyMissile &missiles);

		//get the current position of the enemy
		int GetPositionX();
		int GetPositionY();

		void CleanUp(); 

		//variables used for certain enemy states
		int xVel; 
		bool isAlive; 
		bool shootMissile; 

		SDL_Rect box; //keeps track of enemy position

		//boxes to be used for collision
		SDL_Rect box_1;
		SDL_Rect box_2;

	private:
		SDL_Texture* enemy1Texture; 
		SDL_Texture* enemy2Texture;
		SDL_Texture* currentTexture;

		int sprite; 

		unsigned int lastTime;
		unsigned int currentTime; 
		
		unsigned int bulletTimer;
		unsigned int currentBulletTime;

		unsigned int missileTimer;
		unsigned int currentMissileTimer;
};
#endif