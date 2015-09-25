#include "EnemyMissile.h"

EnemyMissile::EnemyMissile()
{
	speed = 10; 

	angle = 0; 
	flipType = SDL_FLIP_NONE;

	box.x = 0;
	box.y = 0;
	box.w = 60;
	box.h = 20; 

	isAlive = true; 
}

EnemyMissile::~EnemyMissile()
{

}

void EnemyMissile::LoadMissileMedia(SDL_Renderer* ren)
{
	enemyMissile = resource->LoadPNG("missile.PNG", ren, 255, 0, 255);
}

void EnemyMissile::DrawMissile(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	resource->RenderTexture2(ren, tex, x, y, box.w, box.h, NULL, angle, NULL, flipType);
}

void EnemyMissile::UpdateMissiles(SDL_Renderer* ren, Player& player)
{
	//loop through the vector and draw/move/delete missiles
	for (unsigned int i = 0; i < missiles.size(); i++)
	{
		missiles[i]->DrawMissile(enemyMissile, ren, missiles[i]->box.x, missiles[i]->box.y);
		missiles[i]->MoveMissile(player, missiles[i]);

		if (!missiles[i]->isAlive) //When isAlive is set to false, remove the bullet from the vector
		{
			delete missiles[i];
			missiles.erase(missiles.begin() + i);
			i--;
		}
	}
}

void EnemyMissile::MoveMissile(Player& player, EnemyMissile* missile)
{	
	//all this code allows the missile to follow the player
	SDL_Rect target;

	target.x = player.box.x - missile->box.x;
	target.y = player.box.y - missile->box.y; 
	
	missile->angle = atan2(target.y, target.x) * 180 / PI;
	
	double xVel = speed * (90 - abs(missile->angle)) / 90; 
	double yVel = 0; 

	if (missile->angle < 0)
	{
		yVel = -speed + abs(xVel);
	}
	else
	{
		yVel = speed - abs(xVel); 
	}
	
	missile->box.x += xVel; 
	missile->box.y += yVel; 
}

void EnemyMissile::CleanUp()
{
	SDL_DestroyTexture(enemyMissile);
}