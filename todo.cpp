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
    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("What needs to be done?");
    searchBox->setStyleSheet(searchBoxStyle);

    QString buttonstyle = ":hover{background:blue;}" ":pressed{background:red;}";
    button1 = new QPushButton("All");
    button1->setStyleSheet(buttonstyle);

    button2 = new QPushButton("Active");
    button2->setStyleSheet(buttonstyle);

    button3 = new QPushButton("Completed");
    button3->setStyleSheet(buttonstyle);

    label2 = new QLabel(QString::number(count) + " task left");

//    QGridLayout *layout = new QGridLayout ();

    hlayout = new QHBoxLayout();
    vlayout = new QVBoxLayout();

    firstlayout = new QVBoxLayout;
    secondlayout = new QVBoxLayout;
    thirdlayout = new QVBoxLayout;

    all = new QListWidget;
    active = new QListWidget;
    completed = new QListWidget;

    firstPageWidget = new QWidget;
    secondPageWidget = new QWidget;
    thirdPageWidget = new QWidget;

    firstPageWidget->setLayout(firstlayout);
    firstlayout->addWidget(all);

    secondPageWidget->setLayout(secondlayout);
    secondlayout->addWidget(active);

    thirdPageWidget->setLayout(thirdlayout);
    thirdlayout->addWidget(completed);

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
    connect(active,&QListWidget::itemClicked,this,&todo::markCompleted);
    connect(completed,&QListWidget::itemClicked,this,&todo::markActive);

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
    QListWidgetItem *temp = new QListWidgetItem(text);
    QListWidgetItem *temp1 = new QListWidgetItem(text);
    temp->setFlags(Qt::NoItemFlags);
    temp->setTextColor(Qt::black);
    temp->setCheckState(Qt::Unchecked);
    temp1->setCheckState(Qt::Unchecked);
    all->addItem(temp);
    active->addItem(temp1);
    count++;
    label2->setText(QString::number(count) + " task left");
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

void todo::markCompleted()
{
     int row = active->currentRow();
     auto item = active->takeItem(row);
     item->setCheckState(Qt::Checked);
     QListWidgetItem * item1 = all->findItems(item->text(), Qt::MatchExactly)[0];
     item1->setCheckState(Qt::Checked);
     all->addItem(item1);
     completed->addItem(item);
     count--;
     label2->setText(QString::number(count) + " task left");
}

void todo::markActive()
{
    int row = completed->currentRow();
    auto item = completed->takeItem(row);
    item->setCheckState(Qt::Unchecked);
    QListWidgetItem * item1 = all->findItems(item->text(), Qt::MatchExactly)[0];
    item1->setCheckState(Qt::Unchecked);
    all->addItem(item1);
    active->addItem(item);
    count++;
    label2->setText(QString::number(count) + " task left");
}
