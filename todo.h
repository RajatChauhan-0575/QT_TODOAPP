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
        QMap<QRadioButton*, bool> taskList;
        QListWidgetItem *buttonList;
        QGroupBox *groupBox;
        QList<QRadioButton*> currentList;
        QWidget *firstPageWidget;
        QWidget *secondPageWidget;
        QWidget *thirdPageWidget;
        QVBoxLayout *firstlayout;
        QVBoxLayout *secondlayout;
        QVBoxLayout *thirdlayout;
        QStackedWidget *stackedWidget;
        int val = 0;

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
};
#endif // TODO_H
