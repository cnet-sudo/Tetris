#pragma once
#include<iostream>
#include"AssetManager.h"
#include"Button.h";
#include"string";
#include"Tetramino.h";

class GameEngine
{
public:
	// �����������
	GameEngine();
	// ����� ������� �������� �����
	void run();
private:
	AssetManager manager; // �������� ��������
	// ����� ��������� �� ����������� ���� 
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>
	(sf::VideoMode(640, 640),L"������", sf::Style::Close);
	// ������� ��� � ���� ��������������
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(640, 640));
	sf::Image icon;
	Button play = Button(sf::Vector2f(13, 140), AssetManager::GetTexture("image/play1.png"), AssetManager::GetTexture("image/play2.png"));
	Button pause = Button(sf::Vector2f(13,220),AssetManager::GetTexture("image/pause1.png"), AssetManager::GetTexture("image/pause2.png"));
	Button restart = Button(sf::Vector2f(13, 300), AssetManager::GetTexture("image/restart1.png"), AssetManager::GetTexture("image/restart2.png"));
	Button sound = Button(sf::Vector2f(13, 380), AssetManager::GetTexture("image/nosound.png"), AssetManager::GetTexture("image/sound.png"));
	sf::Text text;
	Tetramino tetramino = Tetramino(*window,sf::Vector2f(390,-30),Tetramino::Borders(198,609,585));
	int score = 0;
	// ����� ��������� ������� 
	void input();
	// ����� ���������� ����������, ������� � ������� 
	void update(sf::Time const& deltaTime);
	// ����� ��������� �������� � ����������� ����
	void draw();
};

