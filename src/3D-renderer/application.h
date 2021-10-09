#pragma once

#include "controls.h"
#include "camera.h"
#include "parser.h"
#include "renderer.h"
#include "world.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace NRenderer {

/*!
  \brief Основной класс приложения, упарвляет всем остальным

  Создает и влаеет окном, рисует на нем сцену и запускает event loop
*/
class TApplication {
 public:
    /*!
      \brief Конструктор окна
      \param title - Заголовок окна
      \param width - длина окна в пикселях
      \param height - высота окна в пикселях
    */
    TApplication(const std::string& title, int32_t width, int32_t height);

    /*!
      \brief Проверяет, открыто ли окно
      \returns true если окно открыто, false если закрыто
     */
    auto IsOpen() const -> bool;
    /*!
      \brief Закрывает окно
     */
    void Close();
    /*!
      \brief Загружает объекты из файла
      \param filename - абсолютный или относительный путь к файлу
      \throws - invalid_argument если файл ненайден или некорректен
     */
    void Load(const std::string& filename);
    /*
       \brief Перерисовывет изображение
     */
    void Redraw();
    /*
       \brief Запускает event loop пока окно не закроют
     */
    void Run();

 private:
    sf::RenderWindow Window_;
    TRenderer Renderer_;
    NWorld::TWorld World_;
    NWorld::TController Controller_;
};

}  // namespace NRenderer
