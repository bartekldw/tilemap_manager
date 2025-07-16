#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class TextManager{
private:
    sf::Font font;
    sf::Text text;
    //unique texts (supports 3, belong to second overloaded constructor)
    sf::Text sec_text;
    sf::Text third_text;
public:
    TextManager(const std::string& font_directory, const sf::Vector2f& pos, const sf::Color& color, int size); 
    TextManager(const std::string& font_directory, //here, the constructor supports a few texts with unique colors
                const sf::Vector2f& first_pos, const sf::Color& first_color, const std::string& first_string, //the data of first text
                const sf::Color& sec_color, const std::string& sec_string,//the data of second text (here, the start_pos is calculated automaticly)
                const sf::Color& third_color, const std::string& third_string, int size); //the data of third text (pos calculated automaticly, as higher, check TextManager.cpp for more info) and the size (equal to all texts)
    //^ ALSO, it only supports the second "draw" function, due to the fact that we need to calculate position (so, we need text in constructor!)
    void draw(sf::RenderWindow& window, const std::string& text); 
    void draw(sf::RenderWindow& window); 

    //helper function to change colors of 3 texts
    void changeColor(const sf::Color& color, bool supportuniquecolor = false);
};