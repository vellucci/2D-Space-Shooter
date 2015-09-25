#include "Bullet.h"

Bullet::Bullet()
{
	xVel = 25;
	yVel = 0;
	lastTime = 0;
	box.w = 40; 
	box.h = 10;
	isAlive = true; 
}


Bullet::~Bullet()
{
	
}

//load bullet sprite and sound effect
void Bullet::LoadBulletMedia(SDL_Renderer* ren)
{  
	TheSoundManager::Instance()->LoadSound("LaserShot.wav", "1", SOUND_SFX);
	TheSoundManager::Instance()->LoadSound("LaserExplode.wav", "4", SOUND_SFX);
	laser = resource->LoadPNG("laser.PNG", ren, 255, 0, 0);
}

void Bullet::DrawBullet(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	resource->RenderTexture(tex, ren, x, y, NULL);
}

//draw the bullets in the vector and move them
void Bullet::DrawBullets(SDL_Renderer* ren)
{ 
	for(unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->DrawBullet(laser, ren, bullets[i]->box.x, bullets[i]->box.y);
		bullets[i]->MoveBullet(); 

		//erase the bullets when they go off screen
		if(bullets[i]->box.x < -80)
		{
			bullets[i]->isAlive = false; 
		}

		if(!bullets[i]->isAlive)
		{
			delete bullets[i]; 
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void Bullet::MoveBullet()
{
	//move the bullet 
	box.x += xVel; 
}

void Bullet::BulletInput(SDL_Event& e, Player& player)
{
	currentTime = SDL_GetTicks(); 
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) 
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_SPACE: //add a bullet to the vector when space is pressed
				if(currentTime > lastTime + 300)
				{
					Shoot(player); 
					lastTime = currentTime; //time since last shot (reset cooldown)
					TheSoundManager::Instance()->PlaySound("1", 0);
				}
				break;
		}
	}
	else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
			case SDLK_SPACE:
				break; 
		}
	}
	
}

void Bullet::Shoot(Player& player)
{	
	//adds a new bullet object to the vector with is proper position to spawn it at
	Bullet* bullet = new Bullet(); 
	bullet->box.x = player.box.x + 25;
	bullet->box.y = player.box.y + 25;
	bullets.push_back(bullet); 	
}

void Bullet::CleanUp()
{
	SDL_DestroyTexture(laser); 
}