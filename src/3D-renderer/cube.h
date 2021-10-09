#pragma once

#include "object.h"
#include <nlohmann/json.hpp>
#include <utility>

namespace NWorld {

/*!
  \brief Куб в пространстве с цветами

  Цветов 12 чтобы показать что реально каждая грань разбивается на 2 треугольника и все - треугольники
*/
class TCube : public IObject {
 public:
    /*!
      \brief Количество цветов на куб

      Константв сколько цветов нужно кубу
    */
    static constexpr int COUNT_COLORS = 12;

    /*!
      \brief Создает куб по базе и цветам

      Создает куб по четырем базовым вершинам и цветам
      Если базис не образует куб, поведение неопределено
    */
    TCube(NRenderer::TPoint3d a, NRenderer::TPoint3d b, NRenderer::TPoint3d c, NRenderer::TPoint3d d, std::array<sf::Color, COUNT_COLORS> colors);

    /*!
      \brief Возвращает все треугольники куба

      Возвращает разбиение куба на треугольники
    */
    auto GetTriangles() const -> std::vector<NRenderer::TTriangle3d> override;

 private:
    NRenderer::TPoint3d A_;
    NRenderer::TPoint3d B_;
    NRenderer::TPoint3d C_;
    NRenderer::TPoint3d D_;
    NRenderer::TPoint3d E_;
    NRenderer::TPoint3d F_;
    NRenderer::TPoint3d G_;
    NRenderer::TPoint3d H_;
    std::array<sf::Color, COUNT_COLORS> Colors_;
};

}  // namespace NWorld
