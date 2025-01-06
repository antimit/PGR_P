#include "Music.hpp"
#include <iostream>


Music* Music::instance = nullptr;

Music::Music(const std::string &musicFilePath) 
{
    if (!music.openFromFile(musicFilePath))  
    {
        std::cout << "Error loading music from file: " << musicFilePath << std::endl;
    }
    else
    {
        music.setVolume(50);  
        music.setLoop(true);
    }
}

Music& Music::getInstance(const std::string &musicFilePath)
{
    
    if (instance == nullptr)
    {
        instance = new Music(musicFilePath);  
    }
    return *instance;
}

void Music::update_music_volume()
{
    SliderSFML &slider = SliderSFML::getInstance();
    float volume = slider.getSliderValue(); 
    
    music.setVolume(volume); 
}

void Music::play()
{
    if (music.getStatus() != sf::Music::Playing)  
    {
        music.play();  
    }
}

void Music::stop()
{
    music.stop();  
}

void Music::setLoop()
{
    music.setLoop(true);  
}

void Music::setVolume(float volume)
{
    music.setVolume(volume);  
}

void Music::pause()
{
    music.pause();  
}

bool Music::isPlaying() const
{
    return music.getStatus() == sf::Music::Playing;  
}
