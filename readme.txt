Сборка проекта для MSVS:

1) Установка и сборка boost (http://www.boost.org/users/download/)
2) В настройках проекта указать актуальный путь до boost (Проект->Свойства->Каталоги VC++)
3) Собрать jemalloc (Thirdparty)
	а) Установить cygwin (https://cygwin.com/install.html) с компонентами: 
		- autoconf
		- autogen
		- grep
		- gawk
		- sed
		- bison
		- flex
	b) Добавить путь до cygwin\bin в переменные среды
	с) Запусть консоль разработчика (command promt vs), перейти в директорию jemalloc 
	d) Выполнить sh -c "CC=cl ./autogen.sh"
	e) Собрать проект msvc\jemalloc_vc2015.sln
	f) Поместить dll и рядом с ней сгененрированные файлы в Thirdparty\Lib
4) Запустить сборку fptl
