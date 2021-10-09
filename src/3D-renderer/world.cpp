#include "world.h"

namespace NWorld {

void TWorld::Add(Object object) {
    Objects_.push_back(std::move(object));
}

auto TWorld::Begin() -> iterator {
    return Objects_.begin();
}

auto TWorld::Begin() const -> const_iterator {
    return Objects_.begin();
}

auto TWorld::begin() -> iterator {
    return Objects_.begin();
}

auto TWorld::begin() const -> const_iterator {
    return Objects_.begin();
}

auto TWorld::End() -> iterator {
    return Objects_.end();
}

auto TWorld::End() const -> const_iterator {
    return Objects_.end();
}

auto TWorld::end() -> iterator {
    return Objects_.end();
}

auto TWorld::end() const -> const_iterator {
    return Objects_.end();
}

}  // namespace NWorld
