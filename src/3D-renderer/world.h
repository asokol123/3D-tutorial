#pragma once

#include "object.h"
#include <memory>
#include <vector>

namespace NWorld {

/*!
  \brief Хранит все объекты

  Контейнер, хранящий в себе все объекты и владеющий ими
*/
class TWorld {
 public:
    using Object = std::unique_ptr<IObject>;
    using iterator = std::vector<Object>::iterator;
    using const_iterator = std::vector<Object>::const_iterator;

    /*!
      \brief Добавляет объект в мир
      \param object std::unique_ptr на добавляемый объект
    */
    void Add(Object object);

    /*!
      \brief Добавляет объект в мир
      \param object Ссылка на объект

      Более удобная обертка над TWorld::Add(Object)
    */
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<IObject, T>>>
    void Add(const T& object) {
        Objects_.emplace_back(std::make_unique<T>(object));
    }

    /*!
      \brief Итератор на начало

      Константная версия - TWorld::Begin() const
    */
    auto Begin() -> iterator;
    /*!
      \brief Константный итератор на начало

      Неконстантная версия - TWorld::Begin()
    */
    auto Begin() const -> const_iterator;

    /*!
      \brief То же самое, что и TWorld::Begin()
    */
    auto begin() -> iterator;
    /*!
      \brief То же самое, что и TWorld::Begin() const
    */
    auto begin() const -> const_iterator;

    /*!
      \brief Итератор на конец

      Константная версия - TWorld::End() const
    */
    auto End() -> iterator;
    /*!
      \brief Константный итератор на конец

      Неконстантная версия - TWorld::End()
    */
    auto End() const -> const_iterator;

    /*!
      \brief То же самое, что и TWorld::end()
    */
    auto end() -> iterator;
    /*!
      \brief То же самое, что и TWorld::end() const
    */
    auto end() const -> const_iterator;

 private:
    std::vector<Object> Objects_;
};

}  // namespace NWorld
