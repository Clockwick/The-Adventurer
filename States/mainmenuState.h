
#include "GameState.h"
#include "../GUI.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "../GraphicsSettings.h"

#ifndef GUJARUNSFML_MAINMENUSTATE_H
#define GUJARUNSFML_MAINMENUSTATE_H

class Mainmenu : public State
{
public:
    Mainmenu(StateData* state_data);
    virtual ~Mainmenu();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);

    void updateButtons();
    void renderButtons(sf::RenderTarget& target);


private:
    //Variables
    sf::Font font;
    sf::RectangleShape background;
    gui::Button* gamestates_btn;
    std::map <std::string, gui::Button*> buttons;
    sf::Texture backgroundTexture;
    //Functions
    void initFonts();
    void initButtons();
    void initBackground();
    void initVariables();


};


#endif //GUJARUNSFML_MAINMENUSTATE_H
