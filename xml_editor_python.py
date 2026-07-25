# xml_editor_python.py — редактор XML с цветовой схемой на Python (Tkinter)

import tkinter as tk
from tkinter import filedialog, messagebox, scrolledtext
import re

class XMLHighlighter:
    def __init__(self, text_widget):
        self.text = text_widget
        self.setup_tags()

    def setup_tags(self):
        self.text.tag_configure("tag", foreground="green")
        self.text.tag_configure("attr", foreground="yellow")
        self.text.tag_configure("value", foreground="red")
        self.text.tag_configure("comment", foreground="gray")
        self.text.tag_configure("text", foreground="white")

    def highlight(self, event=None):
        self.text.tag_remove("tag", "1.0", tk.END)
        self.text.tag_remove("attr", "1.0", tk.END)
        self.text.tag_remove("value", "1.0", tk.END)
        self.text.tag_remove("comment", "1.0", tk.END)
        self.text.tag_remove("text", "1.0", tk.END)

        content = self.text.get("1.0", tk.END)
        # Простейшая подсветка
        # Теги
        for match in re.finditer(r'<[^>/]+>', content):
            start = self.text.index(f"1.0+{match.start()}c")
            end = self.text.index(f"1.0+{match.end()}c")
            self.text.tag_add("tag", start, end)
        # Атрибуты (упрощённо)
        for match in re.finditer(r'\s+([a-zA-Z-]+)=', content):
            start = self.text.index(f"1.0+{match.start(1)}c")
            end = self.text.index(f"1.0+{match.end(1)}c")
            self.text.tag_add("attr", start, end)
        # Значения атрибутов
        for match in re.finditer(r'"[^"]*"', content):
            start = self.text.index(f"1.0+{match.start()}c")
            end = self.text.index(f"1.0+{match.end()}c")
            self.text.tag_add("value", start, end)
        # Комментарии
        for match in re.finditer(r'<!--.*?-->', content, re.DOTALL):
            start = self.text.index(f"1.0+{match.start()}c")
            end = self.text.index(f"1.0+{match.end()}c")
            self.text.tag_add("comment", start, end)

class XMLColorEditor:
    def __init__(self, root):
        self.root = root
        self.root.title("🎨 XMLColorEditor — Python")
        self.root.geometry("800x600")
        self.filename = None

        # Текстовое поле с прокруткой
        self.text = scrolledtext.ScrolledText(root, font=("Courier", 12), bg="black", fg="white")
        self.text.pack(fill=tk.BOTH, expand=True)

        # Подсветка
        self.highlighter = XMLHighlighter(self.text)
        self.text.bind("<KeyRelease>", self.highlighter.highlight)

        # Меню
        menubar = tk.Menu(root)
        file_menu = tk.Menu(menubar, tearoff=0)
        file_menu.add_command(label="Открыть", command=self.open_file)
        file_menu.add_command(label="Сохранить", command=self.save_file)
        file_menu.add_separator()
        file_menu.add_command(label="Выход", command=root.quit)
        menubar.add_cascade(label="Файл", menu=file_menu)
        root.config(menu=menubar)

        # Статус
        self.status = tk.Label(root, text="Готов", anchor=tk.W)
        self.status.pack(fill=tk.X)

    def open_file(self):
        path = filedialog.askopenfilename(filetypes=[("XML", "*.xml")])
        if path:
            self.filename = path
            with open(path, 'r') as f:
                content = f.read()
            self.text.delete("1.0", tk.END)
            self.text.insert("1.0", content)
            self.highlighter.highlight()
            self.status.config(text=f"Открыт: {path}")

    def save_file(self):
        if not self.filename:
            self.filename = filedialog.asksaveasfilename(defaultextension=".xml", filetypes=[("XML", "*.xml")])
        if self.filename:
            with open(self.filename, 'w') as f:
                f.write(self.text.get("1.0", tk.END))
            self.status.config(text=f"Сохранён: {self.filename}")

if __name__ == "__main__":
    root = tk.Tk()
    app = XMLColorEditor(root)
    root.mainloop()
