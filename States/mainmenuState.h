
#include "GameState.h"
#include "../Button.h"

#ifndef GUJARUNSFML_MAINMENUSTATE_H
#define GUJARUNSFML_MAINMENUSTATE_H

class Mainmenu : public State
{
public:
    Mainmenu(sf::RenderWindow* window, std::stack <State*>* states);
    virtual ~Mainmenu();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);
    void initButtons();
    void initBackground();
    void initVariables();
    void updateButtons();
    void renderButtons(sf::RenderTarget* target = nullptr);


private:
    //Variables

    sf::Font font;
    sf::RectangleShape background;
    Button* gamestates_btn;
    std::map <std::string, Button*> buttons;
    sf::Texture backgroundTexture;
    //Functions
    void initFonts();


};


#endif //GUJARUNSFML_MAINMENUSTATE_H
