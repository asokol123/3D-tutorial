#pragma once

#include <vector>

namespace NRenderer {

/*!
  \brief Класс для хранения двумерного массива и удобного и безопасного доступа к нему

  Интерфейс двумерного массива, хранит внутри данные в одномерном массиве подряд
 */
template <typename T>
class TPlain2DArray {
 public:
    struct TRowProxy;
    struct TConstRowProxy;

 public:
    /*!
      \brief Создает массив заданных размеров заполненный данным значением
      \param width Длина массива (по первому индексу)
      \param height Высота массива (по второму индексу)
      \throws std::bad_alloc если не удалось выделить память
    */
    TPlain2DArray(int64_t width, int64_t height, T value = {});

    /*!
      \brief Указатель на данные
      \returns Указатель на данные

      Данные лежат по столбцам (элементы одного столбца подряд)
      Для константной версии см. TPlain2DArray<T>::Data() const
    */
    auto Data() -> T*;
    /*!
      \brief Константный указатель на данные
      \returns Указатель на данные

      Данные лежат по столбцам (элементы одного столбца подряд)
      Для неконстантной версии см. TPlain2DArray<T>::Data()
    */
    auto Data() const -> const T*;

    /*!
      \brief Доступ к элементу
      \param column Столбец элемента
      \param row - Строка элемента
      \returns Ссылка на элемент

      Если доступ за границы массива, поведение не определено
      Для константной версии см. TPlain2DArray<T>::operator()(int64_t, int64_t) const
    */
    auto operator()(int64_t column, int64_t row) -> T&;
    /*!
      \brief Константный доступ к элементу
      \param column Столбец элемента
      \param row - Строка элемента
      \returns Константная ссылка на элемент

      Если доступ за границы массива, поведение не определено
      Для неконстантной версии см. TPlain2DArray<T>::operator()(int64_t, int64_t)
    */
    auto operator()(int64_t column, int64_t row) const -> const T&;

    /*!
      \brief Доступ к столбцу
      \param column Столбец
      \returns Proxy-объект TRowProxy

      Если доступ за границы массива, поведение не определено
      Для константной версии см. TPlain2DArray<T>::operator[](int64_t) const
    */
    auto operator[](int64_t column) -> TRowProxy;
    /*!
      \brief Доступ к столбцу
      \param column Столбец
      \returns Proxy-объект TConstRowProxy

      Если доступ за границы массива, поведение не определено
      Для неконстантной версии см. TPlain2DArray<T>::operator[](int64_t)
    */
    auto operator[](int64_t column) const -> TConstRowProxy;

    /*
      \brief Итератор на начало
      \returns Итератор на начало

      Для константной версии см. TPlain2DArray<T>::Begin() const
    */
    auto Begin();
    /*
      \brief Константный итератор на начало
      \returns Константный итератор на начало

      Для неконстантной версии см. TPlain2DArray<T>::Begin()
    */
    auto Begin() const;
    /*
      \brief Итератор на конец
      \returns Итератор на конец

      Для константной версии см. TPlain2DArray<T>::End() const
    */
    auto End();
    /*
      \brief Константный итератор на конец
      \returns Константный итератор на конец

      Для неконстантной версии см. TPlain2DArray<T>::End()
    */
    auto End() const;

 public:
    /*!
      \brief Возвращается из operator[], позволяет обращаться только к конкретному столбцу

      Служит для доступа к одному конкретному столбцу
      Константная версия - TConstRowProxy
    */
    struct TRowProxy {
        int64_t Column;
        TPlain2DArray* Arr;

        auto operator[](int64_t row) const -> T&;
    };

    /*!
      \brief Возвращается из operator[] const, позволяет обращаться на чтение только к конкретному столбцу

      Служит для доступа на чтение к одному конкретному столбцу
      Неконстантная версия - TRowProxy
    */
    struct TConstRowProxy {
        int64_t Column;
        const TPlain2DArray* Arr;
        auto operator[](int64_t row) const -> const T&;
    };

 private:
    /*!
      \brief Получает одномерный индекс из двумерного
      \returns Полученный индекс

      Используется формула column * Height_ + row
    */
    auto TransformIndex(int64_t column, int64_t row) const -> int64_t;

 private:
    int64_t Width_;
    int64_t Height_;
    std::vector<T> Data_;
};

}  // namespace NRenderer

#include "array-inl.h"
