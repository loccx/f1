#include "input.hpp"
#include <SFML/Window/Keyboard.hpp>

InputState getCarInput() {
    InputState input;
    input.accelerate = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    input.brake      = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    input.turnLeft   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    input.turnRight  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    input.ebrake = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P);

    return input;
}

void updateInput(std::vector<InputState>& inputs) {
    for (auto& in : inputs) {
        if (in.ebrake) {
            in.emergencyBrakeActive ^= 1;
        }
    }
}
