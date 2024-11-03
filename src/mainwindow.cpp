#include <QtWidgets>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QString>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("DX21"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("Dvisti"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

MainWindow::~MainWindow()
{

}

void MainWindow::newFile()
{
    infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open System Exclusive files"), ".",
                                                    tr("SysEx files (*.syx)"));
    if (!fileName.isEmpty()) loadFile(fileName); //m_dx21.readFile(fileName.toStdString());
}

bool MainWindow::loadFile(const QString& fileName)
{
    if (!m_dx21.readFile(fileName.toStdString())) {
        return false;
    }

    return true;
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save System Exclusive files"), ".",
                                                    tr("SysEx files (*.syx)"));
    if (!fileName.isEmpty()) saveFile(fileName);
}

bool MainWindow::saveFile(const QString& fileName)
{
    if (!m_dx21.writeFile(fileName.toStdString())) {
        return false;
    }

    return true;
}

void MainWindow::createActions()
{
    newAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew),
                         tr("&New"), this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen),
                          tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    //connect(openAction, &QAction::triggered, this, &MainWindow::open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave),
                          tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the document to disk"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
}
