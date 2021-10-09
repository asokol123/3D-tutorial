#include "zbuffer.h"

#include <glog/logging.h>

namespace NRenderer {

TZBuffer::TZBuffer(int64_t width, int64_t height) : ZCoords_(width, height, std::numeric_limits<double>::infinity()), Width_(width), Height_(height) {
}

auto TZBuffer::operator()(int64_t col, int64_t row) -> double& {
    assert(0 <= row && row < Height_ && 0 <= col && col < Width_);
    return ZCoords_[col][row];
}

auto TZBuffer::operator()(int64_t col, int64_t row) const -> double {
    assert(0 <= row && row < Height_ && 0 <= col && col < Width_);
    return ZCoords_[col][row];
}

void TZBuffer::clear() {
    std::fill(ZCoords_.Begin(), ZCoords_.End(), std::numeric_limits<double>::infinity());
}

auto TZBuffer::size() const -> TScreenSize {
    return {Width_, Height_};
}

}  // namespace NRenderer
