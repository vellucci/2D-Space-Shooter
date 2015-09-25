#pragma once
#ifndef EnemyMissile_H
#define EnemyMissile_H
#include "SpriteResource.h"
#include "Player.h"
#include <math.h> 
#include<vector>

#define PI 3.14159265

class EnemyMissile
{
public:
	EnemyMissile();
	~EnemyMissile();

	std::vector<EnemyMissile*> missiles;

	void LoadMissileMedia(SDL_Renderer* ren);
	void DrawMissile(SDL_Texture* tex, SDL_Renderer* ren, int x, int y);
	void UpdateMissiles(SDL_Renderer* ren, Player& player);
	void MoveMissile(Player& player, EnemyMissile* missile);

	void EnemyMissileHandler(int posX, int posY);

	void CleanUp(); 

	SpriteResource* resource;
	SDL_Rect box;
	bool isAlive; 
private:

	SDL_Texture* enemyMissile;

	unsigned int missileTimer;
	unsigned int currentTime;

	Mix_Chunk *missile_sound;

	int speed; 
	double angle;
	SDL_RendererFlip flipType;

};

#endif