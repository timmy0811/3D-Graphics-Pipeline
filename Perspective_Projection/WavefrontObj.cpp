#include "WavefrontObj.h"

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

                    points.push_back(new Point({ x, y, z }, "point_" + points.size()));
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
