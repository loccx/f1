#include "input.hpp"

InputState getCarInput() {
    InputState input{};
    input.accelerate = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    input.brake      = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    input.turnLeft   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    input.turnRight  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    return input;
}

