#pragma once
#include <SFML/Graphics.hpp>
class Button{
private:
    sf::Font font;
    sf::RectangleShape o_button_outline;

    static int animation_counter;
    sf::Vector2f current_scale;

public:
    sf::RectangleShape d_button_base;
    sf::Text text;
    Button(const sf::Vector2f& start_pos, const std::string& text, const sf::Color& text_color = sf::Color::White, int custom_size_x = 0); //custom_size_x = increment
    void draw(sf::RenderWindow& window);
    void set_position(const sf::Vector2f& start_pos, int custom_size_x = 0);
    bool clicked(sf::RenderWindow& window, const sf::Vector2i& mouse_pos);
    
};