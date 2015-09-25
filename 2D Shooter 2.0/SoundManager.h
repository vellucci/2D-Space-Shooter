#pragma once
#ifndef SoundManager_H
#define SoundManager_H
#include "SpriteResource.h"
#include<map>
#include<vector>
#include<string>
enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
	public:
		
		static SoundManager* Instance()
		{
			if(s_pInstance == 0)
			{
				s_pInstance = new SoundManager();
				return s_pInstance;
			}
			return s_pInstance;
		}

		bool LoadSound(std::string fileName, std::string id, sound_type type);
		bool Load_SDL_Mixer(); 

		void PlaySound(std::string id, int loop);
		void PlayMusic(std::string id, int loop);

	private:

		static SoundManager* s_pInstance;

		//maps to store pointers of Mix_Chunk or Mix_Music
		std::map<std::string, Mix_Chunk*> m_sfxs;
		std::map<std::string, Mix_Music*> m_music;

		SoundManager();
		~SoundManager();

		SoundManager(const SoundManager&);
		SoundManager &operator=(const SoundManager&);
};

typedef SoundManager TheSoundManager;
#endif