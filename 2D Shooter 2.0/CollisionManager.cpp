#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

//checks if there is a collision between 2 objects
bool CollisionManager::CheckCollision(const SDL_Rect &A, const SDL_Rect &B)
{
	int leftA = A.x, leftB = B.x;
	int topA = A.y, topB = B.y;
	int rightA = A.x + A.w, rightB = B.x + B.w;
	int bottomA = A.y + A.h, bottomB = B.y + B.h;

	if( bottomA <= topB )
        return false;
    
    if( topA >= bottomB )
        return false;
   
    if( rightA <= leftB )
        return false;
    
    
    if( leftA >= rightB )
        return false;
    
    return true;
}

bool CollisionManager::EnemyCollisions(EnemyShip1& enemy, Bullet& bullet, Explosions& explosion)
{
	//loop through the enemy and player bullet vectors and check for the collision
	//if there is a collision then destroy the bullet and enemy
	for(unsigned int i = 0; i < enemy.enemies.size(); i++)
	{
		for(unsigned int j = 0; j < bullet.bullets.size(); j++)
		{
			if (CheckCollision(enemy.enemies[i]->box_1, bullet.bullets[j]->box) || CheckCollision(enemy.enemies[i]->box_2, bullet.bullets[j]->box))
			{
				explosion.ExplosionHandler(enemy.enemies[i]->box.x, enemy.enemies[i]->box.y, 1); //add an explosion when an enemy dies
				enemy.enemies[i]->isAlive = false;	
				bullet.bullets[j]->isAlive = false; 
return true;
			}
		}
	}
	return false;
}

bool CollisionManager::EnemyBulletCollisions(Enemy1Bullet& bullet, Player& player, Explosions& explosion)
{
	//loop through the enemy bullet vector to check if any hit the player
	//if the player is hit destroy the bullet and decrease player health by 1
	for (unsigned int i = 0; i < bullet.enemyBullets.size(); i++)
	{
		if (CheckCollision(bullet.enemyBullets[i]->box, player.box_1) || CheckCollision(bullet.enemyBullets[i]->box, player.box_2))
		{
			explosion.ExplosionHandler(player.box.x, player.box.y - 20, 2); //this will play an explosion on the player when it gets hit
			bullet.enemyBullets[i]->isAlive = false;
			return true;
		}
	}
	return false;
}

bool CollisionManager::PlayerEnemyCollisions(EnemyShip1& enemy, Player& player, Explosions& explosion)
{
	//check if the enemy and player collide
	//if they do, destroy the enemy and decrease player health
	for (unsigned int i = 0; i < enemy.enemies.size(); i++)
	{
		if (CheckCollision(player.box_1, enemy.enemies[i]->box_1) || CheckCollision(player.box_1, enemy.enemies[i]->box_2) || CheckCollision(player.box_2, enemy.enemies[i]->box_1) || CheckCollision(player.box_2, enemy.enemies[i]->box_2))
		{
			explosion.ExplosionHandler(enemy.enemies[i]->box.x, enemy.enemies[i]->box.y, 1);//add an explosion when an enemy dies
			explosion.ExplosionHandler(player.box.x, player.box.y - 20, 2);
			enemy.enemies[i]->isAlive = false;
			return true;
		}
	}
	return false;
}

bool CollisionManager::BulletCollisions(Enemy1Bullet& enemyBullet, Bullet& bullet, Explosions& explosion)
{
	//checks if enemy and player bullets collide with each other and destroys them if they do 
	for (unsigned int i = 0; i < enemyBullet.enemyBullets.size(); i++)
	{
		for (unsigned int j = 0; j < bullet.bullets.size(); j++)
		{
			if (CheckCollision(enemyBullet.enemyBullets[i]->box, bullet.bullets[j]->box))
			{
				explosion.ExplosionHandler(bullet.bullets[j]->box.x - 20, bullet.bullets[j]->box.y - 35, 3);
				enemyBullet.enemyBullets[i]->isAlive = false;
				bullet.bullets[j]->isAlive = false;
				return true;
			}
		}
	}
	return false;
}

//handles collision for missiles and player
bool CollisionManager::PlayerMissileCollision(Player& player, EnemyMissile& missile, Explosions& explosion)
{
	for (unsigned int i = 0; i < missile.missiles.size(); i++)
	{
		if (CheckCollision(player.box_1, missile.missiles[i]->box) || CheckCollision(player.box_2, missile.missiles[i]->box))
		{
			explosion.ExplosionHandler(player.box.x, player.box.y - 20, 2);
			missile.missiles[i]->isAlive = false;
			return true;
		}
	}
	return false;
}

//handles collisions for missiles and player bullets
bool  CollisionManager::MissileBulletCollision(Bullet& bullet, EnemyMissile& missile, Explosions& explosion)
{
	for (unsigned int i = 0; i < missile.missiles.size(); i++)
	{
		for (unsigned int j = 0; j < bullet.bullets.size(); j++)
		{
			if (CheckCollision(missile.missiles[i]->box, bullet.bullets[j]->box))
			{
				missile.missiles[i]->isAlive = false;
				bullet.bullets[j]->isAlive = false;
				explosion.ExplosionHandler(bullet.bullets[j]->box.x - 20, bullet.bullets[j]->box.y - 35, 3);
				return true;
			}

		}
	}
	return false;
}

//handles collision for missiles and enemies
bool CollisionManager::EnemyMissileCollision(EnemyShip1& enemy, EnemyMissile& missile, Explosions& explosion)
{
	for (unsigned int i = 0; i < missile.missiles.size(); i++)
	{
		for (unsigned int j = 0; j < enemy.enemies.size(); j++)
		{
			if (CheckCollision(missile.missiles[i]->box, enemy.enemies[j]->box))
			{
				missile.missiles[i]->isAlive = false; 
				enemy.enemies[i]->isAlive = false; 
				explosion.ExplosionHandler(enemy.enemies[i]->box.x, enemy.enemies[i]->box.y, 1);
				return true; 
			}
		}
	}
	return false; 
}
