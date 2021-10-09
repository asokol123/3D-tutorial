#include "geometry/objects.h"
#include <cmath>

namespace NRenderer {

namespace NGeometry {

auto Normalize(TPoint4d p) -> TPoint4d {
    auto w = p.w();
    p.x() /= w;
    p.y() /= w;
    p.z() /= w;
    p.w() = 1;
    return p;
}

}  // namespace NGeometry

auto Triangle3dTo4d(const TTriangle3d& triangle) -> TTriangle4d {
    auto [a, b, c] = triangle.GetPoints();
    return {
        Point3dTo4d(a),
        Point3dTo4d(b),
        Point3dTo4d(c),
        triangle.Color(),
    };
}

auto Point3dTo4d(TPoint3d point) -> TPoint4d {
    return {point.x(), point.y(), point.z(), 1};
}

}  // namespace NRenderer
