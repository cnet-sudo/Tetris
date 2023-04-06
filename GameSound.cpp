

#include "GameSound.h"

void GameSound::play(int index) 
{
	if (GSound[index].getStatus() == sf::SoundSource::Status::Stopped ) GSound[index].play();
}

void GameSound::stop(int index) 
{
	if (GSound[index].getStatus() == sf::SoundSource::Status::Playing) GSound[index].stop();
}

void GameSound::AllStop()
{
	for (int i = 0; i < n; i++) if (GSound[i].getStatus() == sf::SoundSource::Status::Playing) GSound[i].stop();
}








