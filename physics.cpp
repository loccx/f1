#include "physics.hpp"
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>

inline float dot(const sf::Vector2f& a, const sf::Vector2f& b) {
    return a.x * b.x + a.y * b.y;
}

void updateCarsPhysics(Cars& cars, const std::vector<InputState>& inputs, float dt, const sf::Image& trackImage) {
    const float maxForwardSpeed = 1200.f;
    const float maxBackwardSpeed = 600.f;
    const float acceleration = 800.f;
    const float friction = 300.f;
    const float turnSpeed = 2.f;
    const float baseGrip = 0.8f;

    sf::Vector2u imgSize = trackImage.getSize();
    size_t N = cars.position.size();

    for (size_t i = 0; i < N; ++i) {
        sf::Vector2f forward{std::sin(cars.rotation[i]), -std::cos(cars.rotation[i])};
        sf::Vector2f right{-forward.y, forward.x};

        float forwardVel = dot(cars.velocity[i], forward);
        float lateralVel = dot(cars.velocity[i], right);

        if (inputs[i].accelerate) forwardVel += acceleration * dt;
        if (inputs[i].brake) forwardVel -= acceleration * dt;

        forwardVel = std::clamp(forwardVel, -maxBackwardSpeed, maxForwardSpeed);

        float grip = baseGrip;
        if (inputs[i].emergencyBrakeActive) {
            grip = 0.05f;
            forwardVel *= 0.9f;
        }
        lateralVel *= grip;

        if (!inputs[i].accelerate && !inputs[i].brake && !inputs[i].emergencyBrakeActive) {
            forwardVel -= friction * dt * (forwardVel > 0.f ? 1.f : -1.f);
            if (std::abs(forwardVel) < 1.f) forwardVel = 0.f;
        }

        float speedFactor = std::min(std::abs(forwardVel) / maxForwardSpeed, 1.f);
        float turnAmount = turnSpeed * dt * speedFactor;
        if (inputs[i].turnLeft)  cars.rotation[i] -= turnAmount;
        if (inputs[i].turnRight) cars.rotation[i] += turnAmount;

        cars.velocity[i] = forward * forwardVel + right * lateralVel;
        sf::Vector2f newPos = cars.position[i] + cars.velocity[i] * dt;

        unsigned x = std::clamp(static_cast<int>(newPos.x), 0, static_cast<int>(imgSize.x - 1));
        unsigned y = std::clamp(static_cast<int>(newPos.y), 0, static_cast<int>(imgSize.y - 1));
        sf::Color pixel = trackImage.getPixel({x, y});

        if (pixel != sf::Color::White) {
            cars.velocity[i] = -0.5f * cars.velocity[i];
            newPos = cars.position[i] + cars.velocity[i] * dt;
        }

        cars.position[i] = newPos;
    }
}

