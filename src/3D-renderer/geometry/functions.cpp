#include "io.h"
#include "geometry/functions.h"
#include <glog/logging.h>

namespace NRenderer::NGeometry {

namespace {

auto Intersect(TPoint4d from, TPoint4d to, double z) -> TPoint4d {
    auto factor = (to.z() - from.z()) / (z - from.z());
    return Normalize(from + (to - from) * factor);
}

enum class ESide {
    E_LESS,
    E_GREATER,
};

auto ClipByPlane(const TTriangle4d& triangle, double minZ, ESide clippingSide) -> std::vector<TTriangle4d> {
    auto [a, b, c] = triangle.GetPoints();
    auto color = triangle.Color();
    bool aClipped = a.z() < minZ;
    bool bClipped = b.z() < minZ;
    bool cClipped = c.z() < minZ;
    if (clippingSide == ESide::E_GREATER) {
        aClipped = !aClipped;
        bClipped = !bClipped;
        cClipped = !cClipped;
    }

    if (aClipped) {
        if (bClipped) {
            if (cClipped) {
                return {};
            } else {
                return {{Intersect(c, a, minZ), Intersect(c, b, minZ), c, color}};
            }
        } else {
            if (cClipped) {
                return {{Intersect(b, a, minZ), b, Intersect(b, c, minZ), color}};
            } else {
                auto intBA = Intersect(b, a, minZ);
                auto intCA = Intersect(c, a, minZ);
                return {
                    {intCA, b, c, color},
                    {intBA, b, intCA, color},
                };
            }
        }
    } else {
        if (bClipped) {
            if (cClipped) {
                return {{a, Intersect(a, b, minZ), Intersect(a, c, minZ), color}};
            } else {
                auto intAB = Intersect(a, b, minZ);
                auto intCB = Intersect(c, b, minZ);
                return {
                    {a, intCB, c, color},
                    {a, intAB, intCB, color},
                };
            }
        } else {
            if (cClipped) {
                auto intAC = Intersect(a, c, minZ);
                auto intBC = Intersect(b, c, minZ);
                return {
                    {a, b, intBC, color},
                    {a, intBC, intAC, color},
                };
            } else {
                return {triangle};
            }
        }
    }
}

}  // namespace

auto Clip(const TTriangle4d& triangle) -> std::vector<TTriangle4d> {
    auto [minZ, maxZ] = TCamera::GetClippingDistances();
    LOG(INFO) << "Clipping triangle " << triangle;
    auto trianglesClippedByMin = ClipByPlane(triangle, minZ, ESide::E_LESS);
    LOG(INFO) << "After clipping by min: " << trianglesClippedByMin.size();

    std::vector<TTriangle4d> trianglesClipped;
    for (const auto& triangle : trianglesClippedByMin) {
        // we could use insert to end, but here we are moving triangles insted of copying
        LOG(INFO) << "Clipping by max: " << triangle << ", maxZ: " << maxZ;
        for (const auto& clipped : ClipByPlane(triangle, maxZ, ESide::E_GREATER)) {
            trianglesClipped.push_back(clipped);
        }
    }
    return trianglesClipped;
}

auto GetZOnPlane(const TTriangle4d& plane, double x, double y) -> double {
    using Vector2d = Eigen::Vector2d;

    auto [a, b, c] = plane.GetPoints();
    double la = Vector2d{a.x() - x, a.y() - y}.norm();
    double lb = Vector2d{b.x() - x, b.y() - y}.norm();
    double lc = Vector2d{c.x() - x, c.y() - y}.norm();

    return (a.z() * la + b.z() * lb + c.z() * lc) / (la + lb + lc);
}

}  // namespace NRenderer::NGeometry
