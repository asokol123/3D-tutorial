#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <utility>

namespace NRenderer {

using TPoint4d = Eigen::Vector4d;
using TPoint3d = Eigen::Vector3d;
using TVector4d = Eigen::Vector4d;
using TMatrix4d = Eigen::Matrix4d;

namespace NGeometry {

/*!
  \brief Нормализует 4-х мерную точку
  \param p Точка для нормализации
  \returns Нормализованная точка

  Возвращает отнормированную точку
  У возвращаемой точки w = 1
*/
[[nodiscard]] auto Normalize(TPoint4d p) -> TPoint4d;

}  // namespace NGeometry

/*!
  \brief Треугольник над произвольными точками

  Содержит три точки и цвет
  Если точки 4-х мерные, то нормирует
*/
template <typename TPoint>
class TTriangle {
 public:
    /*!
      \brief Создает треугольник
      \param x Первая точка
      \param y Вторая точка
      \param z Третья точка
      \param color Цвет

      Создает треугольник по заданным параметрам
      Если точки четырехмерные, то нормирует
    */
    TTriangle(TPoint x, TPoint y, TPoint z, sf::Color color) : X_(std::move(x)), Y_(std::move(y)), Z_(std::move(z)), Color_(color) {
        if constexpr (std::is_same_v<TPoint, TPoint4d>) {
            X_ = NGeometry::Normalize(X_);
            Y_ = NGeometry::Normalize(Y_);
            Z_ = NGeometry::Normalize(Z_);
        }
    }

    /*!
      \brief Получение цвета
      \returns Цвет треугольника
    */
    auto Color() const -> sf::Color {
        return Color_;
    }

    /*!
      \brief Полученеи точек
      \returns Копия точек
    */
    auto GetPoints() const -> std::tuple<TPoint, TPoint, TPoint> {
        return {X_, Y_, Z_};
    }

 private:
    TPoint X_;
    TPoint Y_;
    TPoint Z_;
    sf::Color Color_;
};

using TTriangle4d = TTriangle<TPoint4d>;
using TTriangle3d = TTriangle<TPoint3d>;

auto Point3dTo4d(TPoint3d point) -> TPoint4d;
auto Triangle3dTo4d(const TTriangle3d& triangle) -> TTriangle4d;

}  // namespace NRenderer
