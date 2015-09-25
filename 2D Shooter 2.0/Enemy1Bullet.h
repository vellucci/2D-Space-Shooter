#pragma once
#ifndef Enemy1Bullet_H
#define Enemy1Bullet_H
#include "SpriteResource.h"
#include "Player.h"
#include<vector>

class Enemy1Bullet 
{
public:
	 
	Enemy1Bullet();
	~Enemy1Bullet(); 

	SpriteResource* resource; 
	std::vector<Enemy1Bullet*> enemyBullets; 
	
	void LoadBulletMedia(SDL_Renderer* ren); //load bullet media and sound effects 
	void DrawBullet(SDL_Texture* tex, SDL_Renderer* ren, int x, int y); //draw a bullet
	void DrawBullets(SDL_Renderer* ren); //draws all the bullets in the vector (calls DrawBullet as vector is being looped through)

	void EnemyBulletHandler(int posX, int posY); //will create bullets to add them to vector
	void MoveBullet();
	void MoveMissile();

	void CleanUp();

	SDL_Rect box;
	bool isAlive; 

private:

	SDL_Texture* enemyLaser; 

	unsigned int bulletTimer;
	unsigned int currentTime;

	Mix_Chunk *bullet_sound; 
	int xVel;
};

#endif
