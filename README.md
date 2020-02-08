Реализация паттерна Static polymorphism	with the curiously recurring template pattern

Класс и наследование, но тем не мение реализовываем статический полимрфизм.
Так же замеряем время выполнения: вызываем 10000000 функцию для одного указателя и для вектора указателей.

### Конфигурация
- QuadCore Intel Core i7-6700HQ, 3200 MHz  
- 24452 МБ  (DDR4 SDRAM)
- KINGSTON SA1000M8480G  (447 ГБ) - ssd M.2 PCIex4 3.0
- GeForce GTX 960M


### Вывод
- Classic Polymorphism
- [Image][Render] draw bg.png
- [Label][Render] draw text
- [Label][Button] draw

- meashuring execution time
- unique_ptr<Derrived> on Derrived class
- execute time duration = 305.869 milliseconds
- vector unique_ptr<Parent> on Derrived class
- execute time duration = 1619.15 milliseconds

- CRTP Polymorphism
- [Image][Render] draw bg.png
- [Label][Render] draw text
- [Label][Button] draw

- meashuring execution time
- unique_ptr<Derrived> on Derrived class
- execute time duration = 253.162 milliseconds
- vector unique_ptr<Parent> on Derrived class
- execute time duration = 3084.01 milliseconds

Сначала убеждаемся, что CRTP Polymorphism работает корректно - выводит тоже самое что и классический полиморфизм(виртуальные функции).
Далее замерям время выполнения.
Вызов пустой функции через указатель производного класса.

- Classic Polymorphism
- execute time duration = 305.869 milliseconds

- CRTP Polymorphism
- execute time duration = 253.162 milliseconds

Статический полиморфизм отрабатывает быстрее. Вызов через виртуальные фунции занимает больше времени.

Но обычно у нас есть вектор указателей базового класса на производный. В случае со статическим полиморфизмом указатель это std::variant 
с перечисленными в нем всеми указателями. И обходится он с помощью std::visit. Все это требует много времени и результаты следующие.

- vector unique_ptr<Parent> on Derrived class
- execute time duration = 1619.15 milliseconds

- vector unique_ptr<Parent> on Derrived class
- execute time duration = 3084.01 milliseconds

Т.е. проигрываем где то в 2 раза.


