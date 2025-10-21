#include "input.hpp"
#include <SFML/Window/Keyboard.hpp>

InputState getCarInput() {
    InputState input;
    input.accelerate = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    input.brake      = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    input.turnLeft   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    input.turnRight  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    input.emergencyBrakeButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    return input;
}

void updateInput(std::vector<InputState>& inputs) {
    for (auto& in : inputs) {
        static bool prevPressed = false;
        if (in.emergencyBrakeButton && !prevPressed) {
            in.emergencyBrakeActive = !in.emergencyBrakeActive;
        }
        prevPressed = in.emergencyBrakeButton;
    }
}
