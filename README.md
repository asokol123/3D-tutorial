# Краткое руководство как написать самому с нуля 3D-renderer на C++ и не умереть

Что __входит__ в это руководство:

* В каком порядке подходить к созданию проекта
* Какие технологии нужны и зачем
* Как сделать написание кода и отладку проще
* Является ли `C++` хорошим выбором для этого проекта

Что __не входит__ в это руководство:

* Как именно получить матрицы преобразований координатных пространств
* Почему все преобразования допустимы и не изменяют картину

Само руководство [тут](./docs/README.md).

## Зависимоти
* `conan` с включенным каналом [bincrafters](https://bincrafters.readthedocs.io/en/latest/)
* `cmake`

## Как собрать код

`SFML` есть только в пользовательском репозитории `bincrafters`. Поэтому сначала надо настроить `conan`.

```bash
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan config set general.revisions_enabled=1
```

```bash
mkdir src/build
cd src/build
conan install ..
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Как запустить пример
```bash
cd src
python ./resources/generate.py
./build/bin/test
```

## Как это выглядит
![Скриншот](./images/example.png)

## Автоматическая документация
С использованием `doxygen`:
```bash
cd src
doxygen doxygen
```
После этого открыть в браузере файл `src/docs/html/index.html`
