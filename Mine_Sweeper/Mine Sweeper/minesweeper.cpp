


// This file contains the implementations of the MineSweeper class

#include "minesweeper.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// Constructor
// Default Constructor
MineSweeper::MineSweeper()
{
	cout << "MineSweeper() called" << endl;
}

// Member Functions

// load from config file
void MineSweeper::load_from_config_file(const string filename)
{
	// Loads the width, height and mine count from the given file.
	ifstream fin(filename);
	// checking if the file is not opened
	if (!fin.is_open())
		throw std::ios_base::failure("Failed to open file.");

	// if file opens SUCCESSFULLY
	string buffer;

	// reading width
	getline(fin, buffer, '\n');
	// writing width
	this->width = atoi(buffer.c_str()) * 32;

	// writing tile count partially
	this->tile_count = atoi(buffer.c_str());

	// reading height
	getline(fin, buffer, '\n');
	// writing height
	this->height = (atoi(buffer.c_str()) * 32) + 100;

	// writing tile count completely
	this->tile_count = this->tile_count * atoi(buffer.c_str());

	// reading mine count
	getline(fin, buffer, '\n');
	// writing mine count
	this->mine_count = atoi(buffer.c_str());

}

// initialize window
sf::RenderWindow* MineSweeper::initialize_window(const string window_title)
{
	this->window_title = window_title;
	this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), this->window_title);

	return window;
}

// print
void MineSweeper::print() const
{
	// prints the information in a nice format.
	cout << "Width: --> " << this->width;
	cout << ", Height: --> " << this->height;
	cout << ", Mine Count: --> " << this->mine_count;
	cout << ", Tile Count: --> " << this->tile_count;
	cout << endl;
}

// Getters

// get width
int MineSweeper::get_width() const
{
	// returns the width.
	return this->width;
}

// get height
int MineSweeper::get_height() const
{
	// returns the height.
	return this->height;
}

// get mine_count
int MineSweeper::get_mine_count() const
{
	// returns the mine_count.
	return this->mine_count;
}

MineSweeper::~MineSweeper()
{
	// deleting heap initialized window
	delete this->window;
}