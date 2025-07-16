#pragma once
#include <SFML/Graphics.hpp>
#include "Tilemap.hpp"
class TMBuilder{
private:
    //rect to higlight current selected tile
    int TILE_SIZE;
    sf::RectangleShape highlight;
public:
    TMBuilder(int _tile_size);
    void get_tile(sf::RenderWindow& window, const sf::Vector2f& start_tm_pos, const sf::Vector2f& end_tm_pos, const sf::Vector2i& mouse_pos, int cols, int& add_id, bool& adding);
    void place_tile(sf::RenderWindow& window, const sf::Vector2f& start_btm_pos, const sf::Vector2f& end_btm_pos, const sf::Vector2i& mouse_pos, int cols, int add_id, std::vector<std::vector<int>>& B_TMAP, bool& placed);
    void display_outline(sf::RenderWindow& window, const sf::Vector2i& mouse_pos, const sf::Vector2f& start_tm_pos); //helper function
    void delete_tile(sf::RenderWindow& window, const sf::Vector2f& start_btm_pos, const sf::Vector2f& end_btm_pos, const sf::Vector2i& mouse_pos, int cols, std::vector<std::vector<int>>& B_TMAP);
};