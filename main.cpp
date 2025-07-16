#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/Tilemap.hpp"
#include "src/Builder.hpp"
#include "src/TextManager.hpp"
#include "add/tinyfiledialogs.h"
#include "add/clip/clip.h"
#include "gui/Button.hpp"
#include "gui/Menu.hpp"
#include "loader/Settings.hpp"
constexpr int scale = 3;
//DEBUG FUCNTION - DO NOT TOUCH!
std::vector<std::vector<int>> default_vector(int TILE_SIZE, int _y, int _x){
    std::vector<std::vector<int>> default_vector;
    for(int y = 0; y < _y; ++y){
        std::vector<int> cur_vec;
        for(int x = 0; x < _x; ++x){
            cur_vec.push_back(-1);
        }
        default_vector.push_back(cur_vec);

    }
    return default_vector;
}
//END OF DEBUG FUNCTION DECLARATION
int main(){
    //first run
    int build_tile_set_size_X;
    int build_tile_set_size_Y;

    int tile_size;
    sf::RenderWindow build_window(sf::VideoMode(1200,700), "Tilemap Manager", sf::Style::Default);
    std::string main_tilemap_path;
    setup::set_settings(build_window, main_tilemap_path, build_tile_set_size_X, build_tile_set_size_Y, tile_size);
    ///////////// base variables, after completing our setup
    int to_add_id = -1;
    bool is_adding = false;
    bool placed = false;
    bool placed_once = false;
    //////////// ^ used to manage tile adding event

    //set up example tile map
    Tilemap map(main_tilemap_path); //USE THE CUSTOM TILEMAP PATH
    std::vector<std::vector<int>> tilemap = map.create_default(tile_size);
    //set up starting & ending positions for our tilemap
    sf::Vector2f start_pos_TM;
    sf::Vector2f end_pos_TM;
    //initialize our custom tilemap
    Tilemap build_map(main_tilemap_path);
    //std::vector<std::vector<int>> tilemap_build = map.create_default(tile_size, true);
    std::vector<std::vector<int>> tilemap_build = default_vector(tile_size, build_tile_set_size_Y, build_tile_set_size_X);
    sf::Vector2f start_pos_BTM; //BTM not to be confused with TM (btm - BUILD tile map, tm - tile map)
    sf::Vector2f end_pos_BTM; //same as higher
    //set up window
    int tileset_pixel_width  = map.get_tileset_size().x * scale; 
    int tileset_pixel_height = map.get_tileset_size().y * scale;

    int tilemap_pixel_width  = tilemap_build[0].size() * tile_size * scale;
    int tilemap_pixel_height = tilemap_build.size() * tile_size * scale;

    int side_margin = 40;  
    int outer_margin = 60;  

    int window_width  = tileset_pixel_width + tilemap_pixel_width + side_margin + outer_margin * 2;
    int window_height = (std::max(tileset_pixel_height, tilemap_pixel_height) + outer_margin * 2) + 100.f;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Tilemap manager 0.1", sf::Style::Default);
    window.setSize(sf::Vector2u(window_width, window_height));
    //window.setSize(sf::Vector2u(3000.f, 3000.f));
    //sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Tilemap Manager", sf::Style::Default);
    //set up custom distance variable
    float side_gap = (window_width - ((tilemap_build[0].size() * tile_size * scale) + (map.get_tileset_size().x * scale) + 20.f)) / 2.f;
    //set up start pos and use the custom distance (side gap) variable
    start_pos_TM = {side_gap, 150.f};
    end_pos_TM = {map.get_tileset_size().x * scale + start_pos_TM.x,map.get_tileset_size().y * scale + start_pos_TM.y};

    start_pos_BTM = {end_pos_TM.x+20.f, 150.f};
    end_pos_BTM = {tilemap_build[0].size() * tile_size * scale + start_pos_BTM.x,tilemap_build.size() * tile_size * scale + start_pos_BTM.y};

    //set up builder class
    TMBuilder build(tile_size*scale);

    //set up header position varaibles
    int header_x = (window_width/2) - 325;
    //set up header text
    TextManager header("assets/font.ttf",{static_cast<float>(header_x), 35.f}, sf::Color::White, 60);

    ///DEBUG TO MANAGE LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    sf::Texture texture;
        texture.loadFromFile("../assets/main_icon.png");
        sf::Sprite icon;
        icon.setTexture(texture);
        icon.setPosition((1200/2 - 450), 0.f);
        icon.setScale(4.f,4.f);
    icon.setPosition((window_width/2 - 450), 20.f);
    //END OF DEBUG MANAGEINGG!!!!!!!!!!!!!!!!!!!!!

    //export button
    //check which is higher: tilemap or BUILDtilemap, to calculate the button position
    std::cout << build_map.get_tileset_size().y << "," << tile_size << "," << build_tile_set_size_Y << std::endl;
    Button export_btn({0.f,0.f}, "Export");
    Button help_btn({0.f,0.f}, "Help");
    if(map.get_tileset_size().y*scale < (tile_size*scale) * build_tile_set_size_Y){
        export_btn.set_position({(side_gap + map.get_tileset_size().x*scale)-220.f, 170.f + map.get_tileset_size().y*scale});
        help_btn.set_position({(side_gap + map.get_tileset_size().x*scale)-450.f, 170.f + map.get_tileset_size().y*scale});
    }
    else{
        export_btn.set_position({side_gap + map.get_tileset_size().x*scale + 20.f, 170.f +tilemap_build.size()*tile_size*scale});
        help_btn.set_position({220.f + side_gap + map.get_tileset_size().x*scale + 20.f, 170.f + tilemap_build.size()*tile_size*scale});
    }
    //set up the export info text
    TextManager export_info("assets/font.ttf", {(window_width/2) - 325, 5.f}, sf::Color::White, 30);
    std::string communicate;
    bool should_display_communicate = false;
    //main loop
    while(window.isOpen()){
        //event handling START
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }//event handling END
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){ //debug mode to display btm vector do NOT delete
            std::cout << "----------------------------------------------" << std::endl;
            for(int i = 0; i < tilemap_build.size(); ++i){
                for(int y = 0; y < tilemap_build[i].size(); ++y){
                    std::cout << tilemap_build[i][y] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "----------------------------------------------" << std::endl;
        } //end of debug mode

        //detect mouse position
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        window.clear(sf::Color::Black);
        /*std::cout << "------------------------------" << std::endl; 
        std::cout << "is adding = " << (is_adding ? "true"  :"false") << std::endl;
        std::cout << "placed = " << (is_adding ? "true"  :"false") << std::endl;
        std::cout << "placed once = " << (is_adding ? "true"  :"false") << std::endl;
        std::cout << "------------------------------" << std::endl; */


        //check if the main "EXPORT" button is pressed
        if(export_btn.clicked(window, mouse_pos)){
            const char *folderPath = tinyfd_selectFolderDialog( //make the user choose where the tilemap is saved
                "Choose the folder",         
                nullptr                   
            );
            int id;
            build_map.save_to_a_file(folderPath, tilemap_build,id);
            should_display_communicate = true;
            communicate = "Succesfully saved tilemap" + std::to_string(id) + ".csv!";
            
        }
        else if(help_btn.clicked(window,mouse_pos)){
            should_display_communicate = true;
            clip::set_text("https://github.com/bartekldw/tilemap_manager");
            communicate = "Succesfully copied github repo link to clipboard!";
        }
        //perform main actions
        map.draw(tile_size, tilemap, window, start_pos_TM, scale); //draw main tilemap
        map.draw(tile_size, tilemap_build, window, start_pos_BTM, scale); //draw our build space
        if(is_adding){ //when we are adding a tile, let's:
            placed = false; 
            map.draw(tile_size, to_add_id, window, {static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y)}, scale); //draw the tile we are moving right now (second function name overflow - in src/Tilemap)
            //build.display_outline(window, mouse_pos, {600.f, 100.f}); //<- debug mode, do not delete
            build.place_tile(window, start_pos_BTM, end_pos_BTM, mouse_pos, map.get_cols(tile_size), to_add_id, tilemap_build, placed); //try to place a tile (see src/Builder.cpp for more info)
            if(placed){placed_once = true;}
            if(placed_once && !placed){
                is_adding = false;
                placed_once = false;
            }
        }
        else{ //when we are wanting to add a tile, or delete a tile, enduce needed functions
            build.get_tile(window, start_pos_TM, end_pos_TM, mouse_pos, map.get_cols(tile_size), to_add_id, is_adding);
            build.delete_tile(window, start_pos_BTM, end_pos_BTM, mouse_pos, map.get_cols(tile_size), tilemap_build);
        }
        //end of main actions
        header.draw(window, "Tilemap Manager 0.1");
        window.draw(icon);
        export_btn.draw(window);
        help_btn.draw(window);
        if(should_display_communicate){
            export_info.draw(window, communicate);
        }
        window.display();
    }
    //end of main loop
    return 0;
}