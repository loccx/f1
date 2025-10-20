#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include "map.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1400u, 1000u}), "map");

    // test file to map nums
    const std::string filename = "../track2.txt"; //back dir, since run from build directory
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "failed to open " << filename << '\n';
        return 1;
    }

    std::string line;
    unsigned int width = 0, height = 0;
    file >> width >> height; // width first, height second
    std::vector<int> mapdata(width * height);
    for (unsigned int i = 0; i < width * height; i++) {
        file >> mapdata[i];
    }

    TileMap map;
    map.load(mapdata, width, height, {32, 32});

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}

