#ifndef Background_H
#define Background_H
#include "SpriteResource.h"

class Background 
{
	public:
		Background();
		~Background();
		SpriteResource* resource; //call needed functions from SpriteResource
		void LoadBackgroundTexture(SDL_Renderer* ren); //loads the background image into memory
		void DrawBackground(SDL_Renderer* ren); //draws background
		void CleanUp(); //frees memory
		
	private:
		//SDL_Surface* mainBackground;
		SDL_Texture* backgroundTexture;
		SDL_Texture* starfield; 

		SDL_Rect box;

		int scrollingOffSet; 
		bool imagesLoaded; 
};

#endif