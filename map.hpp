#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    // Returns true if loaded successfully
    bool load(const std::vector<int>& data, unsigned int w, unsigned int h, sf::Vector2u tileSize);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_vertices;
    unsigned int m_width{}, m_height{};
    sf::Vector2u m_tileSize;
};

