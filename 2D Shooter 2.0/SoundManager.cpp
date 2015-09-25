#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance = NULL; 

SoundManager::SoundManager()
{
	
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

bool SoundManager::Load_SDL_Mixer()
{
	 //Initialize SDL_mixer
	 if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == 0)
     {
        return false;
     }
	 return true; 
}

bool SoundManager::LoadSound(std::string fileName, std::string id, sound_type type)
{
	if(type == SOUND_MUSIC) //if music is being loaded
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str()); //load the music

		if(pMusic == 0) //if pointer is empty (Music can't be loaded)
		{
			std::cout << "Could not load music: ERROR - "
			<< Mix_GetError() << std::endl;
			return false;
		}
		else
		{
			m_music[id] = pMusic; //store the music into the map
			std::cout << "Music Loaded " << std::endl;
			return true;
		}
	}
	else if(type == SOUND_SFX)	//if sound effect is being loaded
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
		if(pChunk == 0)
		{
			std::cout << "Could not load SFX: ERROR - "
			<< Mix_GetError() << std::endl;
			return false;
		}
		else
		{
			m_sfxs[id] = pChunk;
			return true;
		}
	}
	return false;
}

void SoundManager::PlayMusic(std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::PlaySound(std::string id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}