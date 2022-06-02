#include "todo.h"
#include <qmap.h>
#include <QStackedWidget>
#include <QComboBox>
#include <QLabel>
#include <QScrollArea>

todo::todo(QWidget *parent)
    : QMainWindow(parent)
{
    mainWindow = new QWidget();
    mainWindow->setWindowTitle("ToDo App");
    mainWindow->setGeometry(1000, 1000, 500, 500);

    QString labelStyle = "font-weight: bold;" "color: darkgrey;" "font-size: 35px;" "font: Arial;";
    label = new QLabel("todos");
    label->setStyleSheet(labelStyle);
    label->setAlignment(Qt::AlignHCenter);

    QString searchBoxStyle = "background:white;" "color:grey;";
    searchBox = new QLineEdit("What needs to be done?");
    searchBox->setStyleSheet(searchBoxStyle);

    QString buttonstyle = ":hover{background:blue;}" ":pressed{background:red;}";
    button1 = new QPushButton("All");
    button1->setStyleSheet(buttonstyle);

    button2 = new QPushButton("Active");
    button2->setStyleSheet(buttonstyle);

    button3 = new QPushButton("Completed");
    button3->setStyleSheet(buttonstyle);

    label2 = new QLabel("task left");
//    QString text = "You have not created a task yet..";
//    textedit = new QTextEdit();
//    textedit->setText(text);

//    QGridLayout *layout = new QGridLayout ();
    buttonList = new QListWidgetItem();
    groupBox = new QGroupBox();

    hlayout = new QHBoxLayout();
    vlayout = new QVBoxLayout();

    QScrollArea *scrollwindows = new QScrollArea;
    firstlayout = new QVBoxLayout;
    scrollwindows->setLayout(firstlayout);
    scrollwindows->setVerticalScrollBarPolicy (Qt::ScrollBarAsNeeded);
    QVBoxLayout *temp = new QVBoxLayout;
    temp->addWidget(scrollwindows);
    secondlayout = new QVBoxLayout;
    thirdlayout = new QVBoxLayout;

    firstPageWidget = new QWidget;
    secondPageWidget = new QWidget;
    thirdPageWidget = new QWidget;

    firstPageWidget->setLayout(temp);
    QLabel*l = new QLabel("Test");
    firstlayout->addWidget(l);

    secondPageWidget->setLayout(secondlayout);
    thirdPageWidget->setLayout(thirdlayout);

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(firstPageWidget);
    stackedWidget->addWidget(secondPageWidget);
    stackedWidget->addWidget(thirdPageWidget);

    hlayout->addWidget(label2);
    hlayout->addWidget(button1);
    hlayout->addWidget(button2);
    hlayout->addWidget(button3);

    vlayout->addWidget(label);
    vlayout->addWidget(searchBox);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(stackedWidget);

    connect (searchBox, SIGNAL(returnPressed()), this, SLOT(getText()));
    connect (button1, SIGNAL (pressed()), this, SLOT(button1clicked()));
    connect (button2, SIGNAL (pressed()), this, SLOT(button2clicked()));
    connect (button3, SIGNAL (pressed()), this, SLOT(button3clicked()));

    mainWindow->setLayout(vlayout);
}

todo::~todo()
{
}

void todo::show()
{
    mainWindow->show();
}

void todo::getText()
{
    QString text = searchBox->text();
    insertText(text);
}


void todo::insertText(QString text)
{
    QRadioButton *tempBtn = new QRadioButton(text);
    firstlayout->addWidget(tempBtn);
}

void todo::button1clicked()
{
    stackedWidget->setCurrentIndex(0);
}

void todo::button2clicked()
{
    stackedWidget->setCurrentIndex(1);
}

void todo::button3clicked()
{
    stackedWidget->setCurrentIndex(2);
}

