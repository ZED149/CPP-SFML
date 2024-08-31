#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

enum class TileState
{
    Hidden,
    Revealed,
    Flagged
};

struct Tile
{
    bool isMine;
    int adjacentMines;
    TileState state;
};

struct GameConfig
{
    int columns;
    int rows;
    int mineCount;
};

GameConfig parseConfigFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open config file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    GameConfig config;
    file >> config.columns >> config.rows >> config.mineCount;
    file.close();
    return config;
}

map<string, Texture> loadTextures()
{
    map<string, Texture> textures;
    Texture texture;

    if (!texture.loadFromFile("images/tile_hidden.png"))
    {
        cerr << "Error: Failed to load texture: tile_hidden.png" << endl;
        exit(EXIT_FAILURE);
    }
    textures["tile_hidden"] = texture;

    if (!texture.loadFromFile("images/flag.png"))
    {
        cerr << "Error: Failed to load texture: tile_flagged.png" << endl;
        exit(EXIT_FAILURE);
    }
    textures["tile_flagged"] = texture;

    if (!texture.loadFromFile("images/mine.png"))
    {
        cerr << "Error: Failed to load texture: mine.png" << endl;
        exit(EXIT_FAILURE);
    }
    textures["mine"] = texture;

    if (!texture.loadFromFile("images/tile_revealed.png"))
    {
        cerr << "Error: Failed to load texture: tile_revealed.png" << endl;
        exit(EXIT_FAILURE);
    }
    textures["tile_revealed"] = texture;

    for (int i = 1; i <= 8; ++i)
    {
        string filename = "images/number_" + to_string(i) + ".png";
        if (!texture.loadFromFile(filename))
        {
            cerr << "Error: Failed to load texture: " << filename << endl;
            exit(EXIT_FAILURE);
        }
        textures["number_" + to_string(i)] = texture;
    }

    if (!texture.loadFromFile("images/test_1.png"))
    {
    	cerr << "Error: Failed to load texture: test_1.png" << endl;
    	exit(EXIT_FAILURE);
    }
    textures["test_1"] = texture;
    	
    if (!texture.loadFromFile("images/test_2.png"))
    {
    	cerr << "Error: Failed to load texture: test_2.png" << endl;
    	exit(EXIT_FAILURE);
    }
    textures["test_2"] = texture;
    	
    if (!texture.loadFromFile("images/test_3.png"))
    {
    	cerr << "Error: Failed to load texture: test_3.png" << endl;
    	exit(EXIT_FAILURE);
    }
    textures["test_3"] = texture;
    	
    if (!texture.loadFromFile("images/debug.png"))
    {
    	cerr << "Error: Failed to load texture: debug.png" << endl;
    	exit(EXIT_FAILURE);
    }
    textures["debug"] = texture;
    	
    if (!texture.loadFromFile("images/digits.png"))
    {
    	cerr << "Error: Failed to load texture: digits.png" << endl;
    	exit(EXIT_FAILURE);
    }
    textures["digits"] = texture;
    	
    if (!texture.loadFromFile("images/face_lose.png"))
    {
    	cerr << "Error: Failed to load texture: face_lose.png" << endl;
    	exit(EXIT_FAILURE);
    }
    textures["face_lose"] = texture;

    return textures;
}

class Board
{
private:
    vector<vector<Tile>> grid;
    int cols;
    int rows;

public:
    Board(int columns, int rows, int mineCount)
    {
        grid.resize(columns, vector<Tile>(rows));
        initializeMines(mineCount);
        calculateAdjacentMines();

        this->cols = columns;
        this->rows = rows;
    }

    void initializeMines(int mineCount)
    {
        srand(time(NULL));
        int totalMines = 0;
        while (totalMines < mineCount)
        {
            int x = rand() % grid.size();
            int y = rand() % grid[0].size();
            if (!grid[x][y].isMine)
            {
                grid[x][y].isMine = true;
                totalMines++;
            }
        }
    }

    void calculateAdjacentMines()
    {
        for (int x = 0; x < grid.size(); ++x)
        {
            for (int y = 0; y < grid[0].size(); ++y)
            {
                if (!grid[x][y].isMine)
                {
                    int count = 0;
                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        for (int dy = -1; dy <= 1; ++dy)
                        {
                            int nx = x + dx;
                            int ny = y + dy;
                            if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny].isMine)
                            {
                                count++;
                            }
                        }
                    }
                    grid[x][y].adjacentMines = count;
                }
            }
        }
    }

    Tile& getTile(int x, int y)
    {
        return grid[x][y];
    }

    void revealAllMines()
    {
        for (int x = 0; x < grid.size(); ++x)
        {
            for (int y = 0; y < grid[0].size(); ++y)
            {
                if (grid[x][y].isMine)
                {
                    grid[x][y].state = TileState::Revealed;
                }
            }
        }
    }

    bool allNonMineTilesRevealed() const
    {
        for (int x = 0; x < grid.size(); ++x)
        {
            for (int y = 0; y < grid[0].size(); ++y)
            {
                if (!grid[x][y].isMine && grid[x][y].state != TileState::Revealed)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool anyMineTileRevealed() const
    {
        for (int x = 0; x < grid.size(); ++x)
        {
            for (int y = 0; y < grid[0].size(); ++y)
            {
                if (grid[x][y].isMine && grid[x][y].state == TileState::Revealed)
                {
                    return true;
                }
            }
        }
        return false;
    }

    int getColumns()
    {
        return this->cols;
    }

    int getRows()
    {
        return this->rows;
    }
};

void revealTiles(Board& board, int x, int y)
{
    if (x < 0 || x >= board.getColumns() || y < 0 || y >= board.getRows())
        return;

    Tile& tile = board.getTile(x, y);
    if (tile.state == TileState::Hidden)
    {
        tile.state = TileState::Revealed;
        if (tile.adjacentMines == 0)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    revealTiles(board, x + dx, y + dy);
                }
            }
        }
    }
}

