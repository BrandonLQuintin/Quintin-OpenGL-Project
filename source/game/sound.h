#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "../globals.h"

extern std::vector<sf::Sound> sounds;
extern sf::SoundBuffer buffer;

bool loadSoundBuffer(const std::string& filePath);

sf::Sound* findAvailableSound();

void createAndPlaySound();

void playSound();

void playSoundSilentlyMultipleTimes(int times);
