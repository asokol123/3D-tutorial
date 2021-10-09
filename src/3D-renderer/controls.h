#pragma once

#include "camera.h"

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <map>

namespace NWorld {

/*!
  \brief Взаимодействует с клавиатурой

  Класс для считывания действий с клавиатуры и упаравления камерой
*/
class TController {
 public:
    using THandler = std::function<void()>;

    /*!
      \brief Создает controller над заданной камерой
    */
    explicit TController(NRenderer::TCamera& camera);

    /*!
      \brief Выполняет все действия

      Поочередно проверяет какие кнопки нажаты и выполняет соответствующие преобразования над камерой
    */
    void Handle();

 private:
    NRenderer::TCamera& Camera_;
    std::map<sf::Keyboard::Key, THandler> Handlers_;
};

}  // namespace NWorld
