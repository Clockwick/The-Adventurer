#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#ifndef GUJARUNSFML_BUTTON_H
#define GUJARUNSFML_BUTTON_H


enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui {
    class Button {
    public:
        Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
            sf::Color outline_idle_color = sf::Color::Transparent,
            sf::Color outline_hover_color = sf::Color::Transparent,
            sf::Color outline_active_color = sf::Color::Transparent,
            unsigned short id = 0);

        ~Button();

        //Accessories
        const bool isPressed() const;
        const std::string getText() const;
        const unsigned short& getId() const;

        //Modifiers
        void setText(const std::string text);
        void setId(const unsigned short id);

        //Functions
        void render(sf::RenderTarget &target);
        void update(const sf::Vector2f mousePos);

    private:

        unsigned short buttonStates;
        unsigned short id;

        bool pressed;
        bool hover;


        sf::RectangleShape shape;
        sf::Font *font;
        sf::Text text;


        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color outlineidleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;


    };

    class DropDownList
    {
    public:
        DropDownList(float x , float y, float width, float height,
                sf::Font& font, std::string list[],unsigned numofElements, const unsigned default_index = 0);
        virtual ~DropDownList();
    public://Functions
        void update(const sf::Vector2f& mousePos, const float& dt);
        void render(sf::RenderTarget& target);
        void updateKeytime(const float& dt);
        const bool getKeytime();
        const unsigned short& getActiveElementId() const;

    private:
        float keytime;
        float keytimeMax;


        sf::Font& font;
        gui::Button* activeElement;
        std::vector <gui::Button*> list;
        bool showList;


        //Accessors

    };

    class TextureSelector
    {

    public:
        TextureSelector(float x, float y, float width, float height,float gridSize, const sf::Texture* texture_sheet);
        ~TextureSelector();

        //Accessor
        const bool& getActive();

        //Functions

        void update(const sf::Vector2i& mousePosWindow);
        void render(sf::RenderTarget& target);

    private:
        sf::RectangleShape bounds;
        sf::Sprite sheet;
        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;
        sf::IntRect textureRect;

        bool active;
        float gridSize;

    };

}


#endif //GUJARUNSFML_BUTTON_H
