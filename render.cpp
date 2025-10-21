#include "render.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>

void renderCars(sf::RenderWindow& window, const Cars& cars, const sf::Texture& carTexture) {
    for (size_t i = 0; i < cars.position.size(); ++i) {
        sf::Sprite car(carTexture);
        car.setOrigin({carTexture.getSize().x / 2.f, carTexture.getSize().y / 2.f});
        car.setPosition(cars.position[i]);
        car.setRotation(sf::degrees(cars.rotation[i] * 180.f / 3.14159265f + 180.f));
        window.draw(car);
    }
}

