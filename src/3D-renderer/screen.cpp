#include "screen.h"

#include <glog/logging.h>

namespace NRenderer {

TScreen::TScreen(int64_t width, int64_t height) : Data_(width, height), Width_(width), Height_(height) {
}

auto TScreen::operator()(int64_t col, int64_t row) -> sf::Vertex& {
    assert(row < Height_ && col < Width_);
    return Data_[col][row];
}

auto TScreen::operator()(int64_t col, int64_t row) const -> const sf::Vertex& {
    assert(row < Height_ && col < Width_);
    return Data_[col][row];
}

void TScreen::Clear(sf::Vertex value) {
    std::fill(Data_.Begin(), Data_.End(), value);
}

auto TScreen::Size() const -> TScreenSize {
    return {Width_, Height_};
}

auto TScreen::Picture() const -> sf::VertexBuffer {
    sf::VertexBuffer result;
    if (!result.create(Width_ * Height_)) {
        throw std::runtime_error("Failed to allocate graphic memory for VertexBuffer");
    }

    result.update(Data_.Data());
    return result;
}

}  // namespace NRenderer
