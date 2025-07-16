#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"
int Button::animation_counter = 1;
Button::Button(const sf::Vector2f& start_pos, const std::string& text, const sf::Color& text_color, int custom_size_x){ //custom_size_x means the incrementation for x-axis
    //size
    sf::Vector2f size = {200.f + custom_size_x, 50.f};
    //button text
    this->font.loadFromFile("../assets/font.ttf");
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(36);
    this->text.setFillColor(text_color);
    //get text global bounds (width, height)
    sf::FloatRect textBounds = this->text.getGlobalBounds();
    this->text.setOrigin(textBounds.left + (textBounds.width/2.f), textBounds.top + (textBounds.height/2.f));
    sf::Vector2f shape_center = start_pos + (size/2.f);
    this->text.setPosition(shape_center);
    //button base
    this->d_button_base.setPosition(start_pos);
    this->d_button_base.setSize(size);
    this->d_button_base.setFillColor(sf::Color(0,0,0,0));

    //button outline
    this->o_button_outline.setPosition(start_pos);
    this->o_button_outline.setSize(size);
    this->o_button_outline.setFillColor(sf::Color(0,0,0,0));
    this->o_button_outline.setOutlineColor(sf::Color(172, 117, 52));
    this->o_button_outline.setOutlineThickness(5.f);

}
void Button::draw(sf::RenderWindow& window){
    window.draw(this->d_button_base);
    window.draw(this->text);
    window.draw(this->o_button_outline);
}
void Button::set_position(const sf::Vector2f& start_pos, int custom_size_x){
    sf::Vector2f size = {200.f + custom_size_x, 50.f};
    sf::Vector2f shape_center = start_pos + (size/2.f);
    this->text.setPosition(shape_center);
    this->d_button_base.setPosition(start_pos);
    this->o_button_outline.setPosition(start_pos);
}
bool Button::clicked(sf::RenderWindow& window, const sf::Vector2i& mouse_pos){
    if(this->d_button_base.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))){
        this->text.setFillColor(sf::Color::Yellow);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            return true;
        }
    }
    else{
        this->text.setFillColor(sf::Color::White);
        return false;
    }
    return false;
}
