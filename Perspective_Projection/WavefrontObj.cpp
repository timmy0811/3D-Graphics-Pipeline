#include "WavefrontObj.h"

WavefrontObj::~WavefrontObj()
{
    Mesh::~Mesh();
}

const bool WavefrontObj::loadFromFile(char* path)
{
    std::ifstream objFile(path);
    std::string line;

    // Open file
    if (objFile.is_open()) {
        while (std::getline(objFile, line))
            switch (line[0]) {
            // Ignore comments
            case '#': {
                continue;
                break;
            }
            // Name of object
            case 'o': {
                for (int i = 2; i < line.length(); i++) {
                    this->name_ += line[i];
                }
                break;
            }
            // vectors
            case 'v': {
                switch (line[1]) {
                // Edge points
                case ' ': {
                    std::string val;
                    int i = 2;
                    // x
                    while (line[i] != ' ') {
                        val += line[i];
                        i++;
                    }
                    float x = std::stof(val);
                    val.clear();

                    // y
                    i++;
                    while (line[i] != ' ') {
                        val += line[i];
                        i++;
                    }
                    float y = std::stof(val);
                    val.clear();

                    // z
                    i++;
                    while (i < line.length()) {
                        val += line[i];
                        i++;
                    }
                    float z = std::stof(val);
                    val.clear();

                    points.push_back(new Point({ x, -y, z }, "point_" + points.size()));
                    break;
                }
                // Texture points
                case 't': {

                    break;
                }
                // Normals
                case 'n': {

                    break;
                }
                default: {
                    continue;
                    break;
                }
                }
                break;
            }
            // Material
            case 'u': {
                for (int i = 2; i < line.length(); i++) {
                    this->material += line[i];
                }
                break;
            }
            // Smoothing
            case 's': {
                break;
            }
            // Attribute assigning
            case 'f': {
                // Get point index of every column
                unsigned int p[4]{};
                int col = 0;
                std::string val;
                bool readsNumber = false;

                for (int ch = 2; ch < line.length(); ch++) {
                    if (readsNumber) {
                        if (line[ch] == '/') {
                            p[col] = std::stoi(val);
                            col++;
                            readsNumber = false;
                            val = "";
                            continue;
                        }
                        else {
                            val += line[ch];
                        }
                    }

                    if (line[ch - 1] == ' ') {
                        val += line[ch];
                        readsNumber = true;
                    }
                }

                // Check if polygons are triangles or else
                if (col == 3) {
                    polys.push_back(new Triangle(points[p[0] - 1], points[p[1] - 1], points[p[2] - 1], sf::Color(rand() % 255, rand() % 255, rand() % 255, 255.f), name_ + "triangle_" + std::to_string(polys.size())));
                }
                else if (col == 4) {
                    polys.push_back(new Triangle(points[p[0] - 1], points[p[1] - 1], points[p[2] - 1], sf::Color(rand() % 255, rand() % 255, rand() % 255, 255.f), name_ + "triangle_"));
                    polys.push_back(new Triangle(points[p[0] - 1], points[p[2] - 1], points[p[3] - 1], sf::Color(rand() % 255, rand() % 255, rand() % 255, 255.f), name_ + "triangle_"));
                }

                break;
            }
            }

        objFile.close();
    }
    return false;
}

void WavefrontObj::connect(sf::RenderTarget* target)
{
}
