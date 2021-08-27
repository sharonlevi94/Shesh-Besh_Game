#include "Music.h"

//-----------------------------------------------------------------------------

Music::Music()
{
	m_soundBuffers.clear();
	//m_music.setVolume(MUSIC_VOLUME);

	setSounds();
}

//-----------------------------------------------------------------------------

Music& Music::instance() {
	static Music inst;
	return(inst);
}

//-----------------------------------------------------------------------------

void Music::playSound(SOUND soundKey) {
	m_sound.setBuffer(*m_soundBuffers.find(soundKey)->second);
	m_sound.play();
}

//-----------------------------------------------------------------------------

void Music::setSounds() {
	std::unique_ptr<sf::SoundBuffer> soundsCreator;
	//------------------------------------------------------------------------
	soundsCreator = std::make_unique<sf::SoundBuffer>();
	m_soundBuffers.insert(std::pair<SOUND, std::unique_ptr <sf::SoundBuffer>>
		(ROLL_SOUND, std::move(soundsCreator)));
	m_soundBuffers[ROLL_SOUND]->loadFromFile(ROLL_SOUND_PATH);

	//------------------------------------------------------------------------
	soundsCreator = std::make_unique<sf::SoundBuffer>();
	m_soundBuffers.insert(std::pair<SOUND, std::unique_ptr <sf::SoundBuffer>>
		(BUTTON, std::move(soundsCreator)));
	m_soundBuffers[BUTTON]->loadFromFile(BUTTON_SOUND_PATH);

	//------------------------------------------------------------------------
	soundsCreator = std::make_unique<sf::SoundBuffer>();
	m_soundBuffers.insert(std::pair<SOUND, std::unique_ptr <sf::SoundBuffer>>
		(PLAY_STEP, std::move(soundsCreator)));
	m_soundBuffers[PLAY_STEP]->loadFromFile(PLAY_SOUND_PATH);
}