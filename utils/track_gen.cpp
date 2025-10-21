#include <fstream>
#include <vector>
#include <cmath>

int main() {
    const unsigned width = 200, height = 150;
    std::vector<int> map(width * height, 0);

    //s track, boilerplate
    for (unsigned y = 20; y < height - 20; ++y) {
        double centerX = 100 + 40 * std::sin(y * 0.05);
        for (unsigned x = 0; x < width; ++x) {
            double dist = std::abs((double)x - centerX);
            if (dist < 4) map[y * width + x] = 1;          // main road
            else if (dist < 5) map[y * width + x] = 2;     // barrier edge
        }
    }

    std::ofstream out("../monaco_track.txt");
    out << width << " " << height << "\n";
    for (unsigned i = 0; i < width * height; ++i) {
        out << map[i] << (i % width == width - 1 ? "\n" : " ");
    }
}

