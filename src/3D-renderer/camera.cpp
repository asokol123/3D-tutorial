#include "camera.h"

namespace NRenderer {

TCamera::TCamera(double screenWidth, double screenHeight) : Width_(screenWidth), Height_(screenHeight) {
    InitTransformations();
}

auto TCamera::ToCamera(const TPoint4d& point) const -> TPoint4d {
    return NGeometry::Normalize(TransformToCamera_ * point);
}

auto TCamera::ToCamera(const TTriangle4d& triangle) const -> TTriangle4d {
    auto [a, b, c] = triangle.GetPoints();
    return {ToCamera(a), ToCamera(b), ToCamera(c), triangle.Color()};
}

auto TCamera::ToScreen(const TPoint4d& point) const -> TPoint4d {
    return NGeometry::Normalize(TransformToScreen_ * point);
}

auto TCamera::ToScreen(const TTriangle4d& triangle) const -> TTriangle4d {
    auto [a, b, c] = triangle.GetPoints();
    return TTriangle4d{ToScreen(a), ToScreen(b), ToScreen(c), triangle.Color()};
}

void TCamera::Rotate(const TMatrix4d& matrix) {
    Rotation_ *= matrix;
    InitTransformations();
}

void TCamera::Move(const TVector4d& direction) {
    Focus_ += direction;
    InitTransformations();
}

auto TCamera::GetClippingDistances() -> TClippingDistances {
    static constexpr double MIN_CLIPPING = 1;
    static constexpr double MAX_CLIPPING = 10000;
    return {MIN_CLIPPING, MAX_CLIPPING};
}

void TCamera::InitTransformations() {
    TMatrix4d canonical_to_screen{
        {Width_ / 2, 0, 0, Width_ / 2 - 0.5},
        {0, Height_ / 2, 0, Height_ / 2 - 0.5},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
    TMatrix4d rect_to_canonical{
        {2.0 / (RIGHT_POINT.x() - LEFT_POINT.x()), 0, 0, 0},
        {0, 2.0 / (RIGHT_POINT.y() - LEFT_POINT.y()), 0, 0},
        {0, 0, 2.0 / (RIGHT_POINT.z() - LEFT_POINT.z()), 0},
        {0, 0, 0, 1},
    };
    TMatrix4d move_to_center{
        {1, 0, 0, -(LEFT_POINT.x() + RIGHT_POINT.x()) / 2.0},
        {0, 1, 0, -(LEFT_POINT.y() + RIGHT_POINT.y()) / 2.0},
        {0, 0, 1, -(LEFT_POINT.z() + RIGHT_POINT.z()) / 2.0},
        {0, 0, 0, 1},
    };
    TMatrix4d projective_transform{
        {LEFT_POINT.z(), 0, 0, 0},
        {0, LEFT_POINT.z(), 0, 0},
        {0, 0, LEFT_POINT.z() + RIGHT_POINT.z(), LEFT_POINT.z() * RIGHT_POINT.z()},
        {0, 0, 1, 0},
    };
    TMatrix4d move_camera{
        {1, 0, 0, -Focus_.x() / Focus_.w()},
        {0, 1, 0, -Focus_.y() / Focus_.w()},
        {0, 0, 1, -Focus_.z() / Focus_.w()},
        {0, 0, 0, 1},
    };
    TransformToScreen_ = canonical_to_screen * rect_to_canonical * move_to_center * projective_transform;
    TransformToCamera_ = Rotation_.transpose() * move_camera;
}

const TPoint4d TCamera::LEFT_POINT = {-200, -200, 400, 1};
const TPoint4d TCamera::RIGHT_POINT = {200, 200, 5000, 1};

}  // namespace NRenderer
