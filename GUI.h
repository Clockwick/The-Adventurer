#include "Precom.h"
#include "Entities/Player.h"
#ifndef GUJARUNSFML_BUTTON_H
#define GUJARUNSFML_BUTTON_H


enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui {

    const float p2pX(const float perc, const sf::VideoMode& vm);
    const float p2pY(const float perc, const sf::VideoMode& vm);
    const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 130);
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
        void update(const sf::Vector2i& mousePosWindow);

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
    public:
        //Functions
        void update(const sf::Vector2i& mousePosWindow, const float& dt);
        void render(sf::RenderTarget& target);
        void updateKeytime(const float& dt);
        //Accessor
        const bool getKeytime();
        const unsigned short& getActiveElementId() const;

    private:
        float keytime;
        float keytimeMax;


        sf::Font& font;
        gui::Button* activeElement;
        std::vector <gui::Button*> list;
        bool showList;


    };

    class TextureSelector
    {

    public:
        TextureSelector(float x, float y, float width, float height,float* gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
        ~TextureSelector();

        //Accessor
        const bool& getActive();
        const sf::IntRect& getTextureRect() const;

        //Functions

        void update(const sf::Vector2i& mousePosWindow, const float& dt);
        void render(sf::RenderTarget& target);

        const bool getKeytime();
        void updateKeytime(const float& dt);

    private:
        sf::RectangleShape bounds;
        sf::Sprite sheet;
        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;
        sf::IntRect textureRect;
        gui::Button* hide_button;

        bool active;
        bool hidden;
        float gridSize;
        float keytime;
        const float keytimeMax;
        float* ptr;

    };

    class InventorySelector
    {
    public:
        InventorySelector(float x, float y, float width, float height,float gridSize, sf::Font& font, std::string text);
        ~InventorySelector();

        //Accessor
        const bool& getActive();
        const sf::IntRect& getTextureRect() const;
        const bool& getInventoryActive();

        //Functions

        void update(const sf::Vector2i& mousePosWindow, const float& dt);
        void render(sf::RenderTarget& target);

        const bool getKeytime();
        void updateKeytime(const float& dt);

    private:
        sf::RectangleShape bounds;
        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;
        sf::IntRect textureRect;
        gui::Button* hide_button;

        bool active;
        bool hidden;
        float gridSize;
        float keytime;
        const float keytimeMax;




        //Sidebar
        sf::RectangleShape inventoryTag;
        bool inventoryActive;
        sf::Text inventoryText;

    };
    class TextGui
    {
    private:

        //Text
        sf::Font* textFont;
        sf::Text text;
        sf::Text value;

        void initVariables();

    public:
        TextGui(float x, float y, sf::Font* font, unsigned char_size, sf::Color text_color, sf::Color outline_color, std::string text, std::string value, const short type = 0);
        virtual ~TextGui();

        void render(sf::RenderTarget& target);
        void update(const std::string value);



    };
    class Status
    {
    public:
        Status(Player* player, float x, float y, float width, float height,float gridSize, sf::Font& font, std::string text, const std::string player_name);
        ~Status();

        //Accessor
        const bool& getActive();
        const sf::IntRect& getTextureRect() const;
        const bool& getInventoryActive();

        //Functions

        void update(const sf::Vector2i& mousePosWindow, const float& dt);
        void render(sf::RenderTarget& target);
        void updateButtons(const sf::Vector2i& mousePosWindow);
        void renderButtons(sf::RenderTarget &target);

        const bool getKeytime();
        void updateKeytime(const float& dt);

    private:
        std::map <std::string,gui::Button*> buttons;
        void initButtons();
        bool activeButtons;
        std::vector<int> statusStorage;
        std::vector <int> saveStatusStorage;
        sf::RectangleShape bounds;
        sf::Vector2u mousePosGrid;
        sf::IntRect textureRect;
        gui::Button* hide_button;

        bool active;
        bool hidden;
        float gridSize;
        float keytime;
        const float keytimeMax;

        float spaceY;
        float firstCol;
        float secondCol;
        float thirdCol;


        //Sidebar
        sf::RectangleShape statusTag;
        bool statusActive;
        sf::Text statusText;


        //Main
        sf::RectangleShape profileShape;
        sf::Texture profileTexture;
        sf::IntRect profilePlayer;

        //Text
        gui::TextGui* vitText;
        gui::TextGui* strText;
        gui::TextGui* dexText;
        gui::TextGui* agiText;
        gui::TextGui* luckText;
        gui::TextGui* intText;

        gui::TextGui* name;
        gui::TextGui* levelText;
        gui::TextGui* statPoints;
        gui::TextGui* hpText;

        gui::TextGui* dmgText;
        gui::TextGui* levelNextText;

        Player* player;
        std::string playerName;


        //Font
        sf::Font *statusFont;
        void allText();
        void initText();
        void initVariables();
        void initProfile();

    };



}


#endif //GUJARUNSFML_BUTTON_H
