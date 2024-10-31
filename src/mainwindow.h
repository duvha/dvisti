#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class QAction;
class QMenu;

#include "DX21/dx21.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createActions();
    void createMenus();
    bool loadFile(const QString& fileName);

    QAction* openAction;
    QAction* exitAction;
    QMenu* fileMenu;
};
#endif // MAINWINDOW_H
