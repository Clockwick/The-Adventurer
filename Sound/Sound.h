//
// Created by Paratthakorn Sribunyong on 22/10/2019 AD.
//

#ifndef GUJARUNSFML_SOUND_H
#define GUJARUNSFML_SOUND_H
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>

class Sound
{

public:
    Sound(std::string audio_link);
    virtual ~Sound();
    void updateAudio();



private:
    sf::Sound soundBG;
    sf::SoundBuffer soundBufferBG;

};

#endif //GUJARUNSFML_SOUND_H
