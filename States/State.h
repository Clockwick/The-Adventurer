//IMPORT EVERYTHINGS

#ifndef GUJARUNSFML_STATE_H
#define GUJARUNSFML_STATE_H
#include "../Entities/Entity.h"
class State
{
public:
    State(sf::RenderWindow* window);
    virtual ~State();
    virtual void endState() = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
    virtual void update(const float& dt) = 0;
    virtual void checkForQuit();
    virtual void updateInput(const float& dt) = 0;
    virtual void updateMousePos() ;
    const bool& getQuit() const;


protected:
    std::vector <sf::Texture> textures;
    sf::RenderWindow* window;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    bool quit;
private:

};


#endif //GUJARUNSFML_STATE_H
