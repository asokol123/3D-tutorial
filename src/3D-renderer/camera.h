#pragma once

#include "geometry/objects.h"
#include <SFML/System.hpp>

namespace NRenderer {

/*!
  \brief Содержит расстояния для урезания камеры
*/
struct TClippingDistances {
    double min;
    double max;
};

/*!
  \brief Описыват камеру

  Камера - объект в пространстве, так же отвечает за преобразования точек в свою систему координат и на экран
*/
class TCamera {
 public:
    /*!
      \brief Создает камеру по ширине и высоте
      \param width - ширина
      \param height - высота

      Создает камеру с данным обзором
    */
    TCamera(double width, double height);

    /*!
      \brief Переводит точку в координатное пространство камеры
      \param point Точка в глобальном координатном пространстве
      \returns Точка в координатном пространстве камеры

      Возвращает точку в координатном пространстве с
      началом в камере соответственно ее направлению и повороту
    */
    auto ToCamera(const TPoint4d& point) const -> TPoint4d;
    /*!
      \brief Переводит треугольник в координатное пространство камеры
      \param triangle Треугольник в глобальном координатном пространстве
      \returns Треугольник в координатном пространстве камеры

      Переводит все точки треугольника в координатное пространство камеры
    */
    auto ToCamera(const TTriangle4d& triangle) const -> TTriangle4d;
    /*!
      \brief Переводит точку в координатное пространство экрана
      \param point Точка в координатном пространстве камеры
      \returns Точка в координатном пространстве экрана

      Возвращает точку в координатном пространстве с
      началом в экране соответственно его направлению и повороту

      x и y - коорднаты точки на экране, z - ее глубина
    */
    auto ToScreen(const TPoint4d& point) const -> TPoint4d;
    /*!
      \brief Переводит треугольник в координатное пространство экрана
      \param triangle Треугольник в координатном пространстве камеры
      \returns Треугольник в координатном пространстве экрана

      Переводит все точки треугольника в координатное пространство экрана
    */
    auto ToScreen(const TTriangle4d& triangle) const -> TTriangle4d;
    /*!
      \brief Вращает камеру
      \param matrix Матрица поворота

      Вращает камеру в соответствии с данной матрицей поворота
    */
    void Rotate(const TMatrix4d& matrix);
    /*!
      \brief Перемещает камеру в пространстве
      \param direction Вектор сдвига

      Двигает камеру на заданный вектор
    */
    void Move(const TVector4d& direction);
    /*!
      \brief Возвращает расстояния, на котором камера обрезает объекты
      \returns Минимальное и максимальное расстояния
    */
    static auto GetClippingDistances() -> TClippingDistances;

 private:
    /*!
      \brief Создает матрицы преобразований

      Используется после создания камеры или ее перемещений и вращений
    */
    void InitTransformations();

 private:
    static const TPoint4d LEFT_POINT;
    static const TPoint4d RIGHT_POINT;
    TPoint4d Focus_{0, 0, 0, 1};

    double Width_ = 0;
    double Height_ = 0;

    TMatrix4d TransformToScreen_;
    TMatrix4d TransformToCamera_;
    TMatrix4d Rotation_{TMatrix4d::Identity()};
};

}  // namespace NRenderer
