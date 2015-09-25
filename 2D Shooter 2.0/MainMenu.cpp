#include "MainMenu.h"

MainMenu::MainMenu()
{
	titleSTR = "Best Space Game Ever";
	playSTR = "Press 1 to Play";
	exitGame = "Press 2 to Exit";

	playAgainSTR = "Play 1 to Play Again";

	textColor = { 255, 0, 0 };

	playBox.x = 550; 
	playBox.y = 150;
	playBox.w = 100;
	playBox.h = 100; 
}

MainMenu::~MainMenu()
{

}

void MainMenu::LoadMedia(SDL_Renderer* ren)
{
	titleFont = resource->LoadFont("Sci Fied BoldItalic.ttf", 45);
	font = resource->LoadFont("Sci Fied BoldItalic.ttf", 30);

	//create the textures for the texts
	title = resource->CreateTextTextures(ren, titleFont, titleSTR, textColor);
	play = resource->CreateTextTextures(ren, font, playSTR, textColor);
	quit = resource->CreateTextTextures(ren, font, exitGame, textColor);
	playAgain = resource->CreateTextTextures(ren, font, playAgainSTR, textColor); 
}

void MainMenu::HandleMenuEvents(SDL_Event& event)
{
/*	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		//get the cursor's position
		int x, y;
		SDL_GetMouseState(&x, &y);
	}*/
}

void MainMenu::DrawMainMenu(SDL_Renderer* ren)
{
	//draw the textures
	resource->RenderText(ren, title, 1400 / 2, 50);
	resource->RenderText(ren, play, 1400 / 2, 210);
	resource->RenderText(ren, quit, 1400 / 2, 350);
}

void MainMenu::DrawEndMenu(SDL_Renderer* ren)
{
	//these are strings for the end menu
	resource->RenderText(ren, playAgain, 1400 / 2, 150); 
	resource->RenderText(ren, quit, 1400 / 2, 450);
}