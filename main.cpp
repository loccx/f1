#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "map.hpp"
#include "physics.hpp"
#include "input.hpp"
#include "render.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1000u, 600u}), "monaco");
    window.setFramerateLimit(60);

    //tile map
    const std::string filename = "../monaco_track.txt";
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

    //load cars
    Cars cars;
    cars.position.push_back({3200.f, 2400.f});
    cars.rotation.push_back(0.f);
    cars.velocity.push_back({0.f, 0.f});

    sf::View camera(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));

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
        updateCarsPhysics(cars, inputs, dt);

        camera.setCenter(cars.position[0]);
        window.setView(camera);

        //render
        window.clear(sf::Color::Black);
        window.draw(map);
        renderCars(window, cars, carTexture);
        window.display();
    }
    return 0;
}

