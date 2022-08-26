#include "WavefrontObj.h"

WavefrontObj::~WavefrontObj()
{
    Mesh::~Mesh();
}

const bool WavefrontObj::loadFromFile(char* path, Texture* texture)
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
                    std::string val;
                    int i = 3;
                    // x
                    while (line[i] != ' ') {
                        val += line[i];
                        i++;
                    }
                    float x = std::stof(val);
                    val.clear();

                    // y
                    i++;
                    while (i < line.length()) {
                        val += line[i];
                        i++;
                    }
                    float y = std::stof(val);
                    val.clear();

                    vt.push_back({ x, y });
                    
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
            // File
            case 'm': {
                break;
            }
            // Attribute assigning
            case 'f': {
                // Get point index of every column
                unsigned int p[4]{};
                unsigned int pt[4]{};

                int col = 0;
                std::string val;
                bool readsVert = false;
                bool readsCoord = false;

                for (int ch = 2; ch < line.length(); ch++) {            // f    1/1/1  5/2/1   7/3/1    3/4/1
                    if (readsVert || readsCoord) {
                        if (line[ch] == '/') {
                            // Writes vertex position
                            if (readsVert) {
                                p[col] = std::stoi(val);
                                val = "";
                            }
                            // Writes texture position
                            if (readsCoord) {
                                pt[col] = std::stoi(val);
                                val = "";
                            }

                            if (readsCoord && !readsVert) {
                                readsCoord = false;
                                col++;
                                continue;
                            }

                            readsVert = false;
                            readsCoord = true;

                            continue;
                        }
                        else {
                            val += line[ch];
                        }
                    }

                    if (line[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(ch) - 1] == ' ') {
                        val += line[ch];
                        readsVert = true;
                    }

                }
                if (texture) {
                    this->texture = texture;
                }

                // Check if polygons are triangles or else
                if (col == 3) {
                    if (texture) {
                        //polys.push_back(new Triangle(points[p[0] - 1], points[p[1] - 1], points[p[2] - 1], texture, name_ + "triangle_" + std::to_string(polys.size()), vt[pt[0] - 1], vt[pt[1] - 1], vt[pt[2] - 1]));
                        polys.push_back(new Triangle(points[p[0] - 1], points[p[1] - 1], points[p[2] - 1], texture, name_ + "triangle_" + std::to_string(polys.size()), {0.f, 0.f}, {1.f, 0.f}, {1.f, 1.f}));
                    }
                    else {
                        polys.push_back(new Triangle(points[p[0] - 1], points[p[1] - 1], points[p[2] - 1], sf::Color(rand() % 255, rand() % 255, rand() % 255, 255.f), name_ + "triangle_" + std::to_string(polys.size())));
                    }
                }
                else if (col == 4) {
                    if (texture) {
                        /*polys.push_back(new Triangle(points[p[0] - 1], points[p[1] - 1], points[p[2] - 1], texture, name_ + "triangle_" + std::to_string(polys.size()), vt[pt[0] - 1], vt[pt[1] - 1], vt[pt[2] - 1]));
                        polys.push_back(new Triangle(points[p[0] - 1], points[p[2] - 1], points[p[3] - 1], texture, name_ + "triangle_" + std::to_string(polys.size()), vt[pt[0] - 1], vt[pt[2] - 1], vt[pt[3] - 1]));*/


                        polys.push_back(new Triangle(points[p[0] - 1], points[p[1] - 1], points[p[2] - 1], texture, name_ + "triangle_" + std::to_string(polys.size()), { 0.f, 0.f }, { 1.f, 0.f }, { 1.f, 1.f }));
                        polys.push_back(new Triangle(points[p[0] - 1], points[p[2] - 1], points[p[3] - 1], texture, name_ + "triangle_" + std::to_string(polys.size()), { 0.f, 0.f }, { 1.f, 0.f }, { 1.f, 1.f }));
                    }
                    else {
                        polys.push_back(new Triangle(points[p[0] - 1], points[p[1] - 1], points[p[2] - 1], sf::Color(rand() % 255, rand() % 255, rand() % 255, 255.f), name_ + "triangle_"));
                        polys.push_back(new Triangle(points[p[0] - 1], points[p[2] - 1], points[p[3] - 1], sf::Color(rand() % 255, rand() % 255, rand() % 255, 255.f), name_ + "triangle_"));
                    }
                }

                break;
            }
            }

        objFile.close();
        return true;
    }
    return false;
}

void WavefrontObj::connect(sf::RenderTarget* target)
{
}
