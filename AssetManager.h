#pragma once
#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <assert.h>
#include<map>
#include<memory>

class AssetManager
{

public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& filename);
	static sf::SoundBuffer& GetSoundBuffer(std::string const& filename);
	static sf::Font& GetFont(std::string const& filename);
	static sf::Shader* GetShader(std::string const& vsFile,std::string const& fsFile);
private:

	std::map<std::string, sf::Texture> m_Textures;
	std::map<std::string, sf::SoundBuffer> m_SoundBuffer;
	std::map<std::string, sf::Font> m_Fonts;
	std::map < std::string, std::unique_ptr < sf::Shader >> m_Shaders;

	static AssetManager* sInstance;

};

