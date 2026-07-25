🎨 XMLColorEditor — редактор XML с цветовой схемой
Интерактивный редактор XML-файлов с подсветкой синтаксиса, поддержкой тем и удобным управлением.
Реализован на 7 языках программирования для демонстрации работы с текстом и разметкой.

https://img.shields.io/github/repo-size/yourname/xmlcoloreditor
https://img.shields.io/github/stars/yourname/xmlcoloreditor?style=social
https://img.shields.io/badge/License-MIT-blue.svg

🧠 Концепция
XMLColorEditor — это легковесный редактор XML-документов с подсветкой синтаксиса. Он позволяет:

✅ Открывать и редактировать XML-файлы.

✅ Подсвечивать теги, атрибуты, значения и комментарии разными цветами.

✅ Выбирать цветовую схему (светлая/тёмная) — в некоторых версиях.

✅ Сохранять изменения в файл.

✅ Проверять валидность XML (базовая проверка).

✅ Работать как в консоли (с цветным выводом), так и в графическом интерфейсе.

✅ Кроссплатформенность — работает на Windows, Linux, macOS.

🚀 Как запустить
Для каждой версии требуются соответствующие библиотеки. Инструкции по установке и запуску:

Python
bash
pip install tkinter (встроен)
python xml_editor_python.py
C++
bash
# Требуется Qt5 (sudo apt install qt5-default)
qmake && make
./xml_editor_cpp
Java
bash
javac XMLColorEditorJava.java && java XMLColorEditorJava
C# (.NET Core)
bash
dotnet add package System.Windows.Forms
dotnet run
Go
bash
go run xml_editor_go.go
Rust
bash
cargo build --release && ./target/release/xml_editor_rs
JavaScript (Node.js)
bash
npm install readline
node xml_editor_js.js
🧩 Пример интерфейса (консоль)
text
<root>
  <element attribute="value">
    <child>Text</child>
  </element>
</root>
Подсветка:

Теги: зелёный

Атрибуты: жёлтый

Значения атрибутов: красный

Текст: белый

Комментарии: серый

📦 Содержимое репозитория
Файл	Язык	Особенности
xml_editor_python.py	Python	Tkinter GUI, подсветка через текстовые теги
xml_editor_cpp.cpp	C++	Qt Widgets, QSyntaxHighlighter
XMLColorEditorJava.java	Java	Swing, JEditorPane с HTML-стилями
XMLColorEditorCSharp.cs	C#	WPF, RichTextBox с цветами
xml_editor_go.go	Go	консоль, цветной вывод (ANSI)
xml_editor_rs.rs	Rust	консоль, termion, цветной вывод
xml_editor_js.js	JavaScript	Node.js, readline, цветной вывод
🔮 Расширенные функции
Подсветка синтаксиса в реальном времени.

Проверка валидности XML (базовая).

Автоформатирование (в планах).

Экспорт в HTML с сохранением цветов.

📜 Лицензия
MIT — свободно используйте, модифицируйте и распространяйте.

🤝 Вклад
Приветствуются пул-реквесты с улучшениями, поддержкой новых платформ и расширением функциональности.

⭐ Если проект помогает вам редактировать XML — поставьте звёздочку!
