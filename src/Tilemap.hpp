#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Tilemap{
private:
    std::string tilemap_directory;
    sf::Texture TILE_SET;
public:
    Tilemap(const std::string& _directory);
    void draw(int TILE_SIZE, const std::vector<std::vector<int>>& TILE_MAP, sf::RenderWindow& window, const sf::Vector2f& start_pos = {0.f, 0.f}, int scale = 1, bool draw_outline = true);
    void draw(int TILE_SIZE, int TILE_MAP_ID, sf::RenderWindow& window, const sf::Vector2f& pos, int scale = 1);
    void draw_outline(sf::RenderWindow& window, const sf::Vector2f& start_pos, int scale);
    std::vector<std::vector<int>> create_default(int TILE_SIZE, bool shouldBeEmpty = false); //<- function to fill 2D vector with whole tilemap (or, empty variables) 
    sf::Vector2f get_tileset_size();
    int get_cols(int TILE_SIZE);
    void save_to_a_file(const std::string& folder_path, const std::vector<std::vector<int>>& TILE_MAP, int& id);
};