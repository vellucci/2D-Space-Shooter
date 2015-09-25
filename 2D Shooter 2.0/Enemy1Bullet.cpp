#include "Enemy1Bullet.h"

Enemy1Bullet::Enemy1Bullet()
{
	xVel = 17; 
	bulletTimer = 0;
	bool isAlive = true; 

	box.h = 12;
	box.w = 42; 
	box.x = 0; 
	box.y = 0; 
}

Enemy1Bullet::~Enemy1Bullet()
{

} 

void Enemy1Bullet::LoadBulletMedia(SDL_Renderer* ren)
{
	enemyLaser = resource->LoadPNG("EnemyLaser.png", ren, 0, 0, 0);
} 

void Enemy1Bullet::DrawBullet(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	resource->RenderTexture(tex, ren, x, y, NULL); 
}

void Enemy1Bullet::DrawBullets(SDL_Renderer* ren)
{
	//loop through the bullet vector and draw them 
	for(unsigned int i = 0; i < enemyBullets.size();  i++)
	{
		enemyBullets[i]->DrawBullet(enemyLaser, ren, enemyBullets[i]->box.x, enemyBullets[i]->box.y); 
		enemyBullets[i]->MoveBullet(); 

		if(enemyBullets[i]->box.x < -80) 
		{
			enemyBullets[i]->isAlive = false; 
		}

		if(!enemyBullets[i]->isAlive) //When isAlive is set to false, remove the bullet from the vector
		{
			delete enemyBullets[i]; 
			enemyBullets.erase(enemyBullets.begin() + i);
			i--; 
		}
	} 
}


void Enemy1Bullet::MoveBullet()
{
	box.x -= xVel;  
}

void Enemy1Bullet::CleanUp()
{
	SDL_DestroyTexture(enemyLaser);
}