int main()
{
    GameConfig config = parseConfigFile("boards/config.cfg");
    map<string, Texture> textures = loadTextures();
    Board board(config.columns, config.rows, config.mineCount);
    int windowWidth = config.columns * 32;
    int windowHeight = (config.rows * 32) + 100;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Mine Sweeper");

    while (window.isOpen())
    {
        Event event;
        Sprite tileSprite;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePosition = Mouse::getPosition(window);
                    int tileX = mousePosition.x / 32;
                    int tileY = mousePosition.y / 32;
                    if (tileX >= 0 && tileX < config.columns && tileY >= 0 && tileY < config.rows)
                    {
                        Tile& tile = board.getTile(tileX, tileY);
                        if (tile.state == TileState::Hidden)
                        {
                            if (tile.isMine)
                            {
                                cout << "Game Over! You hit a mine!" << endl;
                                board.revealAllMines();
                            }
                            else
                            {
                                revealTiles(board, tileX, tileY);
                                if (board.allNonMineTilesRevealed())
                                {
                                    cout << "Congratulations! You won the game!" << endl;
                                }
                            }
                        }
                    }
                }
                else if (event.mouseButton.button == Mouse::Right)
                {
                    Vector2i mousePosition = Mouse::getPosition(window);
                    int tileX = mousePosition.x / 32;
                    int tileY = mousePosition.y / 32;
                    if (tileX >= 0 && tileX < config.columns && tileY >= 0 && tileY < config.rows)
                    {
                        Tile& tile = board.getTile(tileX, tileY);
                        if (tile.state == TileState::Hidden)
                        {
                            tile.state = TileState::Flagged;
                        }
                        else if (tile.state == TileState::Flagged)
                        {
                            tile.state = TileState::Hidden;
                        }
                    }
                }
            }
        }

        window.clear(Color::White);

        for (int x = 0; x < config.columns; ++x)
        {
            for (int y = 0; y < config.rows; ++y)
            {
                Tile& tile = board.getTile(x, y);
                
                switch (tile.state)
                {
                case TileState::Hidden:
                    tileSprite.setTexture(textures["tile_hidden"]);
                    break;
                case TileState::Revealed:
                    if (tile.isMine)
                    {
                        tileSprite.setTexture(textures["mine"]);
                    }
                    else if (tile.adjacentMines > 0)
                    {
                        string textureName = "number_" + to_string(tile.adjacentMines);
                        tileSprite.setTexture(textures[textureName]);
                    }
                    else
                    {
                        tileSprite.setTexture(textures["tile_revealed"]);
                    }
                    break;
                case TileState::Flagged:
                    tileSprite.setTexture(textures["tile_flagged"]);
                    break;
                }

                tileSprite.setPosition(x * 32, y * 32);
                window.draw(tileSprite);
            }
        }

        tileSprite.setTexture(textures["test_1"]);
        tileSprite.setPosition((config.columns * 32) - (32 * 6), config.rows * 32);
        tileSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        window.draw(tileSprite);
        		        
        tileSprite.setTexture(textures["test_2"]);
        tileSprite.setPosition((config.columns * 32) - (32 * 4), config.rows * 32);
        tileSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        window.draw(tileSprite);
        		
        tileSprite.setTexture(textures["test_3"]);
        tileSprite.setPosition((config.columns * 32) - (32 * 2), config.rows * 32);
        tileSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        window.draw(tileSprite);
        		
        tileSprite.setTexture(textures["debug"]);
        tileSprite.setPosition((config.columns * 32) - (32 * 8), config.rows * 32);
        tileSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        window.draw(tileSprite);
        		
        tileSprite.setTexture(textures["digits"]);
        tileSprite.setPosition(0, config.rows * 32);
        tileSprite.setTextureRect(sf::IntRect(0, 0, 42, 32));
        window.draw(tileSprite);

        window.display();

        if (board.anyMineTileRevealed())
        {
            cout << "Game Over! You hit a mine!" << endl;
            board.revealAllMines();
        }

        if (board.allNonMineTilesRevealed())
        {
            cout << "Congratulations! You won the game!" << endl;
        }
    }

}