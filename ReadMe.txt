Для генерации модулей парсера и токенайзера необходимо:

- установить GnuBison (в папке Tools)
- установить msys
- скопировать flex.exe и msys-regex-1.dll в bin в папке msys.

Для сборки проекта необходимо:

скачать и cобрать boost (www.boost.org).
Собрать сборщик мусора (External/gc/gc-7.0, запустить BuildRelease и BuildDebug).

Также должны быть прописаны следубщие переменные окружения:

BOOST_PATH = директория с бустом
FPTL_INTERP_PATH = корневая директория (c ReadMe.txt)
FLEX_PATH = директория с flex.exe
BISON_PATH = директория с bison.exe

Для оптимальной интерпретатора установать в настройках проекта следующие переменные окружения:

GC_MAXIMUM_HEAP_SIZE=512000000
GC_INITIAL_HEAP_SIZE=8000000