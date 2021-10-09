#include "controls.h"

namespace NWorld {

TController::TController(NRenderer::TCamera& camera) : Camera_(camera) {
    Handlers_ = {{sf::Keyboard::Left, [this]() {
                Camera_.Move({-1, 0, 0, 0}); }},  {sf::Keyboard::Right, [this]() {
                Camera_.Move({1, 0, 0, 0}); }},
                 {sf::Keyboard::Up, [this]() {
                Camera_.Move({0, 0, 1, 0}); }},     {sf::Keyboard::Down, [this]() {
                Camera_.Move({0, 0, -1, 0}); }},
                 {sf::Keyboard::Space, [this]() {
               Camera_.Move({0, -1, 0, 0}); }}, {sf::Keyboard::LControl, [this]() {
                                          Camera_.Move({0, 1, 0, 0}); }}};
}

void TController::Handle() {
    for (const auto& [key, func] : Handlers_) {
        if (sf::Keyboard::isKeyPressed(key)) {
            func();
        }
    }
}

}  // namespace NWorld
