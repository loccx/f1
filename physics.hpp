// physics.hpp
#pragma once
#include <vector>
#include <SFML/System.hpp>

struct InputState {
    bool accelerate = false;
    bool brake = false;
    bool turnLeft = false;
    bool turnRight = false;
};

struct Cars {
    std::vector<sf::Vector2f> position;
    std::vector<sf::Vector2f> velocity;
    std::vector<float> rotation;
};

void updateCarsPhysics(Cars& cars, const std::vector<InputState>& inputs, float dt);

