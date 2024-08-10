#include "sound.h"

std::vector<sf::Sound> sounds;
sf::SoundBuffer buffer;

// Function to load a sound buffer from a file
bool loadSoundBuffer(const std::string& filePath){
    return buffer.loadFromFile(filePath);
}

// Function to find an available (stopped) sound instance, or return nullptr if none are available
sf::Sound* findAvailableSound(){
    for (auto& sound : sounds){
        if (sound.getStatus() == sf::Sound::Stopped){
            return &sound;
        }
    }
    return nullptr; // No available sound found
}

// Function to create a new sound instance, sets its buffer, plays it, and returns the instance
void createAndPlaySound(){
    sounds.emplace_back(); // Add a new sf::Sound to the end of the vector
    auto& sound = sounds.back();
    sound.setBuffer(buffer);
    if(SLOW_MO)
        sound.setPitch(randomInRange(0.65f, 0.75f));
    else
        sound.setPitch(randomInRange(0.9f, 1.0f));
    sound.setVolume(10.0f);
    sound.play();
}

// Function to play the sound, reusing or creating instances as necessary
void playSound(){
    sf::Sound* sound = findAvailableSound();
    if (sound){
        if(SLOW_MO)
            sound->setPitch(randomInRange(0.65f, 0.75f));
        else
            sound->setPitch(randomInRange(0.9f, 1.0f));
        sound->play();
    }
    else
        createAndPlaySound();
}

void playSoundSilentlyMultipleTimes(int times) {
    // Ensure the buffer is loaded before attempting to play
    if (!buffer.getSampleCount()){
        std::cerr << "Buffer is empty, load a sound file first." << std::endl;
        return;
    }

    for (int i = 0; i < times; ++i) {
        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.setVolume(0); // Mute the sound
        sound.play();

        // Keep track of the sound to allow it to finish playing silently
        sounds.push_back(std::move(sound));

    }

    // Wait for all sounds to finish
    bool allStopped = false;
    while (!allStopped){
        allStopped = true;
        for (auto& sound : sounds){
            if (sound.getStatus() != sf::Sound::Stopped) {
                allStopped = false;
                break; // If any sound is still playing, break out and check again
            }
        }
    }

    // Optionally clear sounds that have finished playing
    sounds.erase(std::remove_if(sounds.begin(), sounds.end(),
                                [](const sf::Sound& sound) {
                                    return sound.getStatus() == sf::Sound::Stopped;
                                }),
                 sounds.end());
}
