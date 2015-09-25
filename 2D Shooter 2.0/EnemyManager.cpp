#include "EnemyManager.h"

EnemyManager::EnemyManager()
{


}

void LoadEnemyFiles(SDL_Renderer* ren, EnemyShip1& enemy)
{
	enemy.LoadEnemyShip1(ren); 
}

void EnemyManager::Handler(SDL_Renderer* ren, EnemyShip1& enemy)
{
	enemy.EnemyHandler();
}