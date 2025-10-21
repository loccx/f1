// physics.cpp
#include "physics.hpp"
#include <cmath>
#include <algorithm>

void updateCarsPhysics(Cars& cars, const std::vector<InputState>& inputs, float dt) {
    const float maxForwardSpeed = 1200.f;
    const float maxBackwardSpeed = 600.f;
    const float acceleration = 600.f;
    const float friction = 400.f;
    const float lateralFriction = 0.7f;
    const float turnSpeed = 3.5f;

    size_t N = cars.position.size();
    for (size_t i = 0; i < N; ++i) {
        sf::Vector2f forward{std::cos(cars.rotation[i]), std::sin(cars.rotation[i])};
        sf::Vector2f right{-forward.y, forward.x};

        // accel / decel
        if (inputs[i].accelerate)
            cars.velocity[i] += forward * acceleration * dt;
        if (inputs[i].brake)
            cars.velocity[i] -= forward * acceleration * dt;

        //x y velocity
        float forwardVel = cars.velocity[i].x * forward.x + cars.velocity[i].y * forward.y;
        float lateralVel = cars.velocity[i].x * right.x + cars.velocity[i].y * right.y;

        // friction
        forwardVel -= friction * dt * (forwardVel > 0 ? 1.f : -1.f);
        if (std::abs(forwardVel) < 1.f) forwardVel = 0.f;

        // mukltiplier based on acceleration
        float driftFactor = (inputs[i].accelerate && (inputs[i].turnLeft || inputs[i].turnRight)) ? 0.3f : lateralFriction;
        lateralVel *= driftFactor;

        forwardVel = std::clamp(forwardVel, -maxBackwardSpeed, maxForwardSpeed);

        cars.velocity[i] = forward * forwardVel + right * lateralVel;

        float speedFactor = std::min(std::abs(forwardVel) / maxForwardSpeed, 1.f);
        float turnAmount = turnSpeed * dt * speedFactor;
        if (inputs[i].turnLeft)  cars.rotation[i] -= turnAmount;
        if (inputs[i].turnRight) cars.rotation[i] += turnAmount;

        // update!
        cars.position[i] += cars.velocity[i] * dt;
    }
}

