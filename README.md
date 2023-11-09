# Лабораторная работа 8

## Теоретическая справка
**Что такое алгоритмы STL?**

Контейнеры STL представляли бы собой красивую выдумку, достаточно далёкую от
практического использования (как и было в первые годы существования STL),
если бы не следующее обстоятельство: из-за единой общей природы всех контейнеров
основные алгоритмы, представляющие интерес на практике, могут быть реализованы
в обобщённом виде, применимом к любым типам контейнеров. Алгоритмы — это самая
объёмная и самая востребованная часть библиотеки. Предоставляется настолько много
алгоритмов, что для детального описания их всех не хватит и объёмной книги.
В данной лабораторной работе вам предстоит ознакомиться лишь с некоторыми из них.

Описание всех алгоритмов вы найдете по [ссылке](https://en.cppreference.com/w/cpp/algorithm).

Также в C++20 библиотека алгоритмов была "расширена" библиотекой `<ranges>`. В ней ключевой
сущностью выступает "представление". Для понимания представлений необходимо ввести несколько
понятий.
- _Ленивое исполнение_ - (как противопоставление скорому) исполнение какого-либо алгоритма в момент
необходимости получения представления его результатов. При скором исполнении, в сравнении,
представление результатов алгоритма заготавливается предварительно.

Примеры:

``` cpp
void start_serving(const UserRepresentation&);
void start_serving_lazy(const FileStructure&, UserRepresentation get_repr*);

int main() {
  // imagine a file has been read here
  FileStructure read_data;
  // eager execution
  UserRepresentation repr = get_user_representation(read_data);
  start_serving(repr);
  
  // lazy execution
  start_serving_lazy(read_data, get_user_representation);
}
```
В этом примере ключевым моментом является то, что получение представления пользователя осуществляется
по запросу, когда это представление непосредственно требуется. В общем случае, особенно когда
требуемое пользовательское представление невозможно заготовить заранее (например при запросе в базу
данных), подход ленивого программирования позволяет довольно просто избежать лишних операций.
При скором исполнении же, получение представления будет осуществляться тогда, когда это захочет
программист, что может привести, например, к получению всех сущностей, лишнего чтения диска, излишнего
использования памяти и прочих неприятностей производительности.
- _Функции высшего порядка_ - типичные функции над общим набором данных. Примеры некоторых из них:
  - `map` - применить преобразование ко всем элементам набора данных (`std::transform`, `std::ranges::transform`
    и `std::views::transform`)
  - `filter` - пропустить элементы множества, не удовлетворяющие предикату (`std::remove_if`,
    `std::ranges::remove_if`, `std::views::filter`)
  - `reduce`, `fold` - объединить элементы набора данных какой-либо функцией, последовательно применяя её
    к аккумулятору и следующему элементу (`std::reduce`, `std::accumulate`)
- _Диапазон_ - пара итераторов, обозначающие начало и конец какого-либо набора данных. (`std::ranges::range`)
- Наконец, _представление_ - диапазон, в котором получение доступа к данным осуществляется за
  постоянную единицу времени. Примеры таких диапазонов - итераторы по контейнерам, тривиальные
  генераторы данных (счётчик) или множество указателей на значения.

Ввиду определения представления, можно сказать что функции высшего порядка `std::views::*`
применимы всегда, когда допустимо применение алгоритмов STL.

### Использование некоторых алгоритмов STL

#### `std::find`
Функция `std::find` ищет в диапазоне параметров `[first, last)` первый элемент, равный `value`

```cpp
template< class InputIt, class T >
InputIt find( InputIt first, InputIt last, const T& value );
```


#### `std::find_if`
Алгоритм `std::find_if` находит позицию первого вхождения элемента, удовлетворяющего определенному условию,
в диапазоне `[first, last)`.

```cpp
template<class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred);
```

Параметр `pred` - определенная пользователем функция, объект функции или лямбда-выражение,
определяющее условие, которое должно удовлетворяться искомым элементом. Предикат
берет один аргумент и возвращает `true` (условие удовлетворено) или `false` (условие
не удовлетворено). Прототип `pred` должна быть `bool pred(const T& arg);`, где `T` — тип,
к которому можно явным образом привести `InputIterator` при разименовании. Ключевое
слово `const` указывает, что объект функции или лямбда не должен изменять аргумент.

**Задача**. Найти первое четное число в контейнере.
```cpp
bool even(int a)
{
    return !odd(a);
}

// ...
std::vector<int> v = {1, 3, 5, 6, 7, 8, 9};
auto it2 = std::find_if(v.begin(), v.end(), even);
if (it2 == v.end())
  std::cout << "Все числа нечетные";
else
  std::cout << *it2;
// или
using namespace std::views;
auto found = v | filter(even) | take(1);
if (v.empty()) std::cout << "Все числа нечётные";
else std::cout <<*found.begin();
```

#### `std::count_if`
С помощью `std::count_if` можно легко получить количество элементов в диапазоне `[first, last)`, удовлетворяющих определенному
условию. Подсчитывает элементы, для которых предикат `pred` возвращает значение true. О том,
что такое предикат, можно прочитать выше.

```cpp
template< class InputIt, class UnaryPredicate >
typename iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPredicate pred);
```

**Задача**. Посчитать какое количество четных элементов в массиве
```cpp
bool even(int a)
{
    return !odd(a);
}

// ...
std::vector<int> v = {1, 3, 5, 6, 7, 8, 9};
auto count = std::count_if(v.begin(), v.end(), even);
std::cout << count;
// или
using namespace std::views;
auto needed = v | filter(even);
std::cout << needed.size();
```

#### `std::transform`
```cpp
template <class InIter, class OutIter, class Funс>
OutIter transform(InIter start, InIter end,
		  OutIter result, Func unaryfunc);
template <class InIter1, class InIter2, class OutIter, class Func>
OutIter transform(InIter1 start1, InIter1 end1, InIter2 start2,
		  OutIter result, Func binaryfunc);
```
Алгоритм `transform()` применяет функцию к диапазону элементов и сохраняет результат
в последовательности, заданной параметром `result`. В первой форме диапазон задается
параметрами `start` и `end`. Применяемая функция задается параметром `unaryfunc`.
Она принимает значение элемента в качестве параметра и должна возвратить преобразованное
значение.
Во второй форме алгоритма преобразование применяется с использованием бинарной функции,
которая принимает значение элемента из последовательности, предназначенного для преобразования,
в качестве первого параметра и элемент из второй последовательности в качестве второго параметра.
Обе версии возвращают итератор, указывающий на конец результирующей последовательности.

**Задача**. Дан массив чисел. Преобразовать его в массив квадратов этих чисел.

```cpp
int pow2(int a)
{
    return a * a;
}

// ...
std::vector<int> v = {1, 3, 5, 6, 7, 8, 9};
std::transform(v.begin(), v.end(), v.begin(), pow2);
// или так
std::vector<int> v = {1, 3, 5, 6, 7, 8, 9};
std::transform(v.begin(), v.end(), v.begin(), [](int a){ retunr a * a; });
// или
using namespace std::views;
auto transformed = v | transform(pow2);
v = std::vector<int>(transformed.begin(), transformed.end());
```

**Задача**. Дано два массива, получить новый массив, каждый элемент которого будет равен сумме соответсвующих элементов в изначальных.
```cpp
int sum(int a, int b)
{
    return a + b;
}

// ...
std::vector<int> v0 = {1, 3, 5, 6, 7, 8, 9};
std::vector<int> v1 = {-1, -3, -5, -6, -7, -8, -9};
std::vector<int> out(v0.size());
std::transform(v0.begin(), v0.end(), v1.begin(), out.begin(), sum);
// или
using namespace std::views;
auto output = zip(v0, v1) | transform([](std::tuple<int&, int&> pair) { std::get<0>(pair) + std::get<1>(pair) });
out = std::vector<int>(output.begin(), output.end());
```

#### `std::sort`
Сортировка последовательности `[first, last)`.
```cpp
template<class RandomAccessIterator>
void sort(RandomAccessIterator first,
          RandomAccessIterator last);

template<class RandomAccessIterator, class Predicate>
void sort(RandomAccessIterator first,
          RandomAccessIterator last,
          Predicate comp);
```

Первая форма алгоритма использует дефолтный функтор сравнения, а вторая позволяет
задать его самостоятельно.
Компаратор(смотри вторую форму) — это определенный пользователем объект функции
или лямбда-выражение, который как бы учит сортировать `sort`.

Так, например, можно сортировать по:
кратности на 3, четности или нечетности, изменить сторону сортировки на — по убыванию.
`sort` передает элементы компаратору, а компаратор проверяет их по вашему
алгоритму и передает `true` или `false`.

**Задача**. Отсортировать массив строк по *длине* строк, а не в лексикографическом порядке.
```cpp
bool compare_length(const std::string& a, const std::string& b)
{
    return a.size() < b.size();
}

std::sort(v.begin(), v.end(), compare_length);
```


#### `std::any_of`
Данный алгоритм проверяет, что предикат `pred` возвращает значение `true` для **хотя бы** одного элемента
в диапазоне `[first, last)`.
```cpp
template< class InputIt, class UnaryPredicate >
bool any_of(InputIt first, InputIt last, UnaryPredicate pred);
```

### Что такое лямбда-функция?
Лямбда-выражение (или просто лямбда) в `C++11` — это удобный способ определения анонимного
объекта-функции непосредственно в месте его вызова или передачи в функцию в качестве аргумента.
Если нужна функция, можно описать её лямбдой, а не описывать отдельную функцию, загромождая код.
Удобно в `STL`. Удобно когда выражение короткое. Иначе код становится ужасно читаем.
Лямбда-выражениями называются безымянные локальные функции, которые можно создавать
прямо внутри какого-либо выражения.
В этом примере лямбда-выражение передается в качестве аргумента функции `find_if`.
Лямбда-выражение возвращает значение `true`, если его параметром является четное число.
```cpp
list<int> numbers;
numbers.push_back(13);
numbers.push_back(17);
numbers.push_back(42);
numbers.push_back(46);
numbers.push_back(99);
auto result = find_if(numbers.begin(), numbers.end(),
                      [](int n){ return (n % 2) == 0; });
```
Для полного понимания того, как использовать лямбда- выражения, следует заглянуть
[сюда](https://msdn.microsoft.com/ru-ru/library/dd293599.aspx)

**Примеры, с которыми следует ознакомиться**
* [Здесь](https://github.com/bmstu-iu8-cpp/cpp-beginner-2017/tree/master/lab8)


## Задание
Требуется все задания выполнить с использованием библиотеки `<algorithm>` или `<ranges>`.

- Пусть есть структура `Student`
```cpp
struct Student
{
  std::string Name;
  std::string GroupId;
  std::vector<uint8_t> Ratings;
  std::vector<std::string> Subjects;
};
```
В поле `Ratings` представлены оценки по соответсвующему предмету из поля `Subjects`.
Предположим есть список студентов `std::vector<Student> students`.
Ваше задание состоит в реализации ряда функций. Все прототипы функций необходимо разместить
в файле header.hpp.

Реазилуйте функции, которые выполяют следующие действия с этим списком:
* отсортирует всех студентов по именам. Прототип:
```cpp
void SortByName(std::vector<Student>&);
```
* отсортирует всех студентов по средней оценке;
```cpp
void SortByRating(std::vector<Student>&);
```
* вернет студентов имеющих неудовлетворительную оценку хотя бы по одному предмету;
```cpp
std::vector<Student> FilterTwoness(const std::vector<Student>&);
```
* определит студентов, которые сдали все экзамены на 5.
```cpp
std::vector<Student> FilterExcellent(const std::vector<Student>&);
```
* сформирует список групп, т.е. создаст массив структур `Group`
```cpp
struct Group
{
    std::string Id;
    std::vector<Student> Students;
};
```

Прототип:
```cpp
std::vector<Group> Groups(const std::vector<Student>&);
```

- Вам предоставляется контейнер структур одного типа. Их надо преобразовать в другой тип.
Типы структур:

``` cpp
// may be password hash, fingerprint, totp secret, etc. plain bytes
using AuthFactor = std::vector<uint8_t>;

// Исходная структура
struct DatabaseRepr {
  size_t id;
  std::string name; // needs encoding
  std::string surname; // needs encoding
  int64_t date_of_birth; // unix timestamp
  int64_t last_seen; // unix timestamp
  std::vector<AuthFactor> auth_factors; // needs to be hidden
};

// Конечная структура
using timepoint_t = std::chrono::time_point<std::chrono::steady_clock>;
struct UserRepr {
  size_t id; // leave as is. useful for reverse lookup
  std::string name_encoded; // just replace everything strange with spaces.
  std::string surname_encoded; // the same as name
  timepoint_t date_of_birth;
  timepoint_t last_seen;
}; 
```

Прототип функции:

``` cpp
std::vector<UserRepr> userRepresent(std::vector<DatabaseRepr>::const_iterator begin,
                                      std::vector<DatabaseRepr>::const_iterator end);
```

- Вам предоставляется несколько контейнеров со структурами. Типы структур:

``` cpp
struct StudentDatabaseRepr {
  uint32_t id;
  std::string name;
};

struct StudentRatingsDatabaseRepr {
  uint32_t id;
  uint32_t student_id;
  std::string subject;
  uint8_t rating;
};

struct GroupsDatabaseRepr {
  uint32_t id;
  std::string group_name;
};

struct GroupsStudentsBinding {
  uint32_t student_id;
  uint32_t group_id;
};
```

Их необходимо объединить в один массив групп:

``` cpp
struct GroupUserRepr {
  std::string name;
  std::vector<StudentsRepr> members;
};

// где

struct StudentRepr {
  std::string name;
  std::vector<Rating> ratings;
};

// и

struct Rating {
  std::string subject;
  uint8_t rating;
};
```

Прототип:

``` cpp
std::vector<GroupUserRepr> GroupsRequestAssemble(
  const std::vector<StudentDatabaseRepr>& db_students,
  const std::vector<StudentRatingsDatabaseRepr>& db_ratings,
  const std::vector<GroupsDatabaseRepr>& db_groups,
  const std::vector<GroupsStudentsBinding>& db_groups_students
);
```


