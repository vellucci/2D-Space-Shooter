#include "SpriteResource.h"

SpriteResource::SpriteResource()
{

}

SpriteResource::~SpriteResource()
{

}

bool SpriteResource::Initialize()
{
	srand(time(NULL));

    //Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return true;
    }
	else
	{
		std::cout << "SDL Initialized" << std::endl;

		//Initialize TTF if SDL is properly initialized
		if (TTF_Init() != 0)
			printf("TTF_Init() Failed", TTF_GetError());
		else
			printf("TTF Initialized\n");
	}

	return false;
}

SDL_Texture* SpriteResource::LoadPNG(const char* filename, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Texture* tex = nullptr;
	SDL_Surface* img = IMG_Load(filename);
	//SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, r, g, b));
	if (img != nullptr)
	{
		tex = SDL_CreateTextureFromSurface(ren, img);
		SDL_FreeSurface(img);
		if (tex == nullptr)
		{
			printf("CreateTextureFromSurface");
		}
		printf("texture %s created\n", +filename); 
	}
	else
	{
		printf("Unable to create texture %s! SDL Error: %s\n", + filename, SDL_GetError());
	}
	return tex;
}

TTF_Font* SpriteResource::LoadFont(const char* filename, int size)
{
	//Open the font
	TTF_Font * font = TTF_OpenFont(filename, size);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		printf("Font %s loaded \n", filename);
	}

	return font; 
}

void SpriteResource::RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect* clip)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, clip, &dst);
}

//this render function allows for sprite rotation
void SpriteResource::RenderTexture2(SDL_Renderer *ren, SDL_Texture *tex, int x, int y, int width, int height, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(ren, tex, clip, &renderQuad, angle, center, flip);
}

string SpriteResource::toString(int a)
{
	ostringstream temp;
	temp << a;
	return temp.str();
}

void SpriteResource::CleanUp(SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
}

//this loads and returns a texture with the proper string
SDL_Texture* SpriteResource::CreateTextTextures(SDL_Renderer* ren, TTF_Font* font, string stringText, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, stringText.c_str(), color);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);

	SDL_FreeSurface(surface);

	return texture; 
}

//this draws the TTF texture loaded with CreateTextTextures
void SpriteResource::RenderText(SDL_Renderer* ren, SDL_Texture* tex, int x, int y)
{
	SDL_Rect dst;

	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

	dst.x = x - (dst.w / 2);
	dst.y = y;

	SDL_RenderCopy(ren, tex, NULL, &dst);
}
