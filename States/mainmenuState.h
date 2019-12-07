
#include "GameState.h"
#include "../GUI.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "../GraphicsSettings.h"
#include "NameState.h"
#include "ScoreState.h"

#ifndef GUJARUNSFML_MAINMENUSTATE_H
#define GUJARUNSFML_MAINMENUSTATE_H

class Mainmenu : public State
{
public:
    Mainmenu(StateData* state_data, sf::Event* event);
    virtual ~Mainmenu();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);

    void updateButtons();
    void renderButtons(sf::RenderTarget& target);


private:
    //Variables
    std::map <std::string,sf::Font> fonts;
    sf::RectangleShape background;
    sf::RectangleShape btnBackground;
    std::map <std::string, gui::Button*> buttons;
    sf::Texture backgroundTexture;
    sf::RectangleShape backgroundLogo;

    sf::Text logoText;

    //Audio

    sf::Sound soundBt;
    sf::SoundBuffer soundBufferBt;
    sf::Music musicBG;
    //Functions
    void initFonts();
    void initGui();
    void initVariables();
    void initAudio();
    void resetGui();
    void initLogo();
    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;
    sf::Text myName;
    sf::Event* event;

    //bool
    bool showBox;
    NameState* nameState;




};


#endif //GUJARUNSFML_MAINMENUSTATE_H
