#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "map.hpp"
#include "physics.hpp"
#include "input.hpp"
#include "render.hpp"

int main() {
    const unsigned windowWidth = 1600;
    const unsigned windowHeight = 1200;
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "monaco");
    window.setFramerateLimit(60);

    const std::string filename = "../monaco_track2.txt";
    std::ifstream file(filename);
    if (!file) { std::cerr << "failed to open " << filename << '\n'; return 1; }

    unsigned width, height;
    file >> width >> height;
    std::vector<int> mapData(width * height);
    for (unsigned i = 0; i < width * height; ++i) file >> mapData[i];

    TileMap map;
    map.load(mapData, width, height, {32, 32});

    sf::Texture carTexture;
    if (!carTexture.loadFromFile("../car1.png")) { std::cerr << "failed to load ../car1.png\n"; return 1; }

    Cars cars;
    cars.position.push_back({4000.f, 3000.f});
    cars.rotation.push_back(0.f);
    cars.velocity.push_back({0.f, 0.f});

    sf::View camera(sf::FloatRect({0.f, 0.f}, {static_cast<float>(windowWidth), static_cast<float>(windowHeight)}));
    float cam_rotate = 0.f;
    float cam_lag = 0.05f;

    sf::Clock clock;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        std::vector<InputState> inputs(1);
        inputs[0] = getCarInput();
        updateInput(inputs);
        updateCarsPhysics(cars, inputs, dt);

        camera.setCenter(cars.position[0]);

        float diff = cars.rotation[0] - cam_rotate;
        while (diff > 3.14159265f) diff -= 2.f * 3.14159265f;
        while (diff < -3.14159265f) diff += 2.f * 3.14159265f;
        cam_rotate += diff * cam_lag;

        float angleDeg = cam_rotate * 180.f / 3.14159265f;
        camera.setRotation(sf::degrees(angleDeg));

        window.setView(camera);
        window.clear(sf::Color::Black);
        window.draw(map);
        renderCars(window, cars, carTexture);
        window.display();
    }
    return 0;
}

