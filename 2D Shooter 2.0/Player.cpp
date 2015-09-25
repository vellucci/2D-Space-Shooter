#include "Player.h"

Player::Player() 
{
	xVel = 0;
	yVel = 0;

	health = 10; 
	updatedHealth = 10; 

	score = 0; 
	updatedScore = 0; 
	highScore = 0; 

	//set box properties
	box.x = 100;
	box.y = 100;

	/*-----set box collider properties-----*/
	box_1.x = 9;
	box_1.y = 16;
	box_1.w = 64;
	box_1.h = 48;

	box_2.x = 69;
	box_2.y = 27; 
	box_2.w = 46;
	box_2.h = 18; 
	/*------------------------------------*/

	//color for text
	color = { 255, 0, 0 };

	highScoreSTR = "High Score: " + resource->toString(highScore);
	healthText = "Health: " + resource->toString(health);
	scoreText = "Score: " + resource->toString(score);
}

//clean up every texture
Player::~Player()
{
	resource->CleanUp(player);
}

//load all player media
void Player::LoadPlayerMedia(SDL_Renderer* ren)
{
	TheSoundManager::Instance()->LoadSound("PlayerHit.wav", "3", SOUND_SFX);
	player = resource->LoadPNG("Player.PNG", ren, 255, 0, 255); 

	//load the fonts
	font = resource->LoadFont("Sci Fied BoldItalic.ttf", 20);
	menuFont = resource->LoadFont("Sci Fied BoldItalic.ttf", 30);

	//load texture for the player health and score
	hpTexture = resource->CreateTextTextures(ren, font, healthText, color); 
	scoreTexture = resource->CreateTextTextures(ren, font, scoreText, color); 
	highScoreTex = resource->CreateTextTextures(ren, font, highScoreSTR, color);
}
 
void Player::UpdatePlayer(SDL_Renderer* ren)
{
	resource->RenderTexture(player, ren, box.x, box.y, NULL);

	//strings for health and score while game is being played
	resource->RenderText(ren, hpTexture, 75, 0);
	resource->RenderText(ren, scoreTexture, 1400 / 2, 0); 
	UpdateScoreTTF(ren);
	UpdateHealthTTF(ren); 
}

void Player::DrawTexts(SDL_Renderer* ren)
{
	//this is to show the high score during the main menu
	resource->RenderText(ren, scoreTexture, 1400 / 2, 250);
	resource->RenderText(ren, highScoreTex, 1400 / 2, 350);
}

void Player::HandlePlayerInput(SDL_Event& e, SDL_Renderer* ren)
{
	//adjust the velocity and change the image direction based on the keypress
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//moves player based on key the player presses
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: yVel -= speed; 
				break;
            case SDLK_DOWN: yVel += speed; 
				break;
            case SDLK_LEFT: 
				xVel -= speed; 
				break;
            case SDLK_RIGHT: 
				xVel += speed; 
				break;   
			
        }
    }
	else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity when the player releases a key
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: yVel += speed; break;
            case SDLK_DOWN: yVel -= speed; break;
            case SDLK_LEFT: xVel +=  speed; break;
            case SDLK_RIGHT: xVel -= speed; break;  
        }        
    }	

}

void Player::Move()
{
	//move the player left or right
	box.x += xVel; 
	box_1.x = box.x + 9; 
	box_2.x = box.x + 69;

	//If the player went too far to the left or right
    if(( box.x < 0 ) || (box.x > 600))
    {
        //Move back
        box.x -= xVel;
    }

	//move up or down
	box.y += yVel;
	box_1.y = box.y + 16; 
	box_2.y = box.y + 27; 

	if((box.y < 0) || (box.y > 600))
	{
		box.y -= yVel;
	}
}

void Player::Reset(SDL_Renderer* ren)
{
	//reset the player stats on a new game
	health = 10; 
	score = 0; 
	box.x = 100; 
	box.y = 100; 
	xVel = 0;
	yVel = 0; 
	//on a new game, destroy and reload TTF textures to reset them
	ResetHealthTTF(ren);
	ResetScoreTTF(ren);
}

void Player::UpdateScoreTTF(SDL_Renderer* ren)
{
	//when the score is updated, we need to reload the texture to properly display the new score (SDL_TTF is dumb)
	if (score > updatedScore)
	{ 
		SDL_DestroyTexture(scoreTexture);
		scoreText = "Score: " + resource->toString(score);
		scoreTexture = resource->CreateTextTextures(ren, font, scoreText, color);
		updatedScore = score;

		SDL_DestroyTexture(highScoreTex);
		highScoreSTR = "High Score: " + resource->toString(highScore);
		highScoreTex = resource->CreateTextTextures(ren, font, highScoreSTR, color);
	}
}

void Player::UpdateHealthTTF(SDL_Renderer* ren)
{
	//when the health is updated, we need to reload the texture to properly display the new score (SDL_TTF is dumb)
	if (health < updatedHealth)
	{
		SDL_DestroyTexture(hpTexture);
		healthText = "Health: " + resource->toString(health);
		hpTexture = resource->CreateTextTextures(ren, font, healthText, color);
		updatedHealth = health; 
	}
}


void Player::CheckHighScore(SDL_Renderer* ren)
{
	if (score > highScore)
	{
		highScore = score;

		SDL_DestroyTexture(highScoreTex);
		highScoreSTR = "High Score: " + resource->toString(highScore);
		highScoreTex = resource->CreateTextTextures(ren, font, highScoreSTR, color);
	}
}

void Player::ResetHealthTTF(SDL_Renderer* ren)
{
	SDL_DestroyTexture(hpTexture);
	healthText = "Health: " + resource->toString(health);
	hpTexture = resource->CreateTextTextures(ren, font, healthText, color);
	updatedScore = score;
}

void Player::ResetScoreTTF(SDL_Renderer* ren)
{
	SDL_DestroyTexture(scoreTexture);
	scoreText = "Score: " + resource->toString(score);
	scoreTexture = resource->CreateTextTextures(ren, font, scoreText, color);
	updatedHealth = health; 
}