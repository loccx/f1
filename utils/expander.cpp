#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "failed to open input file.\n";
        return 1;
    }

    int width, height;
    infile >> width >> height;
    infile.ignore(); // skip rest of the line

    std::vector<std::vector<int>> grid(height, std::vector<int>(width));

    for (int i = 0; i < height; ++i) {
        std::string line;
        std::getline(infile, line);
        std::istringstream ss(line);
        for (int j = 0; j < width; ++j) {
            ss >> grid[i][j];
        }
    }

    infile.close();

    int newWidth = width * 2;
    int newHeight = height * 2;
    std::ofstream outfile(argv[2]);
    if (!outfile) {
        std::cerr << "failed to open output file.\n";
        return 1;
    }

    outfile << newWidth << " " << newHeight << "\n";

    //double it
    for (int i = 0; i < height; ++i) {
        for (int repeatRow = 0; repeatRow < 2; ++repeatRow) {
            for (int j = 0; j < width; ++j) {
                outfile << grid[i][j] << " " << grid[i][j] << " ";
            }
            outfile << "\n";
        }
    }

    outfile.close();
    return 0;
}

