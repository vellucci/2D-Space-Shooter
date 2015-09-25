#ifndef Game_H
#define Game_H
#include "SpriteResource.h"
#include "Player.h"
#include "Background.h"
#include "Bullet.h"
#include "EnemyShip1.h"
#include "Enemy1Bullet.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "EnemyMissile.h"
#include "Explosions.h"
#include "MainMenu.h"

enum GameState { GSM_MENU, GSM_LEVEL, GSM_END };

class Game
{
	public:
		//main objects of the game
		Game();
		~Game();
		SpriteResource* resource; //pointer to initialize functions

		//all game objects
		Background background;
		Player player; 
		Bullet bullet; 

		EnemyShip1 enemy1; 
		Enemy1Bullet enemyBullet; 
		EnemyMissile missile; 
		MainMenu menu; 

		CollisionManager ColManager; 
		Explosions explosion; 

		void CreateWindow();  
		void CreateRenderer();
		void LoadGamePlayTextures(); 
		void Run(); //draws all textures
		void MainGameLoop();
		void HandleCollision(); 
		void LoadMedia();
		void ClearVectors();
		void CleanUp(); 

	private:
		SDL_Window* window;
		SDL_Renderer *ren;
		SDL_Event gameEvent; 
		bool quit;

		int currentTime;
		int lastTime; 

		GameState gameState; 
};

#endif