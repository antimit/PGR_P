#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>
#include <string>
#include "Slider.hpp"

class Music {
public:
    // Public static method to get the singleton instance
    static Music& getInstance(const std::string &musicFilePath = "");

    // Methods to control music
    void update_music_volume();
    void play();
    void stop();
    void setLoop();
    void setVolume(float volume);
    void pause();
    bool isPlaying() const;

private:
    // Private constructor (so no one else can create an instance)
    Music(const std::string &musicFilePath);

    // Private static instance of the Music class
    static Music* instance;

    // SFML music object
    sf::Music music;

    // Delete copy constructor and assignment operator to prevent copies
    Music(const Music&) = delete;
    Music& operator=(const Music&) = delete;
};

#endif // MUSIC_HPP
