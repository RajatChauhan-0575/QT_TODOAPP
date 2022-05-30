#include "todo.h"
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>

todo::todo(QWidget *parent)
    : QMainWindow(parent)
{
    mainWindow = new QWidget();
    mainWindow->setWindowTitle("ToDo App");
    mainWindow->setGeometry(1000, 1000, 500, 500);

    QString labelStyle = "font-weight: bold;" "color: darkgrey;" "font-size: 35px;" "font: Arial;";
    QLabel *label = new QLabel("todos");
    label->setStyleSheet(labelStyle);
    label->setAlignment(Qt::AlignHCenter);

    QString searchBoxStyle = "background:white;" "color:grey;";
    QLineEdit *searchBox = new QLineEdit("What needs to be done?");
    searchBox->setStyleSheet(searchBoxStyle);

    QString buttonstyle = ":hover{background:blue;}" ":pressed{background:red;}";
    QPushButton *button1 = new QPushButton("All");
    button1->setStyleSheet(buttonstyle);

    QPushButton *button2 = new QPushButton("Active");
    button2->setStyleSheet(buttonstyle);

    QPushButton *button3 = new QPushButton("Completed");
    button3->setStyleSheet(buttonstyle);

    QLabel *label2 = new QLabel("task left");
    QString text = "You have not created a task yet..";
    QTextEdit *textedit = new QTextEdit();
    textedit->setText(text);

    QGridLayout *layout = new QGridLayout ();
    QHBoxLayout *hlayout = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout();

    hlayout->addWidget(label2);
    hlayout->addWidget(button1);
    hlayout->addWidget(button2);
    hlayout->addWidget(button3);

    vlayout->addWidget(label);
    vlayout->addWidget(searchBox);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(textedit);
//       layout->addItem(hlayout, 0, 0, 1, 1);

//       mainWindow->setLayout(layout);
    mainWindow->setLayout(vlayout);
}

todo::~todo()
{
}

void todo::show()
{
    mainWindow->show();
}

