#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "Menu.hpp"
#include "Button.hpp"
MenuDisplay::MenuDisplay(const sf::Vector2f& button_pos, const std::string& button_text, const std::vector<std::string>& menu_titles, int custom_x) : button(button_pos,button_text,sf::Color::White, custom_x), button_pos_vec(button_pos), menu_titles_vec(menu_titles){
    this->bg.setPosition(button_pos.x+30.f, button_pos.y+30.f);
    this->bg.setSize(sf::Vector2f{max_string(menu_titles).size()*36.f, menu_titles.size()*36.f});
    this->bg.setFillColor(sf::Color(40,40,40));
    this->font.loadFromFile("../assets/font.ttf");
    for(int i = 0; i < menu_titles.size(); ++i){
        sf::Text cur_text;
        cur_text.setFont(this->font);
        cur_text.setString(menu_titles[i]);
        cur_text.setCharacterSize(36.f);
        cur_text.setPosition(button_pos.x+30.f, ((button_pos.y+30.f) + 36.f * i));
        cur_text.setFillColor(sf::Color::White);
        this->menu_text.push_back(cur_text);
    }
    this->should_display_menu = false;
    this->main_id = -1;
}
void MenuDisplay::update_position(const sf::Vector2i& mouse_pos){
    if(!this->should_display_menu){
        this->bg.setPosition(mouse_pos.x, mouse_pos.y);
        int i = -1;
        for(auto& element : this->menu_text){
            element.setPosition(mouse_pos.x, ((mouse_pos.y+30.f) + 36.f * i));
            i++;
        }
    }
}
std::string MenuDisplay::max_string(const std::vector<std::string>& menu_titles){
    std::string biggest_string = "";
    for(const auto& element : menu_titles){
        if(element.size() > biggest_string.size()){
            biggest_string = element;
        }
    }
    return biggest_string;
}
int MenuDisplay::update(sf::RenderWindow& window, const sf::Vector2i& mouse_pos){ //int function, as it returns index (int) of the options we choose
    if(this->button.clicked(window,mouse_pos)){
        this->update_position(mouse_pos);
        this->should_display_menu = true;
    }
    else if(!this->bg.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))){
        this->should_display_menu = false;
    }
    int index_count = 0;
    for(auto& element : this->menu_text){
        if(element.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))){
            element.setFillColor(sf::Color::Yellow);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                this->should_display_menu = false;
                return index_count;
            }
        }
        else{
            element.setFillColor(sf::Color::White);
        }
        index_count++;
    }
    if(this->main_id != -1){
        this->menu_text[main_id].setFillColor(sf::Color::Green);
    }
    return -1;
}
void MenuDisplay::draw(sf::RenderWindow& window){
    if(this->should_display_menu){
        this->button.text.setFillColor(sf::Color::Yellow);
    }
    this->button.draw(window);
    if(this->should_display_menu){
        window.draw(this->bg);
        for(const auto& element : this->menu_text){
            window.draw(element);
        }
    }
}

void MenuDisplay::update_vector(const std::string& new_option){
    this->menu_text.clear();
    this->menu_text.shrink_to_fit();
    menu_titles_vec.push_back(new_option);
    this->bg.setSize(sf::Vector2f{max_string(menu_titles_vec).size()*36.f, menu_titles_vec.size()*36.f});
    for(int i = 0; i < this->menu_titles_vec.size(); ++i){
        sf::Text cur_text;
        cur_text.setFont(this->font);
        cur_text.setString(this->menu_titles_vec[i]);
        cur_text.setCharacterSize(36.f);
        cur_text.setPosition(this->button_pos_vec.x+30.f, ((this->button_pos_vec.y+30.f) + 36.f * i));
        cur_text.setFillColor(sf::Color::White);
        this->menu_text.push_back(cur_text);
    }
}
void MenuDisplay::set_element_color(int id){
    //this->menu_text[id].setFillColor(sf::Color::Green);
    this->main_id = id;
}