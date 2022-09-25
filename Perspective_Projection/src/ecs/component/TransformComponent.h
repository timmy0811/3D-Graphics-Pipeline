
#include "../../miscellaneous/matrix/Matrix3X1.h"

struct TransformComponent {
	Matrix3X1 position{};
	Matrix3X1 rotation{};
	Matrix3X1 scale{};
};