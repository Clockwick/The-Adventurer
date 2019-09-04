
#include "GameState.h"
#include "../Button.h"

#ifndef GUJARUNSFML_MAINMENUSTATE_H
#define GUJARUNSFML_MAINMENUSTATE_H

class Mainmenu : public State
{
public:
    Mainmenu(sf::RenderWindow* window);
    virtual ~Mainmenu();
    void endState();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);


private:
    //Variables
    sf::Font font;
    sf::RectangleShape background;
    //Functions
    void initFonts();


};


#endif //GUJARUNSFML_MAINMENUSTATE_H
