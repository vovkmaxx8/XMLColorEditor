// XMLColorEditorCSharp.cs — редактор XML с цветовой схемой на C# (WPF)

using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Media;
using Microsoft.Win32;

namespace XMLColorEditorCSharp
{
    public partial class MainWindow : Window
    {
        private string filename;

        public MainWindow()
        {
            InitializeComponent();
            Title = "🎨 XMLColorEditor — C#";
            Width = 800;
            Height = 600;
            CreateUI();
        }

        private void CreateUI()
        {
            var grid = new Grid();
            var menu = new Menu();
            var fileMenu = new MenuItem { Header = "Файл" };
            var openItem = new MenuItem { Header = "Открыть" };
            openItem.Click += (s, e) => OpenFile();
            fileMenu.Items.Add(openItem);
            var saveItem = new MenuItem { Header = "Сохранить" };
            saveItem.Click += (s, e) => SaveFile();
            fileMenu.Items.Add(saveItem);
            fileMenu.Items.Add(new Separator());
            var exitItem = new MenuItem { Header = "Выход" };
            exitItem.Click += (s, e) => Close();
            fileMenu.Items.Add(exitItem);
            menu.Items.Add(fileMenu);
            grid.Children.Add(menu);

            var richTextBox = new RichTextBox();
            richTextBox.FontFamily = new FontFamily("Courier New");
            richTextBox.FontSize = 14;
            richTextBox.TextChanged += (s, e) => HighlightXML(richTextBox);
            grid.Children.Add(richTextBox);
            Content = grid;
        }

        private void OpenFile()
        {
            var dialog = new OpenFileDialog { Filter = "XML|*.xml" };
            if (dialog.ShowDialog() == true)
            {
                filename = dialog.FileName;
                string content = File.ReadAllText(filename);
                var flowDoc = new FlowDocument();
                var paragraph = new Paragraph(new Run(content));
                flowDoc.Blocks.Add(paragraph);
                // В реальности нужна подсветка, упрощённо
                (Content as Grid).Children[1] = new RichTextBox { Document = flowDoc };
            }
        }

        private void SaveFile()
        {
            if (filename == null)
            {
                var dialog = new SaveFileDialog { Filter = "XML|*.xml" };
                if (dialog.ShowDialog() != true) return;
                filename = dialog.FileName;
            }
            var rtb = (Content as Grid).Children[1] as RichTextBox;
            File.WriteAllText(filename, new TextRange(rtb.Document.ContentStart, rtb.Document.ContentEnd).Text);
        }

        private void HighlightXML(RichTextBox rtb)
        {
            // Упрощённо: не реализовано
        }
    }
}
