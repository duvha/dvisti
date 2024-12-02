#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class QAction;
class QMenu;
class QLabel;
class QTimer;

#include "DX21/dx21.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    //void open();
    void save();
    void getMessage();
    void load();
    //void saveSingle();
    //void saveBulk();
    //void sendSingle();
    //void sendBulk();
    //void requestSingle();
    //void requestBulk();

private:
    void createActions();
    void createMenus();
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);

    dx21 m_dx21;

    QAction* openAction;
    QAction* newAction;
    QAction* saveAction;
    QAction* exitAction;
    QAction* sendSingleAction;
    QAction* sendBulkAction;
    QAction* requestSingleAction;
    QAction* requestBulkAction;
    QMenu* fileMenu;
    QMenu* midiMenu;
    QLabel* infoLabel;
    QTimer* timer;
};
#endif // MAINWINDOW_H
