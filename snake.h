#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <bits/stdc++.h>


struct pair{
    float x,y;
};

struct Snake
{
    int length;
    pair snake[100];
    int direction;
    int prevdirection;
    float block;
};

struct Oblik{
	int duzina;
	pair shape[100];
};

class Game {
	private:
		sf::RenderWindow* window;
		sf::Event event;
		
		Snake zmica;
		Oblik oblik;
		
		sf::RectangleShape blockSnake;
		sf::RectangleShape blockShape1;
		sf::RectangleShape blockShape2;
		
		sf::Vector2i MousePosWin;
		sf::Vector2f MousePosView;
		
		sf::Texture grass;
		sf::Texture zmijica;
		sf::Texture oci;
		sf::Texture hrana;
		sf::Texture ples;
		
		sf::Font font;
		
		sf::Text score;
		sf::Text nivo;
		
		sf::Sprite zmija;
		sf::Sprite food;
		
		sf::RectangleShape dugme;
		
		sf::Music pesma;
		
		bool inGame;
		bool pojedena;
		
		int rast;
		int level;
	public:
		
		Game();
		~Game();
		
		void InitVariables();
		void InitWindow();
		
		const bool running() const;
		const bool gameStart() const;
		const bool Ziv() const;
		const bool LevelUp() const;
		
		sf::Sprite grassBackground();
		
		void Movement();
		void SpawnFood();
		void SpawnShape();
		void PauseGame();
		void EndGame();
		
		void Intro();
		void EventPolling();
		void updateMousePos();
		void update();
		void render();
};
