#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>
#include <string>
#include "Slider.hpp"

class Music {
public:
    
    static Music& getInstance(const std::string &musicFilePath = "");

    
    void update_music_volume();
    void play();
    void stop();
    void setLoop();
    void setVolume(float volume);
    void pause();
    bool isPlaying() const;

private:
    
    Music(const std::string &musicFilePath);

    
    static Music* instance;

    
    sf::Music music;

    
    Music(const Music&) = delete;
    Music& operator=(const Music&) = delete;
};

#endif 
