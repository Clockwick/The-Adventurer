//IMPORT EVERYTHINGS

#ifndef GUJARUNSFML_STATE_H
#define GUJARUNSFML_STATE_H
#include "../Entities/Player.h"
class State
{
public:
    State(sf::RenderWindow* window, std::stack <State*>* states);
    virtual ~State();
    //Virtual Functions
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
    virtual void update(const float& dt) = 0;
    virtual void updateInput(const float& dt) = 0;
    virtual void updateMousePos() ;
    virtual void updateKeytime(const float& dt);

    //Functions
    void endState();
    void pauseState();
    void unpauseState();
    //Accessor
    const bool& getQuit() const;
    const bool getKeyTime();



public:
    std::stack <State*>* states;


protected:
    std::map <std::string, sf::Texture> textures;
    sf::RenderWindow* window;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    bool quit;
    bool paused;
    float keyTime;
    float keyTimeMax;
private:

};


#endif //GUJARUNSFML_STATE_H
