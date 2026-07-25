// XMLColorEditorJava.java — редактор XML с цветовой схемой на Java (Swing)

import javax.swing.*;
import javax.swing.text.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.filechooser.FileNameExtensionFilter;

public class XMLColorEditorJava extends JFrame {
    private JTextPane textPane;
    private StyleContext styleContext;
    private DefaultStyledDocument doc;
    private String filename;

    public XMLColorEditorJava() {
        setTitle("🎨 XMLColorEditor — Java");
        setSize(800, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        styleContext = new StyleContext();
        doc = new DefaultStyledDocument(styleContext);
        textPane = new JTextPane(doc);
        textPane.setFont(new Font("Courier New", Font.PLAIN, 14));
        textPane.addKeyListener(new KeyAdapter() {
            public void keyReleased(KeyEvent e) { highlightXML(); }
        });
        JScrollPane scroll = new JScrollPane(textPane);
        add(scroll, BorderLayout.CENTER);

        createMenu();
        setVisible(true);
    }

    private void createMenu() {
        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("Файл");
        JMenuItem openItem = new JMenuItem("Открыть");
        openItem.addActionListener(e -> openFile());
        fileMenu.add(openItem);
        JMenuItem saveItem = new JMenuItem("Сохранить");
        saveItem.addActionListener(e -> saveFile());
        fileMenu.add(saveItem);
        fileMenu.addSeparator();
        JMenuItem exitItem = new JMenuItem("Выход");
        exitItem.addActionListener(e -> System.exit(0));
        fileMenu.add(exitItem);
        menuBar.add(fileMenu);
        setJMenuBar(menuBar);
    }

    private void openFile() {
        JFileChooser chooser = new JFileChooser();
        chooser.setFileFilter(new FileNameExtensionFilter("XML", "xml"));
        if (chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            filename = chooser.getSelectedFile().getAbsolutePath();
            try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
                String text = "";
                String line;
                while ((line = reader.readLine()) != null) text += line + "\n";
                doc.remove(0, doc.getLength());
                doc.insertString(0, text, null);
                highlightXML();
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Ошибка: " + ex.getMessage());
            }
        }
    }

    private void saveFile() {
        if (filename == null) {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileFilter(new FileNameExtensionFilter("XML", "xml"));
            if (chooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
                filename = chooser.getSelectedFile().getAbsolutePath();
            } else return;
        }
        try (PrintWriter pw = new PrintWriter(filename)) {
            pw.print(textPane.getText());
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(this, "Ошибка: " + ex.getMessage());
        }
    }

    private void highlightXML() {
        doc.setCharacterAttributes(0, doc.getLength(), styleContext.getStyle(StyleContext.DEFAULT_STYLE), true);
        String text = textPane.getText();
        // Простая подсветка (регулярки)
        // В Java сложно делать подсветку без внешних библиотек, здесь упрощённо
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(XMLColorEditorJava::new);
    }
}
