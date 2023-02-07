# KeyParser - Фреймворк для работы с входными параметрами приложения C++

## Содержание

    1. Общие сведения
    2. Использование
      2.1 Сборка и подключение динамической библиотеки
      2.2 Использование и функционал фреймворка
      2.3 Примеры кода
    3. Дальнейшая разработка

---
## Общие сведения
Фреймворк *KeyParser* позволяет настроить обработку поступающих параметров в приложение написанное на C++ через `argc` и `argv` переменные.

*KeyParser* поддерживает короткие и длинные имена ключей, вложенные ключи, имеет специальные функции обработки данных, такие как обработка данных, введенных без ключа.
*KeyParser* бесопасен по памяти (не требует дополнительного выделения или очистки памяти), обработка данных производится за счет простых функций и не требует написания виртуальных классов и методов к ним.
Также у *KeyParser* имеется система отслеживания пути возникновения исключений, позволяющая быстро понять причину возникновения ошибок в работе приложения.

Сборка проекта настроенна только для UNIX систем, сборку под Windows и MacOS следует настраивать самостоятельно.

В данном проекте представленны исходные код фреймворка (папка "lib") с необходимыми файлами для сборки и установки, а также пример использования фреймворка (папка "example").

---
## Использование

### Сборка и подключение динамической библиотеки



### Использование и функционал фреймворка
Для использования элементов *KeyParser* нужно подключить заголовочный файл `terminal.hpp`:

    #include <keyparser/terminal.hpp>

Все элементы Фреймворка расположены в пространстве имен `KP`. К использованию рекомендуются только два класса: `Terminal` и `Key`.

`Key` - класс, который хранит информацию о ключе и имеет необходимый функционал для его использовании в `Terminal`. Ниже представлен список методов и структур:

*Структуры:*
* enum State{E, S, L, A}

*Конструкторы:*
* explicit Key(const std::string& l_data)
* explicit Key(const char& s_data, const std::string& l_data = "")

*Методы:*
* State getState() const
* bool operator<(const Key& key) const
* char sname() const
* std::string lname() const
* static Key getNull()
* static Key getRoot()

`Terminal` - класс, который занимается разбором поступающих параметров и их обработкой в соответствии с настройкой соответствующих ключей. Ниже представлен список методов и структур:

*Конструкторы:*
* Terminal()
* Terminal(const Terminal& term)

*Методы:*
* Terminal& operator=(const Terminal& term)
* void setKey(Key key, void (*lnr)(Args) = nullptr)
* void delKey(Key key)
* void setRoot(void (*lnr)(Args))
* void delRoot()
* void setFinal(void (*lnr)(Args))
* void delFinal()
* void cleanBinds()
* void execute(int argc, char* argv[])
* void execute(Args input)

### Примеры кода

*Первый пример использования **KeyParser**:*

Данный пример позволяет создать изменить файл и сохранить изменненную копию.
В функции `main` происходит создание экземпляра класса `Terminal`, настройка обработчиков методами `setKey()` и `setRoot()` и запуск обработки данных методом `execute()`.
В качестве исполнителей были созданны методы `root()` и `write()`.

    #include <keyparser/terminal.hpp>
    #include <string>

    using namespace KP;

    std::string s_path, l_path;

    void root(Args opts) {
		if (opts.size() != 3) throw std::invalid_argument("Error");
		s_path = opts[1];
		l_path = opts[2];
	}

    void write(Args opts) {
        std::ifstream l_file(l_path), s_file(s_path);
        if (l_file.bad() || s_file.bad()) return;
        
        for (std::string i = l_file.get_line(); !l_file().eof(); i = l_file.get_line()) s_file << i << '\n';
        for (auto &i : opts) s_file << i << '\n';

        l_file.close();
        s_file.close();
    }

    int main(int argc, char *argv[]) {
        try {
            Terminal terminal;
            terminal.setRoot(root);
            terminal.setKey(Key('w', "write"), write);
            terminal.execute(argc, argv);
        }
        catch (std::invalid_argument e) {
            std::cout << e.what() << '\n';
        }

        return 0;
    }

Второй пример использования *KeyParser* представлен в папка "example", команды для его сборки уже включены в `get-opt.sh` файл.

---
## Дальнейшая разработка

В дальнейшем предролагается расширить возможность настройки обработки ключей, для снижения длины создаваемых запросов.
Предполагается расширить функционал `Terminal` с целью сокращения пользовательского кода при сохранении его функциональности.
Также следует провести рефакторинг, с целью ускорения рабочего процесса и удаления излишнего функционала.
