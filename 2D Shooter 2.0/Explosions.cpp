#include "Explosions.h"

Explosions::Explosions()
{
	box.x = 0; 
	box.y = 0; 
	frame = 0; 
	explosionType = 0; 
}

Explosions::~Explosions()
{

}

void Explosions::LoadExplosions(SDL_Renderer* ren)
{
	TheSoundManager::Instance()->LoadSound("Explosion Sound.wav", "2", SOUND_SFX);
	spriteSheet = resource->LoadPNG("explosions.PNG", ren, 255, 0, 255);

	/*-----Set each spot in the array to a sprite on the sprite sheet--------*/
	spriteClips[0].x = 133;
	spriteClips[0].y = 3;
	spriteClips[0].h = 120;
	spriteClips[0].w = 120;

	spriteClips[1].x = 261;
	spriteClips[1].y = 3;
	spriteClips[1].h = 120;
	spriteClips[1].w = 120;

	spriteClips[2].x = 388;
	spriteClips[2].y = 3;
	spriteClips[2].h = 120;
	spriteClips[2].w = 120;

	spriteClips[3].x = 3;
	spriteClips[3].y = 133;
	spriteClips[3].h = 120;
	spriteClips[3].w = 120;

	spriteClips[4].x = 130;
	spriteClips[4].y = 132; 
	spriteClips[4].h = 120;
	spriteClips[4].w = 120;

	spriteClips[5].x = 258;
	spriteClips[5].y = 132;
	spriteClips[5].h = 120;
	spriteClips[5].w = 120;

	spriteClips[6].x = 386;
	spriteClips[6].y = 132;
	spriteClips[6].h = 120;
	spriteClips[6].w = 120;

	spriteClips[7].x = 3;
	spriteClips[7].y = 260;
	spriteClips[7].h = 120;
	spriteClips[7].w = 120;

	spriteClips[8].x = 130;
	spriteClips[8].y = 260;
	spriteClips[8].h = 120;
	spriteClips[8].w = 120;

	spriteClips[9].x = 258;
	spriteClips[9].y = 260;
	spriteClips[9].h = 120;
	spriteClips[9].w = 120;

	spriteClips[10].x = 386;
	spriteClips[10].y = 260;
	spriteClips[10].h = 120;
	spriteClips[10].w = 120;

	spriteClips[11].x = 3;
	spriteClips[11].y = 388;
	spriteClips[11].h = 120;
	spriteClips[11].w = 120;

	spriteClips[12].x = 130;
	spriteClips[12].y = 388;
	spriteClips[12].h = 120;
	spriteClips[12].w = 120;
	/*-------------End of enemy explosion sprites-------------------*/

}

void Explosions::DrawExplosion(SDL_Renderer* ren, SDL_Texture* tex, int x, int y, SDL_Rect* clip)  
{  
	SDL_Rect renderQuad = {x, y, clip->w, clip->h};
	SDL_RenderCopy(ren, tex, clip, &renderQuad);
}

void Explosions::UpdateEnemyExplosion(SDL_Renderer* ren, Player& player)
{	
	//loop through the vector and draw/update the explosions
	for (unsigned int i = 0; i < expVector.size(); i++)
	{
		/*-----------Display different explosions based on the value of explosionType----------------*/
		if (expVector[i]->explosionType == 1)
		{
			expVector[i]->currentClip = &spriteClips[expVector[i]->frame / 4]; //set each clip to a frame
			expVector[i]->DrawExplosion(ren, spriteSheet, expVector[i]->box.x, expVector[i]->box.y, expVector[i]->currentClip);

			++expVector[i]->frame; //play the next sprite of the explosion

			if ((expVector[i]->frame / 4) >= 13) //when the explosion reaches the last sprite, delete the object entirely
			{
				delete expVector[i];
				expVector.erase(expVector.begin() + i);
				i--;
			}
		}
		else if (expVector[i]->explosionType == 2)
		{
			expVector[i]->currentClip = &spriteClips[expVector[i]->frame / 4]; //set each clip to a frame
			expVector[i]->DrawExplosion(ren, spriteSheet, expVector[i]->box.x, expVector[i]->box.y, expVector[i]->currentClip);

			//update the type 2 explosions positions so it can either stay with the player while he moves
			expVector[i]->ExplosionPos(player.box.x, player.box.y - 20);

			++expVector[i]->frame; //play the next sprite of the explosion

			if ((expVector[i]->frame / 4) >= 4) //when the explosion reaches the last sprite, delete the object entirely
			{
				delete expVector[i];
				expVector.erase(expVector.begin() + i);
				i--;
			}
		}
		else //explosiion for when bullets collide
		{
			expVector[i]->currentClip = &spriteClips[expVector[i]->frame / 4]; //set each clip to a frame
			expVector[i]->DrawExplosion(ren, spriteSheet, expVector[i]->box.x, expVector[i]->box.y, expVector[i]->currentClip);

			++expVector[i]->frame;
			if ((expVector[i]->frame / 4) >= 4) //when the explosion reaches the last sprite, delete the object entirely
			{
				delete expVector[i];
				expVector.erase(expVector.begin() + i);
				i--;
			}
		}

	} 
}

//creates a new explosion object and adds it to the vector
void Explosions::ExplosionHandler(int x, int y, int expType)
{
	//create objects with different frame value for a different explosion based on value of expType
	Explosions* explosion = new Explosions();
	explosion->box.x = x;
	explosion->box.y = y;
	if (expType == 1)
	{
		explosion->explosionType = 1; 
		explosion->frame = 12;
	}
	else if (expType == 2)
	{
		explosion->explosionType = 2; 
		explosion->frame = 0;
	}
	else
	{
		explosion->explosionType = 3;
		explosion->frame = 0;
	}
	
	expVector.push_back(explosion);
}

void Explosions::ExplosionPos(int x, int y)
{
	box.x = x;
	box.y = y; 
}

void Explosions::CleanUp()
{
	SDL_DestroyTexture(spriteSheet);
}