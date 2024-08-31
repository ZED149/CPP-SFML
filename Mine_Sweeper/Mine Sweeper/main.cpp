//
//
//#include <SFML/Window.hpp>
//#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics.hpp>
//using namespace sf;
//#include <iostream>
//using namespace std;
//#include "minesweeper.h"
//
//
//int main()
//{
//	// game object
//	MineSweeper game;
//	// loading configuration file
//	game.load_from_config_file("boards/config.cfg");
//
//	// calculating width, height and mine_count
//	unsigned int width = game.get_width(), height = game.get_height(), mine_count = game.get_mine_count();
//	// printing game details.
//	game.print();
//
//	// initializing main window
//	//RenderWindow window(sf::VideoMode(width, height), "Mine Sweeper");
//	RenderWindow *window = game.initialize_window("ZED");
//
//	// texture for all hidden tiles
//	sf::Texture texture;
//	if (!texture.loadFromFile("images/tile_hidden.png"))
//		cout << "Texture not loaded" << endl;
//	texture.setRepeated(true);
//
//	sf::Sprite sprite;
//	sprite.setTexture(texture);
//	sprite.setTextureRect(sf::IntRect(0, 0, width, height - 100));
//
//	// texture for number of turns
//	sf::Texture t;
//	if (!t.loadFromFile("images/digits.png"))
//	{
//		cout << "Failed to load images.png" << endl;
//	}
//	sf::Sprite s;
//	s.setPosition(0, height - 100);
//	s.setTexture(t);
//	s.setTextureRect(sf::IntRect(0, 0, 21, 32));
//
//	// texture for Debug button
//	sf::Texture t1;
//	t1.loadFromFile("images/debug.png");
//	sf::Sprite s1;
//	s1.setPosition(544, height - 100);
//	s1.setTexture(t1);
//
//	// testure for test 1
//	sf::Texture t2;
//	t2.loadFromFile("images/test_1.png");
//	sf::Sprite s2;
//	s2.setPosition(608, height - 100);
//	s2.setTexture(t2);
//
//	// texture for test 2
//	sf::Texture t3;
//	t3.loadFromFile("images/test_2.png");
//	sf::Sprite s3;
//	s3.setPosition(672, height - 100);
//	s3.setTexture(t3);
//
//	// texture for test 3
//	sf::Texture t4;
//	t4.loadFromFile("images/test_3.png");
//	sf::Sprite s4;
//	s4.setPosition(736, height - 100);
//	s4.setTexture(t4);
//
//	Sprite temp_s;
//	// creating another texture
//	Texture temp;
//	if (!temp.loadFromFile("images/tile_revealed.png"))
//		cout << "Failed to load tile_revealed.png" << endl;
//
//	sf::Mouse mouse;
//
//	while ((*window).isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
//	{
//		Event _event;
//		while ((*window).pollEvent(_event))
//		{
//			// this is the case if we wanna close the window
//			if (_event.type == Event::Closed)
//				(*window).close();
//
//			// checking something else
//			if (_event.type == Event::KeyPressed)
//			{
//				std::cout << "Working key pressed" << std::endl;
//			}
//
//			if (_event.type == Event::MouseButtonPressed)
//			{
//				sf::Vector2i coord = mouse.getPosition((*window));
//				// printing coordinates to screen
//				cout << "COORDS: " << "(" << coord.x << ", " << coord.y << ")" << endl;
//				
//				temp_s.setPosition(Vector2f(coord.x - 16, coord.y - 16));
//				temp_s.setTextureRect(sf::IntRect(0, 0, 32, 32));
//				temp_s.setTexture(temp);
//			}
//		}
//
//
//		// clearing the window
//		(*window).clear();
//		// putting it on the window
//		(*window).draw(sprite);
//		(*window).draw(s);
//		(*window).draw(s1);
//		(*window).draw(s2);
//		(*window).draw(s3);
//		(*window).draw(s4);
//		(*window).draw(temp_s);
//		// displaying the window on screen
//		(*window).display();
//		
//
//
//	}
//
//}
//
