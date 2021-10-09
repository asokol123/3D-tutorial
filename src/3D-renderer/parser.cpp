#include "parser.h"
#include "cube.h"

#include <nlohmann/json.hpp>
#include <array>
#include <fstream>

namespace NParser {

namespace {

auto GetColor(std::string_view color) -> sf::Color {
    if (color == "black") {
        return sf::Color::Black;
    }
    if (color == "white") {
        return sf::Color::White;
    }
    if (color == "red") {
        return sf::Color::Red;
    }
    if (color == "green") {
        return sf::Color::Green;
    }
    if (color == "blue") {
        return sf::Color::Blue;
    }
    if (color == "yellow") {
        return sf::Color::Yellow;
    }
    if (color == "magenta") {
        return sf::Color::Magenta;
    }
    if (color == "cyan") {
        return sf::Color::Cyan;
    }
    throw std::invalid_argument("Unknown color" + std::string(color));
}

// use this structure to parse points from json
struct TPoint {
    double x;
    double y;
    double z;
};
void from_json(const nlohmann::json& nlohmann_json_j, TPoint& nlohmann_json_t) {
    NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, x, y, z))
}

auto PointTo3d(TPoint p) -> NRenderer::TPoint3d {
    return {p.x, p.y, p.z};
}

auto ParseCube(const nlohmann::json& json) -> NWorld::TCube {
    auto colorNames = json.at("colors").get<std::vector<std::string_view>>();
    if (colorNames.empty()) {
        throw std::invalid_argument("Expected at least one color");
    }

    std::array<sf::Color, NWorld::TCube::COUNT_COLORS> colors;
    for (int i = 0; i < NWorld::TCube::COUNT_COLORS; ++i) {
        colors[i] = GetColor(colorNames[i % colorNames.size()]);
    }
    std::vector<TPoint> points;
    json.at("points").get_to(points);
    if (points.size() != 4) {
        throw std::invalid_argument("Expected 4 points for cube, found " + std::to_string(points.size()));
    }
    NWorld::TCube cube(PointTo3d(points[0]), PointTo3d(points[1]), PointTo3d(points[2]), PointTo3d(points[3]), colors);
    return cube;
}

}  // namespace

void LoadFile(const std::string& filename, NWorld::TWorld& world) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::invalid_argument("Failed to open file " + filename);
    }
    nlohmann::json content;
    ifs >> content;
    if (!content.is_array()) {
        throw std::invalid_argument("Expected json array");
    }
    for (const auto& elem : content) {
        if (!elem.is_object()) {
            throw std::invalid_argument("Expected json object");
        }
        auto type = elem.at("type").get<std::string>();
        if (type == "cube") {
            world.Add(ParseCube(elem));
        } else {
            throw std::invalid_argument("Unsupported type " + type);
        }
    }
}

}  // namespace NParser
