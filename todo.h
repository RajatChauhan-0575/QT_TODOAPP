#ifndef TODO_H
#define TODO_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QDebug>
#include <QObject>
#include <QMap>
#include <QRadioButton>
#include <QGroupBox>
#include <QList>
#include <QStackedWidget>
#include <QListWidget>

class todo : public QMainWindow
{
    Q_OBJECT

private:
        QWidget *mainWindow;
        QLabel *label;
        QLineEdit *searchBox;
        QPushButton *button1;
        QPushButton *button2;
        QPushButton *button3;
        QLabel *label2;
        QTextEdit *textedit;
        QHBoxLayout *hlayout;
        QVBoxLayout *vlayout;
        QWidget *firstPageWidget;
        QWidget *secondPageWidget;
        QWidget *thirdPageWidget;
        QVBoxLayout *firstlayout;
        QVBoxLayout *secondlayout;
        QVBoxLayout *thirdlayout;
        QStackedWidget *stackedWidget;
        QListWidget * all;
        QListWidget * active;
        QListWidget * completed;
        int count = 0;

public :
    todo(QWidget *parent = nullptr);
    ~todo();
    void show();
    void showText();
    void insertText(QString);

public slots:
    void getText();
    void button1clicked();
    void button2clicked();
    void button3clicked();
    void markCompleted();
    void markActive();
};
#endif // TODO_H
