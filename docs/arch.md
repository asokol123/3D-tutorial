# Основные сущности

## Точка
Пространство 3-х мерное, однако нам понадобятся 4-х мерные точки потому что с ними проще делать преобразования пространства.

Четвертая координата отвечает за то, на сколько точка далеко от начала координат. 3-х мерные координаты определяются как `x / w, y / w, z / w`. Таким образом мы разрешаем себе иметь точки на бесконечности если `w = 0`

Можно написать свои классы, однако мы поспользуемся библиотекой для линейной алгебры `Eigen`. Это позволит не писать руками все операторы в том числе умножения на матрицу.

Про плюсы и минусы этого подхода более подробно в разделе "особенности C++"

## Треугольник
Треугольник - базовый объект. Рендерер будет работать именно с треугольниками, остальные объекты разбиваются на треугольники.

Нам понадобятся как 2-d, так и 4-d треугольники, поэтому проще всего сделать треугольник шаблонынм классом, не зависящим от размерности точки.

## Камера
Камера определяется тремя вещами:

* Положение в пространстве
* Направление взгляда
* Пирамида зрения

Так же камера будет отвечать за преобразования между системами кординат им проективное преобразование пространства.

Проективное преобразование переводит пирамиду зрения в параллелепипед, отправляя камеру бесконечно назад (благодаря 4-й координате).

Это позволит намного проще отсекать треугольники, потому что параллелепипед намного более простая структура, чем пирамида.

## Экран
Экран соответствует окну нашего приложения.

Состоит из пикселей, имеет определенные размеры, из него картинка потом будет передаваться в библиотеку, выводящую ее на экран.

## Z-буфер
Простая, но необходимая сущность.

При отрисовывании треугольников на экране они могут перекрывать друг друга, и нужно показать тот, который ближе. Для этого нужно для каждого отрисованного пикселя помнить, насколько он далеко от камера.

Именно за это отвечает `Z-buffer`, он для каждого соответствующего экрану пикселя хранит его глубину.

## Renderer
Класс с самой сложной алгоритмической работой, именно он отрисовывает треугольники на экране. Владеет экраном, камерой и z-буфером.

## Object
Произвольный объект (интерфейс с различными реализациями). Единственное требование - разбивается на треугольники.

## World
Объединяет в себе все объекты. По сути просто контейнер с объектами, однако логически это отдельная сущность, и поэтому лучше вынести в отдельный класс

## Parser
Отвечает за считывание и парсинг мира (и прочих данных при необходимости) из файла

## Controller
Обрабатывает ввод с клавиатуры. Ссылается на камеру.

## Application
Объединяет все остальные объекты, именно с `Application` обычно будут работать пользватели.

Владеет `Renderer`-ом, миром, парсером и контроллером.

