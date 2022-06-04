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
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QCheckBox>

class todo : public QMainWindow
{
    Q_OBJECT

private:
        QWidget *mainWindow;
        QLabel *headerlabel;
        QLineEdit *newTaskEdit;
        QPushButton *allbutton;
        QPushButton *activebutton;
        QPushButton *completedbutton;

        QLabel *taskLeftlabel;
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
        QList<QPushButton *> btnList;
        QMap<QPushButton *, QListWidgetItem *> btnwgtitm;
        QMap<QPushButton *, QListWidgetItem *> delbtnwgtitm;
        QMap<QListWidgetItem *, QHBoxLayout *> wgtimlay;
        QMap<QLineEdit *, QHBoxLayout *> txtlay;
        QMap<int, QListWidget *> widgetmap;
        QMap<QCheckBox *, QListWidgetItem *> rdwgtitm;
        QMap<QCheckBox *, QWidget*> rdwgt;
        QPixmap pixmap;
        QIcon ButtonIcon;
        int count = 0;

public :
    todo(QWidget *parent = nullptr);
    ~todo();
    void show();
    void insertTask(QString);
    void updateCount(int);

public slots:
    void getText();
    void button1clicked();
    void button2clicked();
    void button3clicked();
    void markCompleted();
    void markActive();
    void editTask();
    void deleteTask();
    void saveeditTask();
};
#endif // TODO_H
