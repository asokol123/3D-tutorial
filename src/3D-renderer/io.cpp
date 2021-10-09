#include "io.h"

auto operator<<(std::ostream& out, const NRenderer::TTriangle4d& triangle) -> std::ostream& {
    out << "Triangle4d{\n";
    auto [a, b, c] = triangle.GetPoints();
    out << "    " << a << "\n";
    out << "    " << b << "\n";
    out << "    " << c << "\n";
    out << "}";
    return out;
}

auto operator<<(std::ostream& out, const NRenderer::TPoint4d& point) -> std::ostream& {
    out << "Point4d{x: " << point.x() << ", y: " << point.y() << ", z: " << point.z() << ", w: " << point.w() << "}";
    return out;
}
