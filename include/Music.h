#pragma once
#include "Macros.h"
#include <SFML/Audio.hpp>
#include <unordered_map>

//-----------------------------------------------------------------------------

class Music
{
public:
	static Music& instance();
	void playSound(SOUND);
	/*void playMusic(int);
	void pauseMusic();*/

private:
	Music();
	std::unordered_map<SOUND, std::unique_ptr<sf::SoundBuffer>> m_soundBuffers;
	//sf::Music m_music;
	sf::Sound m_sound;
	void setSounds();
};