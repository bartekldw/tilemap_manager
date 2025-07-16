#pragma once
#include "Button.hpp"
#include <vector>
#include <string>
class MenuDisplay{
private:
    Button button;
    sf::RectangleShape bg;
    std::vector<sf::Text> menu_text;
    bool should_display_menu;
    sf::Vector2f button_pos_vec;
    sf::Text text;
    int main_id;
    sf::Font font;
    //helper function to calculate the biggest string 
    std::string max_string(const std::vector<std::string>& menu_titles);
    //helper function to make the menu show in the mouse pos
    void update_position(const sf::Vector2i& mouse_pos);
public:
    std::vector<std::string> menu_titles_vec;
    MenuDisplay(const sf::Vector2f& button_pos, const std::string& button_text, const std::vector<std::string>& menu_titles, int custom_x);
    void draw(sf::RenderWindow& window);
    int update(sf::RenderWindow& window, const sf::Vector2i& mouse_pos);
    void update_vector(const std::string& new_option);
    void set_element_color(int id);
};