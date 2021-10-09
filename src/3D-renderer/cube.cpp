#include "cube.h"

namespace NWorld {

TCube::TCube(NRenderer::TPoint3d a, NRenderer::TPoint3d b, NRenderer::TPoint3d c, NRenderer::TPoint3d d, std::array<sf::Color, COUNT_COLORS> colors)
    : A_(std::move(a)), B_(std::move(b)), D_(std::move(c)), E_(std::move(d)), Colors_(colors) {
    C_ = B_ + D_ - A_;
    F_ = B_ + E_ - A_;
    G_ = C_ + E_ - A_;
    H_ = D_ + E_ - A_;
}

auto TCube::GetTriangles() const -> std::vector<NRenderer::TTriangle3d> {
    return {
        {A_, B_, C_, Colors_[0]}, {A_, C_, D_, Colors_[1]},  {A_, B_, F_, Colors_[2]},
        {A_, F_, E_, Colors_[3]}, {A_, D_, H_, Colors_[4]},  {A_, H_, E_, Colors_[5]},

        {E_, F_, G_, Colors_[6]}, {E_, G_, H_, Colors_[7]},  {B_, C_, G_, Colors_[8]},
        {B_, G_, F_, Colors_[9]}, {C_, D_, H_, Colors_[10]}, {C_, H_, G_, Colors_[11]},
    };
}

}  // namespace NWorld
