#pragma once

#include "camera.h"
#include "screen.h"
#include "zbuffer.h"
#include "object.h"

#include <SFML/Graphics.hpp>

namespace NRenderer {

/*!
  \brief Класс, занимающийся отрисовкой треугольников на экран

  Класс с основной логикой - в нем непосредственно объекты преобразуются в пиксели на экране
*/
class TRenderer {
 public:
    /*!
      \brief Создает renderer для экрана с заданными шириной и высотой
      \param width Ширина экрана в пикселях
      \param height Высота экрана в пикселях
      \throws std::bad_alloc Если не удалось выделить память
    */
    TRenderer(int width, int height) : Camera_(width, height), Screen_(width, height), ZBuffer_(width, height) {
    }

    /*!
      \brief Отрисовывает треугольник
      \param triangle - треугольник в глобальном координатном пространстве

      Отрисовывает треугольник на экране с учетом того, что он может быть не полностью виден
      или его могут закрывать другие объекты
    */
    void Add(TTriangle4d triangle);
    /*!
      \brief Отрисовывает объект
      \param object - объект в глобальном координатном пространстве

      Поочередно отрисовывает все треугольники объекта
    */
    void Add(const NWorld::IObject& object);
    /*!
      \brief Переносит отрендеренный рисунок в окно и очищает буферы
      \param window - окно, на котороу будет перенесено изображение

      \throws std::runtime_error если не удалось выделить буфер в видеопамяти
    */
    void Flush(sf::RenderWindow& window);
    /*!
      \brief Доступ к камере
      \returns Камера привязанная к рендереру

      Для константной версии см. TRenderer::GetCamera() const
    */
    auto GetCamera() -> TCamera&;
    /*!
      \brief Константный доступ к камере
      \returns Камера привязанная к рендереру

      Для неконстантной версии см. TRenderer::GetCamera()
    */
    auto GetCamera() const -> const TCamera&;

 private:
    /*!
      \brief Рисует треугольник на экране
      \param triangle Треугольник, не вылезающий за границы, в координатном пространстве камеры

      Вспомогательная функция для TRenderer::Add(const TTriangle4d&)
    */
    void DrawOnScreen(const TTriangle4d& triangle);

 private:
    TCamera Camera_;
    TScreen Screen_;
    TZBuffer ZBuffer_;
};

}  // namespace NRenderer
