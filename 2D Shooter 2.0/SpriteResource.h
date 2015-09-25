#ifndef SpriteResource_H
#define SpriteResource_H
#include"Common.h"

class SpriteResource
{
	public:
		SpriteResource();
		~SpriteResource();

		bool Initialize();
		bool Initialize_Mixer(); 

		SDL_Texture* CreateTextTextures(SDL_Renderer* ren, TTF_Font* font, string stringText, SDL_Color color);
		SDL_Texture* LoadPNG(const char* filename, SDL_Renderer* ren, Uint8, Uint8, Uint8);
		TTF_Font* LoadFont(const char* filename, int size);

		void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect* clip);
		void RenderTexture2(SDL_Renderer *ren, SDL_Texture *tex, int x, int y, int width, int height, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip); //This render function allows for sprite rotation 
		void RenderText(SDL_Renderer* ren, SDL_Texture* tex, int x, int y);

		string toString(int a);

		void CleanUp(SDL_Texture* texture);
		void Close();

	private:
		
};

#endif

