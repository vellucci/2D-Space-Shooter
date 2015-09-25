#pragma once
#ifndef CollisionManager_H
#define CollisionManager_H
#include "SpriteResource.h"
#include "Player.h"
#include "EnemyShip1.h"
#include "Enemy1Bullet.h"
#include "Bullet.h"
#include "Explosions.h"

class CollisionManager
{
	public:
		CollisionManager();

		//make to functions to check collision since objects have more than one box collider
		bool CheckCollision(const SDL_Rect &rect1, const SDL_Rect &rect2);
      
		bool EnemyCollisions(EnemyShip1& enemy, Bullet& bullet, Explosions& explosion); 
		bool PlayerEnemyCollisions(EnemyShip1& enemy, Player& player, Explosions& explosion); 
		bool EnemyBulletCollisions(Enemy1Bullet& bullet, Player& player, Explosions& explosion);
		bool BulletCollisions(Enemy1Bullet& enemyBullet, Bullet& bullet, Explosions& explosion);
		bool PlayerMissileCollision(Player& player, EnemyMissile& missile, Explosions& explosion);
		bool MissileBulletCollision(Bullet& bullet, EnemyMissile& missile, Explosions& explosion);
		bool EnemyMissileCollision(EnemyShip1& enemy, EnemyMissile& missile, Explosions& explosion);

	private:

};

#endif
