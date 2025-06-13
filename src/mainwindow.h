#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class QAction;
class QMenu;
class QLabel;
class QTimer;
//class QWidget; //?? needed?

#include "DX21/dx21.h"
#include "DX21/dx21_widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    //void open();
    void save(bool);
    void getMessage();
    void load();
    void saveSingle();
    void saveBulk();
    void sendSingle();
    void sendBulk();
    void requestSingle();
    void requestBulk();

private:
    void createActions();
    void createMenus();
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName, bool );

    dx21 m_dx21;

    QAction* openAction;
    QAction* newAction;
    QAction* saveSingleAction;
    QAction* saveBulkAction;
    QAction* exitAction;
    QAction* sendSingleAction;
    QAction* sendBulkAction;
    QAction* requestSingleAction;
    QAction* requestBulkAction;
    QMenu* fileMenu;
    QMenu* midiMenu;
    QLabel* infoLabel;
    QTimer* timer;
    dx21_widget* w;
};
#endif // MAINWINDOW_H
