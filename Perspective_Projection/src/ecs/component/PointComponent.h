
#include "../../miscellaneous/matrix/Matrix3X1.h"

struct PointComponent {
	Matrix3X1 projected{};
	float w = 1.f;
	float wProj;
};