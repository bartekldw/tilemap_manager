#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Textbox.hpp"
Textbox::Textbox(const sf::Vector2f& start_pos, const std::string& text, int text_x_axis_inc){
    this->input_text_font.loadFromFile("../assets/font.ttf");
    this->input_text.setFont(this->input_text_font);
    this->input_text.setPosition(start_pos.x+8.f, start_pos.y+4.f);
    this->input_text.setFillColor(sf::Color::White);
    this->input_text.setCharacterSize(36.f);

    this->input_box.setPosition(start_pos);
    this->input_box.setSize({120.f, 50.f});
    this->input_box.setOutlineColor(sf::Color(172, 117, 52));
    this->input_box.setOutlineThickness(5.f);
    this->input_box.setFillColor(sf::Color::Black);

    this->info_text.setFont(this->input_text_font);
    this->info_text.setString(text);
    this->info_text.setPosition(start_pos.x-text_x_axis_inc, start_pos.y+4.f);
    this->info_text.setFillColor(sf::Color::White);
    this->info_text.setCharacterSize(36.f);
    
    this->position_rect.setPosition(start_pos.x + 7.f, start_pos.y + 40.f);
    this->position_rect.setSize(sf::Vector2f{25.f, 3.f});
    this->position_rect.setFillColor(sf::Color::White);

    this->can_write = false;
    this->clicked_write = false;
    this->added_px = false;
}

void Textbox::update(const sf::Vector2i& mouse_pos){
    if(this->input_box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            this->position_rect.setFillColor(sf::Color::Yellow);
            this->clicked_write = true;
        }
        this->can_write = true;
    }
    else{
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            if(!this->added_px && !this->user_string.empty()){
                this->user_string += "px";
                this->input_text.setString(this->user_string);
                this->position_rect.move(30.f, 0.f);
                this->added_px = true;
            }
            this->position_rect.setFillColor(sf::Color::White);
            this->clicked_write = false;
        }
        this->can_write = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        if(this->can_write || this->clicked_write){
            if(this->user_string.size() < 4 && !this->user_string.empty() && !added_px){
                this->user_string += "px";
                this->position_rect.move(30.f, 0.f);
                this->input_text.setString(this->user_string);
                this->added_px = true;
            }
        }
        this->clicked_write = false;
        this->can_write = false;
    }
}

void Textbox::handle_event(const sf::Event& event){
   if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && !this->user_string.empty()) { // backspace
            if(this->can_write || this->clicked_write){
                if(this->user_string.size() >= 3){
                    this->position_rect.move(-30.f, 0.f);
                    this->user_string.pop_back();
                    this->user_string.pop_back();
                    this->added_px = false;
                }
                this->position_rect.move(-30.f, 0.f);
                this->user_string.pop_back();
            }
            
        }
        else if (event.text.unicode >= '0' && event.text.unicode <= '9' && this->user_string.size() < 2) {
            if(this->can_write || this->clicked_write){
                this->user_string += static_cast<char>(event.text.unicode);
                this->position_rect.move(30.f, 0.f);
                if(this->user_string.size() == 2){
                    this->position_rect.move(30.f, 0.f);
                    this->added_px = true;
                    this->user_string += "px";
                }
            }
        }       
        if(this->can_write || this->clicked_write){this->input_text.setString(this->user_string);}
    } 
}

void Textbox::draw(sf::RenderWindow& window){
    window.draw(this->input_box);
    window.draw(this->input_text);
    window.draw(this->info_text);
    if(this->can_write || clicked_write){
        window.draw(this->position_rect);
    }
}

std::string Textbox::getter(){
    return this->user_string;
}
