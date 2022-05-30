#ifndef TODO_H
#define TODO_H

#include <QMainWindow>

class todo : public QMainWindow
{
    Q_OBJECT

public:
    todo(QWidget *parent = nullptr);
    ~todo();

    void show();

private:
        QWidget *mainWindow;
};
#endif // TODO_H
