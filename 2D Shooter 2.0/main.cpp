#include <SDL.h>
#include <stdio.h>
#include "Game.h"

int main( int argc, char* argv[] )
{
	Game game; //Initialize SDL and create the window then load the needed images
	
	bool quit = false; 
	 
	game.MainGameLoop();
	
	
  	return 0;
}