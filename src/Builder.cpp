#include <SFML/Graphics.hpp>
#include "Builder.hpp"
#include "Tilemap.hpp"
#include <iostream>
TMBuilder::TMBuilder(int _tile_size) : TILE_SIZE(_tile_size){
    highlight.setFillColor(sf::Color(0,255,0,50));
    highlight.setOutlineColor(sf::Color::Red);
    highlight.setOutlineThickness(5.f);
    highlight.setSize(sf::Vector2f{static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE)});
}
void TMBuilder::display_outline(sf::RenderWindow& window, const sf::Vector2i& mouse_pos, const sf::Vector2f& start_tm_pos){
    int tileX = (mouse_pos.x - start_tm_pos.x)/ TILE_SIZE;
    int tileY = (mouse_pos.y - start_tm_pos.y)/ TILE_SIZE;
    highlight.setOutlineThickness(5.f);
    highlight.setPosition(start_tm_pos.x + TILE_SIZE * tileX, start_tm_pos.y + TILE_SIZE * tileY);
    window.draw(highlight);
}
void TMBuilder::get_tile(sf::RenderWindow& window, const sf::Vector2f& start_tm_pos, const sf::Vector2f& end_tm_pos, const sf::Vector2i& mouse_pos, int cols, int& add_id, bool& adding){
    if(mouse_pos.x >= start_tm_pos.x && mouse_pos.x < end_tm_pos.x && mouse_pos.y >= start_tm_pos.y && mouse_pos.y < end_tm_pos.y){
        this->display_outline(window, mouse_pos, start_tm_pos);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            int tileX = (mouse_pos.x - start_tm_pos.x)/ TILE_SIZE;
            int tileY = (mouse_pos.y - start_tm_pos.y)/ TILE_SIZE;
            add_id = tileY * cols + tileX;
            adding = true;
        }
        else{
            add_id = -1;
        }
    }
    else{
            add_id = -1;
    }
    
}
void TMBuilder::place_tile(sf::RenderWindow& window, const sf::Vector2f& start_btm_pos, const sf::Vector2f& end_btm_pos, const sf::Vector2i& mouse_pos, int cols, int add_id, std::vector<std::vector<int>>& B_TMAP, bool& placed){
    if(mouse_pos.x >= start_btm_pos.x && mouse_pos.x < end_btm_pos.x && mouse_pos.y >= start_btm_pos.y && mouse_pos.y < end_btm_pos.y){
        this->display_outline(window, mouse_pos, start_btm_pos);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            int tileX = (mouse_pos.x - start_btm_pos.x)/ TILE_SIZE;
            int tileY = (mouse_pos.y - start_btm_pos.y)/ TILE_SIZE;
            if(B_TMAP[tileY][tileX] != add_id){
                B_TMAP[tileY][tileX] = add_id;
            }
            placed = true;
           
        }
        else{placed = false;}
    }
}
void TMBuilder::delete_tile(sf::RenderWindow& window, const sf::Vector2f& start_btm_pos, const sf::Vector2f& end_btm_pos, const sf::Vector2i& mouse_pos, int cols, std::vector<std::vector<int>>& B_TMAP){
    if(mouse_pos.x >= start_btm_pos.x && mouse_pos.x < end_btm_pos.x && mouse_pos.y >= start_btm_pos.y && mouse_pos.y < end_btm_pos.y){
        this->display_outline(window, mouse_pos, start_btm_pos);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            
            int tileX = (mouse_pos.x - start_btm_pos.x)/ TILE_SIZE;
            int tileY = (mouse_pos.y - start_btm_pos.y)/ TILE_SIZE;
            B_TMAP[tileY][tileX] = -1;
        }
    }   
}