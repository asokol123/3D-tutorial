#pragma once

#include "geometry/objects.h"
#include <vector>

namespace NWorld {

/*!
  \brief Интерфейс объекта

  Интерфейс объекта, единственное требование - все объекты должны разбиваться на треугольники
*/
class IObject {
 public:
    /*!
      \brief Разбиение на треугольники
      \returns Список треугольников

      Каждый объект должен триангулироваться, потому что примитив рендерера - треугольники
    */
    virtual auto GetTriangles() const -> std::vector<NRenderer::TTriangle3d> = 0;
    /*!
      \brief Виртуальный деструктор для наследования

      Для возможности уничтожать наследников по указателю без уточки ресурсов
    */
    virtual ~IObject() = default;
};

}  // namespace NWorld
