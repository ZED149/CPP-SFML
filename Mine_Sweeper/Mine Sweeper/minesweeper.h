

#pragma once

#include <iostream>
#include <string>
using namespace std;
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>

// This class contains the Mine Sweeper class

class MineSweeper
{
	// Private data members
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int mine_count = 0;
	unsigned int tile_count = 0;
	string window_title = "";
	sf::RenderWindow* window = nullptr;

public:
	// Constructor
	// Default Constructor
	MineSweeper();

	// Member Functions

	// load from config file
	void load_from_config_file(const string filename);

	// initialize window
	sf::RenderWindow* initialize_window(const string window_title);

	// print
	void print() const;

	// Getters
	
	// get width
	int get_width() const;

	// get height
	int get_height() const;

	// get mine_count
	int get_mine_count() const;

	// Destructor
	~MineSweeper();


};