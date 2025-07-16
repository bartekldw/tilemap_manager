#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextManager.hpp"
TextManager::TextManager(const std::string& font_directory, const sf::Vector2f& pos, const sf::Color& color, int size){
    if(!this->font.loadFromFile("../" + font_directory)){
        std::cout << "TU DODAC EXCEPT" << std::endl; // <----------- HERE ADD TO LOG ERR
    }
    this->text.setFont(this->font);
    this->text.setPosition(pos);
    this->text.setFillColor(color);
    this->text.setCharacterSize(size);
}
TextManager::TextManager(const std::string& font_directory, //CHECK TEXTMANAGER.HPP FOR CONSTRUCTOR EXPLANATION
                const sf::Vector2f& first_pos, const sf::Color& first_color, const std::string& first_string, 
                const sf::Color& sec_color, const std::string& sec_string,
                const sf::Color& third_color, const std::string& third_string, int size){
    if(!this->font.loadFromFile("../" + font_directory)){
        std::cout << "TU DODAC EXCEPT" << std::endl; // <----------- tutaj dodac logi pozniej
    }
    //first text
    this->text.setFont(this->font);
    this->text.setPosition(first_pos);
    this->text.setFillColor(first_color);
    this->text.setCharacterSize(size);
    this->text.setString(first_string);
    float first_width = this->text.getLocalBounds().width; //here, we calculate the first text width - to set position for seonc text
    //sec text
    this->sec_text.setFont(this->font);
    this->sec_text.setPosition({first_pos.x + first_width + 15.f, first_pos.y});
    //this->sec_text.setPosition({first_pos.x + (5*first_string.size()), first_pos.y}); //here, we calculate the position automaticly (5 times more (x axis) than first string size)
    this->sec_text.setFillColor(sec_color);
    this->sec_text.setCharacterSize(size);
    this->sec_text.setString(sec_string);
    //third text
    this->third_text.setFont(this->font);
    this->third_text.setPosition({first_pos.x, first_pos.y + 30.f}); //the position is unique, as it's under 2 first texts
    this->third_text.setFillColor(third_color);
    this->third_text.setCharacterSize(size);
    this->third_text.setString(third_string);

}
void TextManager::draw(sf::RenderWindow& window, const std::string& text){
    this->text.setString(text);
    window.draw(this->text);
}
void TextManager::draw(sf::RenderWindow& window){ //supports second constructor!
    window.draw(this->text);
    window.draw(this->sec_text);
    window.draw(this->third_text);
}
void TextManager::changeColor(const sf::Color& color, bool supportuniquecolor){
    this->text.setFillColor(color);
    if(supportuniquecolor){
        this->sec_text.setFillColor(sf::Color::Blue);
    }
    else{
        this->sec_text.setFillColor(color);
    }
    this->third_text.setFillColor(color);
}