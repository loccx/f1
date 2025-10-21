#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "input.hpp"

struct InputState;

struct Cars {
    std::vector<sf::Vector2f> position;
    std::vector<sf::Vector2f> velocity;
    std::vector<float> rotation;
};

void updateCarsPhysics(Cars& cars, const std::vector<InputState>& inputs, float dt, const sf::Image& trackImage);

