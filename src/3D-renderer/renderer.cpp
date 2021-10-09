#include "io.h"
#include "renderer.h"
#include "geometry/objects.h"
#include "geometry/functions.h"

#include <glog/logging.h>
#include <cmath>

namespace NRenderer {

void TRenderer::Flush(sf::RenderWindow& window) {
    window.draw(Screen_.Picture());
    Screen_.Clear();
    ZBuffer_.clear();
}

auto TRenderer::GetCamera() -> TCamera& {
    return Camera_;
}

auto TRenderer::GetCamera() const -> const TCamera& {
    return Camera_;
}

void TRenderer::Add(const NWorld::IObject& object) {
    for (const auto& triangle : object.GetTriangles()) {
        Add(Triangle3dTo4d(triangle));
    }
}

void TRenderer::Add(TTriangle4d triangle) {
    LOG(INFO) << "Adding triangle " << triangle;
    triangle = Camera_.ToCamera(triangle);
    auto clipped = NGeometry::Clip(triangle);
    LOG(INFO) << "Count after clipping: " << clipped.size();
    for (auto&& triangle : clipped) {
        LOG(INFO) << "Adding clipped triangle " << triangle;
        DrawOnScreen(triangle);
    }
}

void TRenderer::DrawOnScreen(const TTriangle4d& triangle) {
    auto triangleOnScreen = Camera_.ToScreen(triangle);

    auto [widthD, heightD] = Screen_.Size();
    int width = std::floor(widthD);
    int height = std::floor(heightD);

    // we have to sort points by x to get minimum and maximum y for each x
    std::vector<TPoint4d> points;
    {
        auto [a, b, c] = triangleOnScreen.GetPoints();
        points = {a, b, c};
        std::sort(points.begin(), points.end(), [](TPoint4d left, TPoint4d right) { return left.x() < right.x(); });
    }
    TPoint4d a = NGeometry::Normalize(points[0]);
    TPoint4d b = NGeometry::Normalize(points[1]);
    TPoint4d c = NGeometry::Normalize(points[2]);

    auto GetMinMaxY = [&](double x) -> std::pair<double, double> {
        double y1 = 0;
        if (x < b.x()) {
            y1 = a.y() + (b.y() - a.y()) * (x - a.x()) / (b.x() - a.x());
        } else {
            y1 = c.y() + (b.y() - c.y()) * (x - c.x()) / (b.x() - c.x());
        }
        double y2 = a.y() + (c.y() - a.y()) * (x - a.x()) / (c.x() - a.x());
        if (y1 > y2) {
            std::swap(y1, y2);
        }
        return {y1, y2};
    };

    int minX = std::ceil(a.x());
    int maxX = std::floor(c.x());
    minX = std::max(0, minX);
    maxX = std::min(maxX, width - 1);

    LOG(INFO) << "Drawing " << TTriangle4d{a, b, c, triangle.Color()};

    for (int x = minX; x <= maxX; ++x) {
        auto [yminD, ymaxD] = GetMinMaxY(x);
        int ymin = std::ceil(yminD);
        int ymax = std::floor(ymaxD);
        ymin = std::max(ymin, 0);
        ymax = std::min(ymax, height - 1);
        for (int y = ymin; y <= ymax; ++y) {
            auto z = NGeometry::GetZOnPlane(triangle, x, y);
            double& currZ = ZBuffer_(x, y);
            if (z < currZ) {
                currZ = z;
                Screen_(x, y) = sf::Vertex(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), triangle.Color());
            }
        }
    }
}

}  // namespace NRenderer
