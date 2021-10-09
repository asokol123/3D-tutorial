#pragma once

#include "geometry/objects.h"
#include "camera.h"

#include <vector>

namespace NRenderer::NGeometry {

/*!
  \brief Обрезает треугольник по дальностям камеры
  \param triangle Треугольник в пространстве камеры
  \returns Список треугольников после обрезания

  Треугольников может быть несколько, поэтому возвращается список
*/
auto Clip(const TTriangle4d& triangle) -> std::vector<TTriangle4d>;
/*!
  \brief Получает z-координату точку на плоскости
  \param plane Треугольник, задающий плоскость
  \param x X-координата точки
  \param y Y-координата точки
  \returns z Z-координата точки

  Поведение неопределено если на плоскости нет такой точки
*/
auto GetZOnPlane(const TTriangle4d& plane, double x, double y) -> double;

}  // namespace NRenderer::NGeometry
