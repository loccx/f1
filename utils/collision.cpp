#include "collision.hpp"

sf::Image generateCollisionImage(const std::vector<int>& mapData, unsigned width, unsigned height, unsigned tileSize) {
    sf::Image img;
    img.resize({width * tileSize, height * tileSize}, sf::Color::Black);

    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            sf::Color color = (mapData[y * width + x] == 0) ? sf::Color(128,128,128) : sf::Color::White;

            for (unsigned ty = 0; ty < tileSize; ++ty) {
                for (unsigned tx = 0; tx < tileSize; ++tx) {
                    img.setPixel({x * tileSize + tx, y * tileSize + ty}, color);
                }
            }
        }
    }
    return img;
}

