#pragma once

#include "array.h"
#include "screen.h"

namespace NRenderer {

/*!
  \brief Класс для z-буфера

  Хранит в себе текущую глубину для каждого пикселя
*/
class TZBuffer {
 public:
    /*!
      \brief Создает TZBuffer с заданными шириной и высотой
      \param width Ширина в пикселях
      \param height Высота в пикселях
    */
    TZBuffer(int64_t width, int64_t height);

    /*!
      \brief Доступ к пикселю
      \param col Столбец пикселя
      \param row Строка пикселя
      \returns Ссылка на пиксель

      Поведение неопределено если пиксель за границами экрана
      Для константной версии см. TZBuffer::operator()(int64_t, int64_t) const
    */
    auto operator()(int64_t col, int64_t row) -> double&;
    /*!
      \brief Доступ к пикселю на чтение
      \param col Столбец пикселя
      \param row Строка пикселя
      \returns Константная ссылка на пиксель

      Поведение неопределено если пиксель за границами экрана
      Для неконстантной версии см. TZBuffer::operator()(int64_t, int64_t)
    */
    auto operator()(int64_t col, int64_t row) const -> double;

    /*!
      \brief Очищает z-буфер
    */
    void clear();
    /*!
      \brief Получение размеров
      \returns Ширина и высота
    */
    auto size() const -> TScreenSize;

 private:
    TPlain2DArray<double> ZCoords_;
    int64_t Width_;
    int64_t Height_;
};

}  // namespace NRenderer
