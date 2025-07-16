#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <random>
#include "Tilemap.hpp"
Tilemap::Tilemap(const std::string& _directory) : tilemap_directory(_directory){
    if(!TILE_SET.loadFromFile(tilemap_directory)){
        std::cerr << "Error while trying to load tilemap!" << std::endl;
    }
}
void Tilemap::draw(int TILE_SIZE, const std::vector<std::vector<int>>& TILE_MAP, sf::RenderWindow& window, const sf::Vector2f& start_pos, int scale, bool draw_outline){
    if(scale == 0){scale = 1;}
    sf::Sprite sprite;
    sprite.setTexture(TILE_SET);
    int ColsPerRow = TILE_SET.getSize().x / TILE_SIZE;
    for(int y = 0; y < TILE_MAP.size(); ++y){
        for(int x = 0; x < TILE_MAP[y].size(); ++x){
            int CurID = TILE_MAP[y][x];
            if(CurID != -1){
                int tu = CurID % ColsPerRow;
                int ty = CurID / ColsPerRow;
                sprite.setTextureRect(sf::IntRect{{tu * TILE_SIZE, ty * TILE_SIZE}, {TILE_SIZE,TILE_SIZE}});
                sprite.setPosition(x * TILE_SIZE * scale + start_pos.x, y * TILE_SIZE * scale + start_pos.y);
                sprite.setScale(scale,scale);
                window.draw(sprite);
            }
            
        }
    }
    //optional: draw an outline for the tilemap
    if(draw_outline){
        sf::RectangleShape outline;
        outline.setFillColor(sf::Color(0,0,0,0));
        outline.setSize(sf::Vector2f{static_cast<float>(TILE_MAP[0].size() * TILE_SIZE * scale), static_cast<float>(TILE_MAP.size() * TILE_SIZE * scale)});
        outline.setPosition(start_pos);
        outline.setOutlineThickness(5.f);
        outline.setOutlineColor(sf::Color{172, 117, 52});
        window.draw(outline);
    }

}
void Tilemap::draw(int TILE_SIZE, int TILE_MAP_ID, sf::RenderWindow& window, const sf::Vector2f& pos, int scale){
    if(scale == 0){scale = 1;}
    sf::Sprite sprite;
    sprite.setTexture(this->TILE_SET);
    int ColsPerRow = TILE_SET.getSize().x / TILE_SIZE;
    int tu = TILE_MAP_ID % ColsPerRow;
    int ty = TILE_MAP_ID / ColsPerRow;
    sprite.setTextureRect(sf::IntRect{{tu * TILE_SIZE, ty * TILE_SIZE}, {TILE_SIZE,TILE_SIZE}});
    sprite.setPosition(pos);
    sprite.setScale(scale, scale);
    window.draw(sprite);
}
void Tilemap::draw_outline(sf::RenderWindow& window, const sf::Vector2f& start_pos, int scale){
    sf::RectangleShape outline;
    outline.setFillColor(sf::Color(0,0,0,0));
    outline.setSize(sf::Vector2f{static_cast<float>(this->TILE_SET.getSize().x * scale), static_cast<float>(this->TILE_SET.getSize().y * scale)});
    outline.setPosition(start_pos);
    outline.setOutlineThickness(5.f);
    outline.setOutlineColor(sf::Color{172, 117, 52});
    window.draw(outline);
}
std::vector<std::vector<int>> Tilemap::create_default(int TILE_SIZE, bool shouldBeEmpty){
    std::vector<std::vector<int>> default_vector;
    int cur_id = 0;
    int x_size = this->TILE_SET.getSize().x / TILE_SIZE;
    int y_size = this->TILE_SET.getSize().y / TILE_SIZE;
    for(int y = 0; y < y_size; ++y){
        std::vector<int> cur_vec;
        for(int x = 0; x < x_size; ++x){
            cur_vec.push_back(shouldBeEmpty ? -1 : cur_id++);
        }
        default_vector.push_back(cur_vec);

    }
    return default_vector;
}
sf::Vector2f Tilemap::get_tileset_size(){
    return sf::Vector2f{static_cast<float>(this->TILE_SET.getSize().x), static_cast<float>(this->TILE_SET.getSize().y)};
};
int Tilemap::get_cols(int TILE_SIZE){
    return this->TILE_SET.getSize().x / TILE_SIZE;
}
void Tilemap::save_to_a_file(const std::string& folder_path, const std::vector<std::vector<int>>& TILE_MAP, int& id){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100000);
    id = dist(gen);
    std::string file_name = "/tilemap" + std::to_string(id) + ".csv";
    std::ofstream file_save(folder_path+file_name);
    for(int i = 0; i < TILE_MAP.size(); ++i){
        for(int y = 0; y < TILE_MAP[i].size(); ++y){
            file_save << TILE_MAP[i][y] << ",";
        }
        file_save << "\n";
    }
    file_save.close();
}