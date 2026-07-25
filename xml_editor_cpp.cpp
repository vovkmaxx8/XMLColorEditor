// xml_editor_cpp.cpp — редактор XML с цветовой схемой на C++ (Qt)

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QFile>
#include <QFileDialog>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QTextStream>
#include <QRegExp>

class XMLHighlighter : public QSyntaxHighlighter {
public:
    XMLHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
        // Теги
        QTextCharFormat tagFormat;
        tagFormat.setForeground(Qt::green);
        highlightRules.append({QRegExp("<[^>]*>"), tagFormat});
        // Атрибуты
        QTextCharFormat attrFormat;
        attrFormat.setForeground(Qt::yellow);
        highlightRules.append({QRegExp("\\s+[a-zA-Z-]+="), attrFormat});
        // Значения
        QTextCharFormat valueFormat;
        valueFormat.setForeground(Qt::red);
        highlightRules.append({QRegExp("\"[^\"]*\""), valueFormat});
        // Комментарии
        QTextCharFormat commentFormat;
        commentFormat.setForeground(Qt::gray);
        highlightRules.append({QRegExp("<!--[^>]*-->"), commentFormat});
    }

protected:
    void highlightBlock(const QString &text) override {
        for (const Rule &rule : highlightRules) {
            int index = text.indexOf(rule.pattern);
            while (index >= 0) {
                int length = rule.pattern.matchedLength();
                setFormat(index, length, rule.format);
                index = text.indexOf(rule.pattern, index + length);
            }
        }
    }

private:
    struct Rule {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QList<Rule> highlightRules;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("🎨 XMLColorEditor — C++");
        resize(800, 600);

        textEdit = new QTextEdit(this);
        textEdit->setFont(QFont("Courier", 12));
        setCentralWidget(textEdit);

        new XMLHighlighter(textEdit->document());

        createMenu();
        statusBar()->showMessage("Готов");
    }

private slots:
    void openFile() {
        QString path = QFileDialog::getOpenFileName(this, "Открыть XML", "", "XML (*.xml)");
        if (!path.isEmpty()) {
            QFile file(path);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                textEdit->setPlainText(in.readAll());
                file.close();
                statusBar()->showMessage("Открыт: " + path);
            }
        }
    }

    void saveFile() {
        QString path = QFileDialog::getSaveFileName(this, "Сохранить XML", "", "XML (*.xml)");
        if (!path.isEmpty()) {
            QFile file(path);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << textEdit->toPlainText();
                file.close();
                statusBar()->showMessage("Сохранён: " + path);
            }
        }
    }

private:
    QTextEdit *textEdit;

    void createMenu() {
        QMenu *fileMenu = menuBar()->addMenu("Файл");
        QAction *openAction = new QAction("Открыть", this);
        connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
        fileMenu->addAction(openAction);
        QAction *saveAction = new QAction("Сохранить", this);
        connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
        fileMenu->addAction(saveAction);
        fileMenu->addSeparator();
        QAction *exitAction = new QAction("Выход", this);
        connect(exitAction, &QAction::triggered, this, &QWidget::close);
        fileMenu->addAction(exitAction);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}

#include "xml_editor_cpp.moc"
