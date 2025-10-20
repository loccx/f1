#include "map.hpp"

bool TileMap::load(const std::vector<int>& data, unsigned int w, unsigned int h, sf::Vector2u tileSize) {
    m_width = w;
    m_height = h;
    m_tileSize = tileSize;

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(m_width * m_height * 6);

    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            sf::Vertex* quad = &m_vertices[(x + y * m_width) * 6];

            float left   = static_cast<float>(x * m_tileSize.x);
            float top    = static_cast<float>(y * m_tileSize.y);
            float right  = left + m_tileSize.x;
            float bottom = top + m_tileSize.y;

            quad[0].position = {left,  top};
            quad[1].position = {right, top};
            quad[2].position = {left,  bottom};
            quad[3].position = {left,  bottom};
            quad[4].position = {right, top};
            quad[5].position = {right, bottom};

            int tile = data[x + y * m_width];
            sf::Color color = (tile == 1) ? sf::Color::White : sf::Color(60, 60, 60);
            for (int i = 0; i < 6; ++i)
                quad[i].color = color;
        }
    }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_vertices, states);
}

