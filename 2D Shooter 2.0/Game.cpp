#include "Game.h"

Game::Game()
{
	ren = ren; 
	//initialize SDL/Mixer and create the window 
	resource->Initialize(); 
	TheSoundManager::Instance()->Load_SDL_Mixer();
	CreateWindow();
		
	//load and play main song
	TheSoundManager::Instance()->LoadSound("day 69.wav", "6", SOUND_MUSIC);
	TheSoundManager::Instance()->PlayMusic("6", 100);

	//load all the textures
	menu.LoadMedia(ren);
	background.LoadBackgroundTexture(ren);
	LoadGamePlayTextures();

	gameState = GSM_MENU; 

	quit = false;
}

Game::~Game()
{

}

void Game::CreateWindow()
{
	//screen = NULL;
	window = SDL_CreateWindow( "2D Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1400, 700, SDL_WINDOW_SHOWN );
	 
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		CreateRenderer(); //create the renderer if the window was created successfully
	}
}

void Game::CreateRenderer()
{
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		SDL_DestroyWindow(window);
		printf("Could not create renderer");
		SDL_Quit();
		return;
	}
	else
	{
		SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 0xFF );
	}
}

void Game::LoadGamePlayTextures()
{
	//load textures related to gameplay
	player.LoadPlayerMedia(ren);
	bullet.LoadBulletMedia(ren);
	enemy1.LoadEnemyShip1(ren);
	enemyBullet.LoadBulletMedia(ren);
	missile.LoadMissileMedia(ren);
	explosion.LoadExplosions(ren);
}


void Game::Run()
{
	//draws everything thats needed
	if (gameState == GSM_MENU) //draw whats needed during menu
	{
		background.DrawBackground(ren);
		menu.DrawMainMenu(ren);
	}
	else if(gameState == GSM_LEVEL) //draw proper objects when the game is being played
	{
		HandleCollision();
		player.Move();

		background.DrawBackground(ren);
		player.UpdatePlayer(ren);
		bullet.DrawBullets(ren);
		missile.UpdateMissiles(ren, player);
		enemy1.DrawEnemies(ren, enemyBullet, missile);
		explosion.UpdateEnemyExplosion(ren, player); 

		if (player.health == 0) //when health is zero, clear the vectors and reset the player and initialize the end menu
		{
			ClearVectors(); 
			player.CheckHighScore(ren);
			gameState = GSM_END; 
		}
	}
	else if (gameState == GSM_END)
	{
		//on game end, have a menu and show player score/high score
		background.DrawBackground(ren);
		menu.DrawEndMenu(ren);
		player.DrawTexts(ren);
	}
}

void Game::HandleCollision()
{
	/*-------------Handle Collision here-----------------*/
	if (ColManager.EnemyCollisions(enemy1, bullet, explosion))
	{
		player.score++; //if player kills enemy, add a point 
		TheSoundManager::Instance()->PlaySound("2", 0);
	}
	else if (ColManager.PlayerEnemyCollisions(enemy1, player, explosion))
	{
		player.health--; //if enemy and player collide, remove health
		TheSoundManager::Instance()->PlaySound("2", 0); //this plays the explosion sound when enemy dies
		//TheSoundManager::Instance()->PlaySound("3", 0); //this plays a sound when play gets hit
	}
	else if (ColManager.EnemyBulletCollisions(enemyBullet, player, explosion))
	{
		player.health--;  //if player and enemy bullet collide, remove health
		TheSoundManager::Instance()->PlaySound("3", 0); //this plays a sound when play gets hit
	}
	else if (ColManager.MissileBulletCollision(bullet, missile, explosion)) //collison of player bullets and enemy missiles
	{
		TheSoundManager::Instance()->PlaySound("3", 0);
	}
	else if (ColManager.BulletCollisions(enemyBullet, bullet, explosion)) //collison of player and enemy bullets
	{
		TheSoundManager::Instance()->PlaySound("4", 0);
	}
	else if (ColManager.PlayerMissileCollision(player, missile, explosion)) //collision of player and missile
	{
		TheSoundManager::Instance()->PlaySound("3", 0);
		player.health--; 
	}
	
	/*--------------End of collision code------------------*/
}

void Game::MainGameLoop()
{
		while (!quit)
		{
			SDL_Event event;

			if (gameState == GSM_LEVEL) //while the game is being played, handle the proper events
			{
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (event.type == SDL_KEYUP && event.key.repeat == 0)
					{
						switch (event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								quit = true; 
								break;
						}
					}

					bullet.BulletInput(event, player); //handles controls for player bullets
					player.HandlePlayerInput(event, ren); //handles controls for player
				}
			}
			else if (gameState == GSM_MENU) //when its the main menu, handle menu events
			{
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quit = true;			
					}

					if (event.type == SDL_KEYUP && event.key.repeat == 0)
					{
						switch (event.key.keysym.sym)
						{ 
							//new game when player presses 1 and quits when player presses 2
							case SDLK_1:
								//LoadGamePlayTextures();
								gameState = GSM_LEVEL;
								break;
							case SDLK_2:
								quit = true;
								break;
						}
					}

					menu.HandleMenuEvents(event);
				}
			}
			else if (gameState == GSM_END)
			{
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}

					if (event.type == SDL_KEYUP && event.key.repeat == 0)
					{
						switch (event.key.keysym.sym)
						{ 
							//new game when player presses 1 and quits when player presses 2
							case SDLK_1:
							//	LoadGamePlayTextures();
								gameState = GSM_LEVEL; 
								player.Reset(ren); //reset player class attributes on a new game
							break; 
							case SDLK_2:
								quit = true; 
							break; 
						}
					}
				}
			}

			SDL_RenderClear(ren);

			Run(); //draw loaded sprites

			SDL_RenderPresent(ren); //update the screen		
		}

		CleanUp();
} 

void Game::ClearVectors()
{
	//clear all the vectors when the game ends
	enemy1.enemies.clear();
	bullet.bullets.clear();
	enemyBullet.enemyBullets.clear(); 
	explosion.expVector.clear(); 
}

void Game::CleanUp()
{
	ClearVectors();
	bullet.CleanUp();
	enemy1.CleanUp(); 
	missile.CleanUp(); 
	explosion.CleanUp();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
}