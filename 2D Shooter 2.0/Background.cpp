#include "Background.h"

Background::Background() 
{
	box.x = 0;
	box.y = 0; 
	scrollingOffSet = 0;
	imagesLoaded = false;
}

Background::~Background()
{
	resource->CleanUp(backgroundTexture); 
}

void Background::LoadBackgroundTexture(SDL_Renderer* ren)
{
	backgroundTexture = resource->LoadPNG("SpaceBackground.PNG", ren, NULL, NULL, NULL); //load the texture
	//resource->LoadImage(backgroundTexture, "SpaceBackground.png", ren);
	starfield = resource->LoadPNG("starfield.PNG", ren, NULL, NULL, NULL); //load the texture
}

void Background::DrawBackground(SDL_Renderer* ren)
{
	//The background scrolling offset
	--scrollingOffSet;
	if(scrollingOffSet < -1400)
	{
		scrollingOffSet = 0;
	}

	resource->RenderTexture(backgroundTexture, ren, 0, 0, NULL);
	//resource->RenderTexture(backgroundTexture, ren, scrollingOffSet, 0, NULL);
	//resource->RenderTexture(backgroundTexture, ren, scrollingOffSet + 1400, 0, NULL);
	resource->RenderTexture(starfield, ren, scrollingOffSet, 0, NULL);
	resource->RenderTexture(starfield, ren, scrollingOffSet + 1400, 0, NULL);
}
