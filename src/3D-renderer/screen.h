#pragma once

#include "array.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

namespace NRenderer {

/*!
  \brief Содержит размеры экрана
*/
struct TScreenSize {
    int64_t Width;
    int64_t Height;
};

/*!
  \brief Экран с пикселями

  Хранит пиксели на экране и дает к ним доступ
*/
class TScreen {
 public:
    /*!
      \brief Создает экран по ширине и высоте
      \param width Ширина экрана в пикселях
      \param height Высота экрана в пикселях
    */
    TScreen(int64_t width, int64_t height);

    /*!
      \brief Доступ к пикселю
      \param col Столбец пикселя
      \param row Строка пикселя
      \returns Ссылка на пиксель

      Если пиксель за границами экрана, поведение не определено
      Для константной версии см. TScreen::operator()(int64_t, int64_t) const
    */
    auto operator()(int64_t col, int64_t row) -> sf::Vertex&;
    /*!
      \brief Доступ к пикселю только на чтение
      \param col Столбец пикселя
      \param row Строка пикселя
      \returns Константная ссылка на пиксель

      Если пиксель за границами экрана, поведение не определено
      Для неконстантной версии см. TScreen::operator()(int64_t, int64_t)
    */
    auto operator()(int64_t col, int64_t row) const -> const sf::Vertex&;

    /*!
      \brief Очищает экран
      \param value Новое значение всех пикселей

      Устанавливает значение всех пикселей на экране \ref value
    */
    void Clear(sf::Vertex value = {});
    /*!
      \brief Получает размеры экрана
      \returns Размеры экрана
    */
    auto Size() const -> TScreenSize;

    /*!
      \brief Полуачает картинку на экране
      \returns Картинка в видеопамяти
      \throws std::runtime_error Если не удалось выделить видеопамять

      Копирует картинку на экране в видеопамять и возвращает
      Не очищает экран, для очистки используйте TScreen::Clear()
    */
    auto Picture() const -> sf::VertexBuffer;

 private:
    TPlain2DArray<sf::Vertex> Data_;
    int64_t Width_ = 0;
    int64_t Height_ = 0;
};

}  // namespace NRenderer
