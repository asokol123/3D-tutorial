#pragma once

#include "geometry/objects.h"
#include <iostream>

/*!
  \brief Вывод в поток треугольника в json-like формате

  Вывод в поток в человекочитаемом формате
  Используется для логирования и отладки
*/
auto operator<<(std::ostream& out, const NRenderer::TTriangle4d& triangle) -> std::ostream&;
/*!
  \brief Вывод в поток точки в json-like формате

  Вывод в поток в человекочитаемом формате
  Используется для логирования и отладки
*/
auto operator<<(std::ostream& out, const NRenderer::TPoint4d& point) -> std::ostream&;
