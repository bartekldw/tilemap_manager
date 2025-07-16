#include <SFML/Graphics.hpp>
#include <iostream>
#include "../src/Tilemap.hpp"
#include "../src/Builder.hpp"
#include "../src/TextManager.hpp"
#include "../add/tinyfiledialogs.h"
#include "../gui/Button.hpp"
#include "../gui/Menu.hpp"
#include "../gui/Textbox.hpp"
namespace setup{
    void set_settings(sf::RenderWindow& window, std::string& file_path, int& btm_x, int& btm_y, int& tile_size){
        const char *filePath;
        //at first, enter the preview mode to load the tilemap
        //in this preview mode, we operate on dry variables (const numbers, not calculated) as the window size is const
        TextManager prev_header("assets/font.ttf",{280.f, 25.f}, sf::Color::White, 60);
        window.setFramerateLimit(15);
        bool completed = false; //variable to check if the setup of tilemap is completed
        //outline for tilemaps
        sf::RectangleShape outline, outline_btm;
        outline.setFillColor(sf::Color(0,0,0,0)); outline_btm.setFillColor(sf::Color(0,0,0,0));
        outline.setSize(sf::Vector2f{480.f, 480.f}); outline_btm.setSize(sf::Vector2f{480.f, 480.f});
        outline.setPosition({110.f, 120.f}); outline_btm.setPosition({610.f, 120.f});
        outline.setOutlineThickness(5.f); outline_btm.setOutlineThickness(5.f);
        outline.setOutlineColor(sf::Color{172, 117, 52}); outline_btm.setOutlineColor(sf::Color{172, 117, 52});
        //main icon sprite
        sf::Texture texture;
        texture.loadFromFile("../assets/main_icon.png");
        sf::Sprite icon;
        icon.setTexture(texture);
        icon.setPosition((1200/2 - 450), 0.f);
        icon.setScale(4.f,4.f);
        //folder icon sprite
        sf::Texture texture_folder;
        texture_folder.loadFromFile("../assets/folder_icon.png");
        sf::Sprite folder_icon;
        folder_icon.setTexture(texture_folder);
        folder_icon.setPosition(38.f, 80.f);
        folder_icon.setScale(8.f, 8.f);

        //settings icon sprite
        sf::Texture texture_setting;
        texture_setting.loadFromFile("../assets/settings.png");
        sf::Sprite settings_icon;
        settings_icon.setTexture(texture_setting);
        settings_icon.setPosition(640.f, 140.f);
        settings_icon.setScale(8.f, 8.f);

        //folder icon text
        TextManager first_load_text("assets/font.ttf", {210.f, 380.f}, sf::Color::White, "Click", sf::Color::Blue, "HERE", sf::Color::White, "to load tilemap", 32);
        TextManager first_load_btm_text("assets/font.ttf", {640.f, 380.f}, sf::Color::White, "Click", sf::Color::Blue, "HERE", sf::Color::White, "to configure build area", 32);
        //additional error text
        TextManager error("assets/font.ttf", {150.f, 450.f}, sf::Color::Red, 32);
        bool errorstate {false};

        //completed configure variables
        bool completed_tilemap {false};
        bool completed_buildtilemap {false};
        bool configuring_buildtm {false};
        //complete text and sprite
        TextManager complete_tm("assets/font.ttf", {260.f, 300.f}, sf::Color::Green, 32);
        sf::Texture mark_texture;
        mark_texture.loadFromFile("../assets/mark.png");
        sf::Sprite mark_tm;
        mark_tm.setTexture(mark_texture);
        mark_tm.setPosition(290.f, 330.f);
        mark_tm.setScale(0.2f, 0.2f);

        TextManager complete_btm("assets/font.ttf", {770.f, 300.f}, sf::Color::Green, 32);
        sf::Sprite mark_btm;
        mark_btm.setTexture(mark_texture);
        mark_btm.setPosition(800.f, 330.f);
        mark_btm.setScale(0.2f, 0.2f);

        //configuring build tilemap menu
        MenuDisplay grid_size_menu({655.f, 200.f}, "Set grid size", {"10x10","20x20","Custom"}, 200);
        MenuDisplay tile_size_menu({655.f, 350.f}, "Set tile size", {"16x16","32x32","Custom"}, 200);
        grid_size_menu.set_element_color(-1);
        tile_size_menu.set_element_color(-1);
        Button btm_complete({750.f, 500.f}, "Complete", sf::Color(50,50,50));

        //more "CUSTOM" options for menu manager
        bool create_custom_grid = false;
        bool create_custom_tile = false;
        Textbox tb1({760.f, 200.f}, "Custom grid size (x): ", 440);
        Textbox tb2({760.f, 300.f}, "Custom grid size (y): ", 440);
        Button btm_custom_grid_complete({500.f, 385.f}, "Complete");
        sf::RectangleShape shadow(sf::Vector2f{window.getSize().x, window.getSize().y});
        shadow.setFillColor(sf::Color(0,0,0,230));
        shadow.setPosition(0.f, 0.f);
        bool completed_btm_grid = false;
        bool completed_btm_tile = false;



        Textbox tb3({760.f, 200.f}, "Custom tile size: ", 440);
        Button btm_custom_tile_complete({500.f, 385.f}, "Complete");

        TextManager error_btm_grid("assets/font.ttf", {310.f, 150.f}, sf::Color::Red, 36);
        TextManager error_btm_tile("assets/font.ttf", {310.f, 150.f}, sf::Color::Red, 36);
        bool error_btm_grid_error_state = false;
        bool error_btm_tile_error_state = false;

        //main button to confirm everything
        Button btm_complete_whole({500.f, 625.f}, "Go build!", sf::Color(50,50,50));
        do{
            sf::Event event;
            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed){
                    window.close();
                }
                if(create_custom_grid){
                    tb1.handle_event(event);
                    tb2.handle_event(event);
                }
                if(create_custom_tile){
                    tb3.handle_event(event);
                }
            }
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            if(completed_tilemap && completed_buildtilemap){
                btm_complete_whole.text.setFillColor(sf::Color::White);
                if(btm_complete_whole.clicked(window, mouse_pos)){
                    completed = true;
                }
            }
            if(completed_btm_grid && completed_btm_tile){
                btm_complete.text.setFillColor(sf::Color::White);
                if(btm_complete.clicked(window, mouse_pos)){
                    completed_buildtilemap = true;
                }
            }
            if(create_custom_grid){
                tb1.update(mouse_pos);
                tb2.update(mouse_pos);
            }
            else if(create_custom_tile){
                tb3.update(mouse_pos);
            }
            //std::cout << "x = " << mouse_pos.x << " | y = " << mouse_pos.y << std::endl;
            first_load_text.changeColor(sf::Color::White, true);
            first_load_btm_text.changeColor(sf::Color::White, true);
            if(mouse_pos.x >= 200 && mouse_pos.x < 550 && mouse_pos.y >= 365 && mouse_pos.y < 550 && !completed_tilemap && !create_custom_grid && !create_custom_tile){
                first_load_text.changeColor(sf::Color::Yellow);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    const char *filters[] = { "*.png", "*.jpg", "*.jpeg" };
                    filePath = tinyfd_openFileDialog(
                    "Choose tilemap file",          
                    "",                      
                    3, filters,              
                    "Pictures (*.png, *.jpg, *.jpeg)",                 
                    0                        
                    );
                    if(filePath){
                        sf::Texture catch_dir_err;
                        if(catch_dir_err.loadFromFile(filePath)){
                            errorstate = false;
                            completed_tilemap = true;
                        }
                        else{
                            errorstate = true;
                        }
                        
                    }
                }
            }
            else if(mouse_pos.x >= 650 && mouse_pos.x < 1080 && mouse_pos.y >= 365 && mouse_pos.y < 550){
                first_load_btm_text.changeColor(sf::Color::Yellow);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    configuring_buildtm = true;
                }
            }
            else{
                first_load_text.changeColor(sf::Color::White, true);
                first_load_btm_text.changeColor(sf::Color::White, true);
            }
            window.clear(sf::Color::Black);
            //draw all components
            prev_header.draw(window, "Tilemap Manager 0.1");
            window.draw(outline);
            window.draw(outline_btm);
            window.draw(icon);
            btm_complete_whole.draw(window);
            //tilemap
            if(completed_tilemap){
                window.draw(mark_tm);
                complete_tm.draw(window, "Completed!");
            }
            else{
                window.draw(folder_icon);
                first_load_text.draw(window);
                if(errorstate){
                    error.draw(window, "Wrong file! Try again");
                }
            }
            //build tilemap
            if(completed_buildtilemap){
                window.draw(mark_btm);
                complete_btm.draw(window, "Completed!");
            }
            else{
            if(configuring_buildtm){
                if(!create_custom_grid && !create_custom_tile){
                    int grid_size_index = grid_size_menu.update(window, mouse_pos);
                    int tile_size_index = tile_size_menu.update(window, mouse_pos);
                    if(grid_size_index != -1){
                        if(grid_size_index == 2){
                            create_custom_grid = true;
                        }
                        else{
                            switch(grid_size_index){
                                case 0:
                                    btm_x = 10;
                                    btm_y = 10;
                                    break;
                                case 1:
                                    btm_x = 20;
                                    btm_y = 20;
                                    break;
                            }
                            grid_size_menu.set_element_color(grid_size_index);
                        }
                        completed_btm_grid = true;
                    }
                    else if(tile_size_index != -1){
                        if(tile_size_index == 2){
                            create_custom_tile = true;
                        }
                        else{
                            switch(tile_size_index){
                                case 0:
                                    tile_size = 16;
                                    break;
                                case 1:
                                    tile_size = 32;
                                    break;
                            }
                            tile_size_menu.set_element_color(tile_size_index);
                        }
                        completed_btm_tile = true;
                    }
                }
                grid_size_menu.draw(window);
                tile_size_menu.draw(window);
                btm_complete.draw(window);
            }    
            else{
                first_load_btm_text.draw(window);
                window.draw(settings_icon);
            }
            if(create_custom_grid){
                window.draw(shadow);
                tb1.draw(window);
                tb2.draw(window);
                completed_btm_grid = btm_custom_grid_complete.clicked(window, mouse_pos);
                btm_custom_grid_complete.draw(window);
                if(completed_btm_grid){
                    if(tb1.getter().empty() || tb2.getter().empty()){
                        error_btm_grid_error_state = true;
                    }
                    else{
                        std::string tb_x_grid_string = tb1.getter();
                        std::string tb_y_grid_string = tb2.getter();
                        tb_x_grid_string.pop_back(); tb_x_grid_string.pop_back();
                        tb_y_grid_string.pop_back(); tb_y_grid_string.pop_back();
                        int tb_x_grid, tb_y_grid;
                        try{
                            tb_x_grid = std::stoi(tb_x_grid_string);
                            tb_y_grid = std::stoi(tb_y_grid_string);
                            std::string custom_option = std::to_string(tb_x_grid) + "x" + std::to_string(tb_y_grid);
                            grid_size_menu.update_vector(custom_option);
                            grid_size_menu.set_element_color(grid_size_menu.menu_titles_vec.size()-1);
                            btm_x = tb_x_grid;
                            btm_y = tb_y_grid;
                            create_custom_grid = false;
                        } catch(...){
                            error_btm_grid_error_state = true;
                        }
                    }
                }
                if(error_btm_grid_error_state){
                    error_btm_grid.draw(window, "Enter a valid number (2-99)!");
                }
            }
            else if(create_custom_tile){
                window.draw(shadow);
                tb3.draw(window);
                completed_btm_tile = btm_custom_tile_complete.clicked(window, mouse_pos);
                btm_custom_tile_complete.draw(window);
                if(completed_btm_tile){
                    if(tb3.getter().empty()){
                        error_btm_tile_error_state = true;
                    }
                    else{
                        std::string tb_x_tile_string = tb3.getter();
                        tb_x_tile_string.pop_back(); tb_x_tile_string.pop_back();
                        int tb_x_tile;
                        try{
                            tb_x_tile = std::stoi(tb_x_tile_string);
                            std::string custom_option = std::to_string(tb_x_tile) + "x" + std::to_string(tb_x_tile);
                            tile_size_menu.update_vector(custom_option);
                            tile_size_menu.set_element_color(tile_size_menu.menu_titles_vec.size()-1);
                            create_custom_tile = false;
                            tile_size = tb_x_tile;
                        } catch(...){
                            error_btm_tile_error_state = true;
                        }
                    }
                }
                if(error_btm_tile_error_state){
                    error_btm_tile.draw(window, "Enter a valid number (2-99)!");
                }
            }
            }
            //finish drawing
            window.display();
        } while(!completed);
        window.close();
        file_path = filePath;
    }
}