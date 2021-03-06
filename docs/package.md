# Пакетные менеджеры C++
При написании больших пакетов всегда появляются внешние зависимости такие как `boost`, `folly` и другие.

В нашем случае мы пользуемся внешними библиотеками `sfml`, `Eigen`, `glog`, `nlohmann_json`.

Есть много пакетных менеджеров, но мы рассмотрим три самых популярных способа поставить пакеты.

## Системный менеджер пакетов
`apt`, `pacman`, `dnf`, `homebrew` и прочие системные менеджеры пакетов часто дают возможность поставить ту или иную библиотеку.

Однако у этого есть множество недостатков:

* Нельзя поставить разные версии одной и той же библиотеки для разных проектов, часто вообще нельзя выбрать версию пакета
* Слабая переносимость между разными системами: своя инструкция под каждую систему
* Сравнительно малое количество доступных библиотек

Поэтому этот вариант обрасываем сразу

## Conan
Один из двух самых популярных пакетных менеджеров для `C++`, я выбрал именно его потому что больше опыта в работе с ним.

Плюсы:

* Огромный репозиторий
* Достаточно просто в установке
* Интеграция с `Cmake`

Минусы:

* Нужно потратить немного времени чтобы разобраться

## Vcpkg
Второй популярный менеджер пакетов от `Microsoft`, так же как и `Conan` покрывает 99% требуемых сценариев работы.

Более детальное сравнение с `Conan` доступно [здесь](https://github.com/52doho/vcpkg-vs-conan), однако на практике большой разницы между ними вы скорее всего не обнаружите.

Пример работы `vcpkg` так же есть на [хабре](https://habr.com/ru/post/549788/).