#pragma once
#include<array>
#include<SFML/Audio.hpp>
#include "AssetManager.h"

class GameSound
{   static const int n = 3;
	std::array<sf::Sound, n> GSound; 	
		
public:
	
	GameSound()
	{
		std::array<std::string, n> namefilebuf{ "sound/fon.ogg" ,"sound/deadline.ogg","sound/game_over.ogg"};
		
		for (int i = 0; i < n; i++) {
		GSound[i].setBuffer(AssetManager::GetSoundBuffer(namefilebuf[i]));
		if (i == 0) GSound[i].setLoop(true);
		}
	};

	void play(int index);
	void stop(int index);
	void AllStop();
};

