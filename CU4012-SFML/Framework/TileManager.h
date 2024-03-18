#pragma once
#include "GameObject.h"
#include "World.h"
#include "Tiles.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream> // This is required for std::stringstream


class TileManager :
    public GameObject
{

    std::string CustomTileTexturePath;
    int activeTileIndex = -1; // -1 indicates no tile is actively being edited
    bool tilesLoaded = false;
    //std::vector<Tiles> tiles;

    std::vector<std::unique_ptr<Tiles>> tiles;

    std::string filePath; // File to store tile data
    sf::Texture tileTexture;
    World* world;
public:
    TileManager();

    void update(float dt) override;
    void handleInput(float dt) override;
    void render();

    void saveTiles(const std::vector<std::unique_ptr<Tiles>>& tiles, const std::string& filePath);
    bool loadTiles();

    std::vector<std::unique_ptr<Tiles>>& getTiles();

    void setWorld(World* world) { this->world = world; }

    std::string getFilePath() { return filePath; }

    void setCustomTexture(std::string texturePath);
};

