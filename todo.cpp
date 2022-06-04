#include "todo.h"
#include <qmap.h>
#include <QStackedWidget>
#include <QComboBox>
#include <QLabel>
#include <QScrollArea>
#include <windows.h>
#include "styles.h"

todo::todo(QWidget *parent)
    : QMainWindow(parent)
{
    mainWindow = new QWidget();
    mainWindow->setWindowTitle("ToDo App");
    mainWindow->setGeometry(750, 750, 750, 750);

    headerlabel = new QLabel("todos");
    headerlabel->setStyleSheet(labelStyle);
    headerlabel->setAlignment(Qt::AlignHCenter);


    newTaskEdit = new QLineEdit();
    newTaskEdit->setPlaceholderText("What needs to be done?");
    newTaskEdit->setStyleSheet(newTaskEditStyle);

    allbutton = new QPushButton("All");
    allbutton->setStyleSheet(buttonstyle);

    activebutton = new QPushButton("Active");
    activebutton->setStyleSheet(buttonstyle);

    completedbutton = new QPushButton("Completed");
    completedbutton->setStyleSheet(buttonstyle);

    taskLeftlabel = new QLabel(QString::number(count) + " task left");
    pixmap.load("C:/Personal/Learnings/QT/QT_TODOAPP/icons/icons8-edit-30.png");
    ButtonIcon.addPixmap(pixmap);

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

    hlayout->addWidget(taskLeftlabel);
    hlayout->addWidget(allbutton);
    hlayout->addWidget(activebutton);
    hlayout->addWidget(completedbutton);

    vlayout->addWidget(headerlabel);
    vlayout->addWidget(newTaskEdit);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(stackedWidget);

    connect (newTaskEdit, SIGNAL(returnPressed()), this, SLOT(getText()));
    connect (allbutton, SIGNAL (pressed()), this, SLOT(button1clicked()));
    connect (activebutton, SIGNAL (pressed()), this, SLOT(button2clicked()));
    connect (completedbutton, SIGNAL (pressed()), this, SLOT(button3clicked()));

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
    QString text = newTaskEdit->text();
    insertTask(text);
}

void todo::updateCount(int count)
{
      taskLeftlabel->setText(QString::number(count) + " task left");
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

void todo::insertTask(QString text)
{
    QListWidgetItem *wItemAll = new QListWidgetItem(text);
    wItemAll->setFlags(Qt::NoItemFlags);
    wItemAll->setCheckState(Qt::Unchecked);
    all->addItem(wItemAll);

    QListWidgetItem *wItemAct = new QListWidgetItem();
    QHBoxLayout *tmpLayout = new QHBoxLayout();
    QCheckBox *tmpRbtn = new QCheckBox();
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
    updateCount(count);
    QPushButton* btn = tmpLayout->findChild<QPushButton*> (QString("Edit"));
    auto idx = tmpLayout->indexOf(btn);
    qDebug() << "idx of Edit " << idx;
}

void todo::markCompleted()
{
    auto rdbtn = dynamic_cast<QCheckBox *> (sender());
    QListWidgetItem * wdgtitem = rdwgtitm.value(rdbtn);
    rdwgt.value(rdbtn)->show();
    int row = active->row(wdgtitem);
    qDebug () << "row : " << row;
    QListWidgetItem * item = active->takeItem(row);

    completed->addItem(item);
//    completed->setItemWidget(item, wgt);
//    completed->

    count--;
    updateCount(count);
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
    updateCount(count);
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
    updateCount(count);
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

    qDebug () << "Count inside saveditTask "<< layout->count();
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
