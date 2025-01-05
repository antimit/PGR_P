#include "Music.hpp"
#include <iostream>

// Initialize the static instance pointer to nullptr
Music* Music::instance = nullptr;

Music::Music(const std::string &musicFilePath) 
{
    if (!music.openFromFile(musicFilePath))  // Try to load the music file
    {
        std::cout << "Error loading music from file: " << musicFilePath << std::endl;
    }
    else
    {
        music.setVolume(50);  // Set initial volume (50% as a default)
        music.setLoop(true);
    }
}

Music& Music::getInstance(const std::string &musicFilePath)
{
    // Check if the instance is already created, if not create it
    if (instance == nullptr)
    {
        instance = new Music(musicFilePath);  // Create the instance if it's not yet created
    }
    return *instance;
}

void Music::update_music_volume()
{
    SliderSFML &slider = SliderSFML::getInstance();
    float volume = slider.getSliderValue(); // Get the slider value (expected range: 0 to 100)
    // std::cout <<"Volume updated" <<std::endl;
    music.setVolume(volume); // Set the volume of the music (0 to 100 range)
}

void Music::play()
{
    if (music.getStatus() != sf::Music::Playing)  // Check if music is already playing
    {
        music.play();  // Play the music
    }
}

void Music::stop()
{
    music.stop();  // Stop the music
}

void Music::setLoop()
{
    music.setLoop(true);  // Loop the music
}

void Music::setVolume(float volume)
{
    music.setVolume(volume);  // Set the volume directly
}

void Music::pause()
{
    music.pause();  // Pause the music
}

bool Music::isPlaying() const
{
    return music.getStatus() == sf::Music::Playing;  // Check if the music is playing
}
