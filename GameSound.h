#pragma once
#include<array>
#include<SFML/Audio.hpp>
#include "AssetManager.h"

class GameSound
{   
	// количество звуковых эффектов
	static const int n = 5;
	// массив объектов звуковых эффектов
    std::array<sf::Sound, n> GSound; 	
		
public:
	
	GameSound()
	{
		// массив названий файлов и путей расположения звуковых эффектов
		std::array<std::string, n> namefilebuf{ "sound/fon.ogg" ,"sound/deadline.ogg","sound/game_over.ogg",
		"sound/movetetramino.ogg","sound/svist.ogg"};
		// цикл присвоения звуковым объектам звуковых эффектов
		for (int i = 0; i < n; i++) GSound[i].setBuffer(AssetManager::GetSoundBuffer(namefilebuf[i]));
		// звуковой объект с нулевым индексом воспроизводится циклично
		GSound[0].setLoop(true);
	};
	// метод включения звукового эффекта согласно установленного в параметрах индекса
	void play(int index);
	// метод выключения звукового эффекта согласно установленного в параметрах индекса
	void stop(int index);
	// метод выключения всех звуковых эффектов
	void AllStop();
};

