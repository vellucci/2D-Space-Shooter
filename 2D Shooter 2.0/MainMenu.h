#ifndef MainMenu_H
#define MainMenu_H
#include "SpriteResource.h"

class MainMenu
{
	public:
		MainMenu();
		~MainMenu();
		SpriteResource* resource;

		void LoadMedia(SDL_Renderer* ren);
		void DrawMainMenu(SDL_Renderer* ren);
		void DrawEndMenu(SDL_Renderer* ren); 
		void HandleMenuEvents(SDL_Event& event); //will handle the mouse events when player chooses play/exit game
		
		//strings that will be used for the text
		string playSTR;
		string exitGame;
		string titleSTR; 
		string playAgainSTR;
		
	private:
		//TTF_Font *font;
		SDL_Color textColor; 

		SDL_Rect playBox; 
		SDL_Rect exitBox;

		//textures that will be used for the text
		SDL_Texture* title;
		SDL_Texture* play;
		SDL_Texture* quit; 
		SDL_Texture* playAgain;

		TTF_Font *titleFont;
		TTF_Font *font;
};

#endif 