#pragma once
#include "physics.hpp"
#include <SFML/Window/Keyboard.hpp>

struct InputState {
    bool accelerate = false;
    bool brake = false;
    bool turnLeft = false;
    bool turnRight = false;
    bool emergencyBrakeButton = false;
    bool emergencyBrakeActive = false;
};

InputState getCarInput();

void updateInput(std::vector<InputState>& inputs);
