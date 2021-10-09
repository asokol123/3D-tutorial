#pragma once

#include "world.h"

namespace NParser {

/*!
  \brief Загружает объекты из файла
  \throws std::invalid_argument если файл не найден или невалиден

  Загружает объекты из файла и добавляет в мир
  Сейчас поддержан только json-формат и только кубы
*/
void LoadFile(const std::string& filename, NWorld::TWorld& world);

}  // namespace NParser
