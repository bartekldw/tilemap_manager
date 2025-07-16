#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Textbox{
private:
    sf::Font input_text_font;
    sf::Text input_text;
    std::string input_string;
    std::string user_string;
    sf::RectangleShape input_box;

    sf::RectangleShape position_rect;
    sf::Text info_text;
    bool can_write;
    bool clicked_write;
    bool added_px;
public:
    Textbox(const sf::Vector2f& start_pos, const std::string& text, int text_x_axis_inc);
    void handle_event(const sf::Event& event);
    void draw(sf::RenderWindow& window);
    void update(const sf::Vector2i& mouse_pos);
    std::string getter();
};