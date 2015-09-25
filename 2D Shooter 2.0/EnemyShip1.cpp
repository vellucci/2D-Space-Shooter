#include "EnemyShip1.h"

EnemyShip1::EnemyShip1()
{
 	xVel = 8; 
	lastTime = 0; 
	bulletTimer = 0; 
	missileTimer = 0; 
	isAlive = true;
	sprite = 0; 

	//keeps track of position
	box.x = 100;
	box.y = 100; 

	/*---set box collider properties---*/
	//properties for enemy 1
	box_1.x = 0;
	box_1.y = 25; 
	box_1.w = 60;
	box_1.h = 20; 

	//properties for enemy 2
	box_2.x = 66;
	box_2.y = 3;
	box_2.w = 48;
	box_2.h = 77;
	/*-----------------------------*/
	shootMissile = true; 
}

EnemyShip1::~EnemyShip1()
{
	 
}

void EnemyShip1::LoadEnemyShip1(SDL_Renderer* ren)
{
	TheSoundManager::Instance()->LoadSound("enemyShot.wav", "-1", SOUND_SFX);
	enemy1Texture = resource->LoadPNG("EnemyShip1.png", ren, 255, 0, 0);  
	enemy2Texture = resource->LoadPNG("EnemyShip2.png", ren, 255, 0, 255);
	currentTexture = enemy1Texture; 
}

void EnemyShip1::DrawEnemyTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	resource->RenderTexture(tex, ren, x, y, NULL); 
}

void EnemyShip1::DrawEnemies(SDL_Renderer* ren, Enemy1Bullet &bullet, EnemyMissile &missile)
{ 
	//add enemies to the vector, loops through vector and draw
	EnemyHandler(); 
	for(unsigned int i = 0; i < enemies.size(); i++)
	{	
		//draw the correct sprite based on sprite number
		if(enemies[i]->sprite == 1)
		{ 
			enemies[i]->DrawEnemyTexture(enemy2Texture, ren, this->enemies[i]->box.x, this->enemies[i]->box.y);
		}
		else if (enemies[i]->sprite == 2)
		{
			enemies[i]->DrawEnemyTexture(enemy1Texture, ren, this->enemies[i]->box.x, this->enemies[i]->box.y);
		}
		enemies[i]->MoveEnemy(enemies[i]);

		if(enemies[i]->box.x < -80) //Set isAlive to false when they go off screen
		{
			enemies[i]->isAlive = false; 
		}

		if(enemies[i]->isAlive) //have an enemy shoot while it is actually alive 
		{
			if (enemies[i]->sprite == 1)
			{
				enemies[i]->ShootMissile(ren, enemies[i]->box.x, enemies[i]->box.y, missile);
			}
			else
			{
				enemies[i]->ShootBullet(ren, enemies[i]->box.x, enemies[i]->box.y, bullet);
			}		
		}
		else //delete the enemy from the vector when isAlive is set to false
		{ 
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			i--;
		}	
	}
	
	bullet.DrawBullets(ren); //draw the enemy bullets created with the ShootBullet function
}

void EnemyShip1::EnemyHandler()
{
	//every second, create a new enemy
	currentTime = SDL_GetTicks();
	if(currentTime > lastTime + 1000)
	{
		int texture = rand() % 10 + 1; 
		
		EnemyShip1 *ship = new EnemyShip1(); 

		//give a small chance to set the enemy as a different sprite
		if (texture == 1)
		{
			ship->sprite = 1;
		}
		else
		{
			ship->sprite = 2; 
		}
		
		//set where the enemy should spawn 
		ship->box.x = 1430;
		ship->box.y = rand() % 600 + 1; 

		enemies.push_back(ship); 
		lastTime = currentTime; 
	};
}

void EnemyShip1::ShootBullet(SDL_Renderer* ren, int posX, int posY, Enemy1Bullet &bullets)
{
	//Every two seconds the enemy will create a new bullet and add it to the enemy bullet vector
	currentBulletTime = SDL_GetTicks();
	if(currentBulletTime > bulletTimer + 2000)
	{
		Enemy1Bullet* bullet = new Enemy1Bullet(); 
		bullet->box.x = posX + 50; 
		bullet->box.y = posY + 30; 
		bullets.enemyBullets.push_back(bullet); 
		bulletTimer = currentBulletTime; 
	}
}

void EnemyShip1::ShootMissile(SDL_Renderer* ren, int posX, int posY, EnemyMissile &missileRef)
{
	//Every few seconds the enemy will create a new missile and add it to the enemy bullet vector
	currentMissileTimer = SDL_GetTicks();
	if (currentMissileTimer > missileTimer + 4000)
	{
		EnemyMissile* missile = new EnemyMissile();
		missile->box.x = posX + 50;
		missile->box.y = posY + 30;
		missileRef.missiles.push_back(missile);
		missileTimer = currentMissileTimer;
	}
}


void EnemyShip1::MoveEnemy(EnemyShip1* ship)
{
	box.x -= xVel;    
	
	ship->box_1.x = ship->box.x;
	ship->box_1.y = ship->box.y + 25;

	ship->box_2.x = ship->box.x + 66;
	ship->box_2.y = ship->box.y + 3;
}

void EnemyShip1::CleanUp()
{
	resource->CleanUp(enemy1Texture); 
}
