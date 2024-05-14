# yadro_test
1. [Задание](#задание)
2. [Инструкция по сборке](#инструкция-по-сборке)

## Задание
<h5>C++</h5>
<h5>Решением задания будет: </h5>
Файл или несколько файлов с исходным кодом программы
на языке C++ (стандарт до C++20 включительно), инструкции по сборке и тестовые
примеры (количество тестов – на усмотрение разработчика).
Входные данные представляют собой текстовый файл. Файл указывается первым
аргументом при запуске программы. Пример запуска программы:

$ task.exe test_file.txt

Программа должна компилироваться компилятором gcc или clang в Linux,
mingw/cygwin в Windows. Рекомендуется использование стандартной библиотеки
(STL). Использование любых сторонних библиотек, кроме STL, запрещено. В
решении, кроме файлов с исходным кодом, требуется предоставить инструкции по
компиляции программы для проверки. Можно, но необязательно, использовать
следующие системы автоматизации сборки: make, automake, cmake, gradle;
проприетарные средства сборки не допускаются: например, файлы проектов MS
Visual Studio не подойдут.
Можно (но необязательно) написать проверочные юнит-тесты с использованием
доступной библиотеки (Google Test, CppUTest, и т.п.).
<h5>Формат входных данных</h5>

~~~
<количество столов в компьютерном клубе>
<время начала работы> <время окончания работы>
<стоимость часа в компьютерном клубе>
<время события 1> <идентификатор события 1> <тело события 1>
<время события 2> <идентификатор события 2> <тело события 2>
...
<время события N> <идентификатор события N> <тело события N>
~~~
Первая строка содержит количество столов в виде целого положительного числа.
Во второй строке задается время начала и окончания работы компьютерного клуба,
разделенные пробелом.
В третьей строке задается стоимость часа в компьютерном клубе в виде целого
положительного числа.
Затем задается список входящих событий, разделенных переносом строки. Внутри
строки в качестве разделителя между элементами используется один пробел.
<ul>
<li>Имена клиентов представляют собой комбинацию символов из алфавита a..z, 0..9, _, -</li>
<li>Время задается в 24-часовом формате с двоеточием в качестве разделителя
XX:XX, незначащие нули обязательны при вводе и выводе (например 15:03 или
08:09). </li>
<li>Каждый стол имеет свой номер от 1 до N, где N – общее число столов, указанное в
конфигурации.</li>
<li>Все события идут последовательно во времени. (время события N+1) ≥ (время
события N).</li>
</ul>
<h5>Выходные данные</h5>
Если входные данные не удовлетворяют описанному формату, программа должна
вывести в консоль первую строку, в которой найдена ошибка формата и
завершиться.
Если входные данные корректны, программа должна вывести следующий результат:
<ul>
<li>На первой строке выводится время начала работы.</li>
<li>Далее перечислены все события, произошедшие за рабочий день (входящие и
исходящие), каждое на отдельной строке. </li>
<li>После списка событий на отдельной строке выводится время окончания
работы. </li>
<li>Для каждого стола на отдельной строке выведены через пробел следующие
параметры: Номер стола, Выручка за день и Время, которое он был занят в
течение рабочего дня. </li>
После этого программа должна завершиться.
</ul> 
<h5>Подсчет выручки</h5>
За каждый час, проведённый за столом, клиент платит цену, указанную в
конфигурации. При оплате время округляется до часа в большую сторону, поэтому,
даже если клиент занимал стол всего несколько минут, он платит за целый час.
Выручка – сумма, полученная ото всех клиентов за всё время работы компьютерного
клуба.
<h5>События</h5>
Все события характеризуются временем и идентификатором события. Исходящие
события — это события, создаваемые во время работы программы. События,
относящиеся к категории «входящие», сгенерированы быть не могут, и выводятся в
том же виде, в котором были поданы во входном файле.
<h5>Входящие события:</h5>
<h5>ID 1. Клиент пришел</h5>
<ul>
<li>Формат: &lt;время&gt; 1 &lt;имя клиента&gt;</li>
<li>Если клиент уже в компьютерном клубе, генерируется ошибка &quot;YouShallNotPass&quot; </li>
<li>Если клиент пришел в нерабочие часы, тогда &quot;NotOpenYet&quot; </li>
</ul>
<h5>ID 2. Клиент сел за стол</h5>
<ul>
<li>Формат: &lt;время&gt; 2 &lt;имя клиента&gt; &lt;номер стола&gt;
<li>Если клиент уже сидит за столом, то он может сменить стол.</li>
<li>Если стол &lt;номер стола&gt; занят (в том числе, если клиент пытается пересесть за
стол, за которым сам и сидит), генерируется ошибка &quot;PlaceIsBusy&quot;.</li>
<li>Если клиент не находится в компьютерном клубе, генерируется ошибка
&quot;ClientUnknown&quot;.</li>
</ul>   
<h5>ID 3. Клиент ожидает</h5>
<ul>   
<li>Формат: &lt;время&gt; 3 &lt;имя клиента&gt;</li>
<li>Если в клубе есть свободные столы, то генерируется ошибка &quot;ICanWaitNoLonger!&quot;.</li>
<li>Если в очереди ожидания клиентов больше, чем общее число столов, то клиент
уходит и генерируется событие ID 11.</li>
</ul>   
<h5>4. Клиент ушел</h5>
<ul>
<li>Формат: &lt;время&gt; 4 &lt;имя клиента&gt;</li>
<li>Если клиент не находится в компьютерном клубе, генерируется ошибка
&quot;ClientUnknown&quot;.</li>
<li>Когда клиент уходит, стол, за которым он сидел освобождается и его занимает
первый клиент из очереди ожидания (ID 12).</li>
</ul>
<h5>Исходящие события:</h5>
<h5>ID 11. Клиент ушел</h5>
<ul>
<li>Формат: &lt;время&gt; 11 &lt;имя клиента&gt;</li>
<li>Генерируется в конце рабочего дня для всех клиентов, оставшихся в компьютерном
клубе, в алфавитном порядке их имен. </li>
<li>А также, когда клиент встает в очередь, а очередь ожидания уже заполнена.</li>
</ul>
<h5>ID 12. Клиент сел за стол</h5>
<ul>
<li>Формат: &lt;время&gt; 12 &lt;имя клиента&gt; &lt;номер стола&gt;</li>
<li>Генерируется для первого клиента в очереди при освобождении любого стола.</li>
</ul>
<h5>ID 13. Ошибка</h5>
<ul>
<li>Формат: &lt;время&gt; 13 &lt;ошибка&gt;</li>
<li>Выводится сразу после события, которое вызвало ошибку. Событие, вызвавшее
ошибку, считается не выполненным, и никакого эффекта на состояние клиентов не
оказывает.</li>
</ul>
<h5>Пример работы программы:</h5>

| Входные данные:   | Вывод в консоль:          |
|-------------------|---------------------------|
| 3                 | 09:00                     |
| 09:00 19:00       | 08:48 1 client1           |
| 10                | 08:48 1 client1           |
| 08:48 1 client1   | 09:41 1 client1           |
| 09:41 1 client1   | 09:48 1 client2           |
| 09:48 1 client2   | 09:52 3 client1           |
| 09:52 3 client1   | 09:52 13 ICanWaitNoLonger! |
| 09:54 2 client1 1 | 09:54 2 client1 1         |
| 10:25 2 client2 2 | 10:25 2 client2 2         |
| 10:58 1 client3   | 10:58 1 client3           |
| 10:59 2 client3 3 | 10:59 2 client3 3         |
| 11:30 1 client4   | 11:30 1 client4           |
| 11:35 2 client4 2 | 11:35 2 client4 2         |
| 11:45 3 client4   | 11:35 13 PlaceIsBusy      |
| 12:33 4 client1   | 11:45 3 client4           |
| 12:43 4 client2   | 12:33 4 client1           |
| 15:52 4 client4   | 12:33 12 client4 1        |
|                   | 12:43 4 client2           |
|                   | 15:52 4 client4           |
|                   | 19:00 11 client3          |
|                   | 19:00                     |
|                   | 1 70 05:58                |
|                   | 2 30 02:18                |
|                   | 3 90 08:01                |

## Инструкция по сборке

В ``solution`` лежит ``Makefile``, сборка происходит с помощью него.

Для сборки команда ``make main``бинарник появится в папке ``bin``, для запуска тестов ``make test``, в той же папке появится бинарник, который будет запущен
