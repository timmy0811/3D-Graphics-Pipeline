
#include <vector>
#include "../../miscellaneous/matrix/Matrix3X1.h"

struct MeshComponent {
	std::vector<uint32_t> polygons{};
	std::vector<uint32_t> points{};
	Matrix3X1 center{};
	bool isWireframe = false;
};