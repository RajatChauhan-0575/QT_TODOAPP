#include "todo.h"
#include <qmap.h>
#include <QStackedWidget>
#include <QComboBox>
#include <QLabel>
#include <QScrollArea>
#include <windows.h>

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

    QString searchBoxStyle = "background:white;" "color:grey;"; // change name
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
    pixmap.load("C:/Personal/Learnings/QT/QT_TODOAPP/icons/icons8-edit-30.png");
     //pixmap.load("C:/Personal/Learnings/QT/QT_TODOAPP/icons/icons8-edit.gif");//
    ButtonIcon.addPixmap(pixmap);
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

    widgetmap.insert (0, all);
    widgetmap.insert (1, active);
    widgetmap.insert (2, completed);

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
    QListWidgetItem *wItemAll = new QListWidgetItem(text);
    wItemAll->setFlags(Qt::NoItemFlags);
    wItemAll->setTextColor(Qt::black);
    wItemAll->setCheckState(Qt::Unchecked);
    all->addItem(wItemAll);

    QListWidgetItem *wItemAct = new QListWidgetItem();
    QHBoxLayout *tmpLayout = new QHBoxLayout();
    QRadioButton *tmpRbtn = new QRadioButton();
    QLabel *tmpLabel = new QLabel(text);
    QPushButton *tmpbtn = new QPushButton();
    tmpbtn->setIcon(ButtonIcon);
    QWidget *tmpWgt = new QWidget();
    tmpLayout->addWidget(tmpRbtn);
    tmpLayout->addWidget(tmpLabel);
    tmpLayout->addWidget(tmpbtn);
    tmpLayout->setSizeConstraint(QLayout::SetMaximumSize);
    tmpWgt->setLayout(tmpLayout);
    wItemAct->setSizeHint(tmpWgt->sizeHint());
    wItemAct->setFlags(Qt::NoItemFlags);
    btnwgtitm.insert(tmpbtn, wItemAct);
    wgtimlay.insert(wItemAct, tmpLayout);
    rdwgtitm.insert(tmpRbtn, wItemAct);
    rdwgt.insert(tmpRbtn, tmpWgt);
    active->addItem(wItemAct);
    active->setItemWidget(wItemAct, tmpWgt);
    connect (tmpbtn, &QPushButton::pressed, this, &todo::editTask);
    connect (tmpRbtn, &QRadioButton::clicked, this, &todo::markCompleted);

    count++;
    label2->setText(QString::number(count) + " task left");
    QPushButton* btn = tmpLayout->findChild<QPushButton*> (QString("Edit"));
    auto idx = tmpLayout->indexOf(btn);
    qDebug() << "idx of Edit " << idx;

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
    auto rdbtn = dynamic_cast<QRadioButton *> (sender());
    QListWidgetItem * wdgtitem = rdwgtitm.value(rdbtn);
    QWidget *wgt = rdwgt.value(rdbtn);


    int row = active->row(wdgtitem);
    auto item = active->takeItem(row);

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

void todo::editTask()
{
    auto btn = dynamic_cast<QPushButton *> (sender());
    QListWidgetItem * wdgtitem = btnwgtitm.value(btn);
    QHBoxLayout * layout = wgtimlay.value(wdgtitem);
    QPushButton *btnwgt = dynamic_cast <QPushButton *> (layout->itemAt(2)->widget());
    QLabel *wgt = dynamic_cast <QLabel *> (layout->itemAt(1)->widget());
    QString txt = wgt->text();

    QLineEdit *temp = new QLineEdit(txt);
    QPushButton *delbtn = new QPushButton("Delete");
    delbtnwgtitm.insert(delbtn, wdgtitem);

    connect (delbtn, &QPushButton::pressed, this, &todo::deleteTask);
    txtlay.insert(temp, layout);
    connect (temp, &QLineEdit::returnPressed, this, &todo::saveeditTask);
    btnwgtitm.remove(btn);


    auto idx = layout->indexOf(wgt);
    layout->insertWidget(idx, temp);
    layout->removeWidget(wgt);
    wgt->deleteLater();

    idx = layout->indexOf(btnwgt);
    layout->insertWidget(idx, delbtn);
    qDebug() << "button idx" << idx;
    layout->removeWidget(btnwgt);
    btnwgt->deleteLater();

    qDebug () << "Count " << layout->count();
}

void todo::deleteTask()
{
    auto btn = dynamic_cast<QPushButton *> (sender());
    QListWidgetItem * wdgtitem = delbtnwgtitm.value(btn);
    auto idx = stackedWidget->currentIndex();
    qDebug() << "Index" <<idx;
    auto lstwgt = widgetmap.value(idx);
    auto rownum = lstwgt->row(wdgtitem);
    qDebug() << "row" <<rownum;
    lstwgt->takeItem(rownum);

    count--;
    label2->setText(QString::number(count) + " task left");
}

void todo::saveeditTask()
{
    auto lineedit = dynamic_cast<QLineEdit *> (sender());
    qDebug() << "inside saveeditTask";
    QHBoxLayout * layout = txtlay.value(lineedit);
    QLabel *label = new QLabel(lineedit->text());
    auto idx = layout->indexOf(lineedit);
    layout->insertWidget(idx, label);
    layout->removeWidget(lineedit);
    txtlay.remove (lineedit);
    lineedit->deleteLater();

    qDebug () << "Cound inside saveditTask "<< layout->count();
    idx = 2; // get this value later
    auto item = layout->itemAt(idx)->widget();
    QPushButton * delbtn = dynamic_cast <QPushButton *> (item);
    QPushButton *edtbtn = new QPushButton();
    edtbtn->setIcon(ButtonIcon);
    layout->insertWidget(idx, edtbtn);
    layout->removeWidget(item);
    btnwgtitm.insert(edtbtn, delbtnwgtitm.value(delbtn));
    connect (edtbtn, &QPushButton::pressed, this, &todo::editTask);
    delbtnwgtitm.remove(delbtn);
    item->deleteLater();
}
