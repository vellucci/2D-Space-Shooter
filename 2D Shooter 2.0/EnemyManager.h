#pragma once
#ifndef EnemyManager_H
#define EnemyManager_H
#include "SpriteResource.h"
#include "EnemyShip1.h"
#include "Enemy1Bullet.h"
#include <vector> 
class EnemyManager
{
public:
	EnemyManager();

	void LoadEnemyFiles(SDL_Renderer* ren, EnemyShip1& Enemy); 
	void Handler(SDL_Renderer* ren, EnemyShip1& Enemy); //will loop through enemy vector and draw them
	void Shoot(SDL_Renderer* ren, EnemyShip1 Enemy); 

private:

};

#endif