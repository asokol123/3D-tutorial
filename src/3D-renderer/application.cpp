#include "application.h"

namespace NRenderer {

TApplication::TApplication(const std::string& title, int32_t width, int32_t height)
    : Window_(sf::VideoMode(width, height), title), Renderer_(width, height), Controller_(Renderer_.GetCamera()) {
    Window_.clear(sf::Color::Black);
    Window_.display();
}

auto TApplication::IsOpen() const -> bool {
    return Window_.isOpen();
}

void TApplication::Close() {
    Window_.close();
}

void TApplication::Load(const std::string& filename) {
    NParser::LoadFile(filename, World_);
}

void TApplication::Redraw() {
    Window_.clear(sf::Color::Black);
    for (const auto& object : World_) {
        Renderer_.Add(*object);
    }
    Renderer_.Flush(Window_);
    Window_.display();
}

void TApplication::Run() {
    while (true) {  // according to docs we don't check IsOpen every time
        sf::Event event = {};
        if (!Window_.pollEvent(event)) {
            continue;
        }
        if (event.type == sf::Event::EventType::Closed) {
            Close();
            return;
        }
        Controller_.Handle();
        Redraw();
    }
}

}  // namespace NRenderer
