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

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::getMessage);
    timer->start(10);

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

void MainWindow::load()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open System Exclusive files"), ".",
                                                    tr("SysEx files (*.syx)"));
    if (!fileName.isEmpty()) loadFile(fileName);
}

bool MainWindow::loadFile(const QString& fileName)
{
    if (!m_dx21.readFile(fileName.toStdString())) {
        return false;
    }
    return true;
}

void MainWindow::getMessage()
{
    m_dx21.getMessage();
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

/*void MainWindow::sendMessage()
{
    m_dx21.sendMessage();
}

void MainWindow::sendSingle()
{
    m_dx21.sendSingle();
}

void MainWindow::sendBulk()
{
    m_dx21.sendMessage();
}

void MainWindow::requestSingle()
{
    m_dx21.requestSingle();
}

void MainWindow::requestBulk()
{
    m_dx21.requestBulk();
}
*/

void MainWindow::createActions()
{
    newAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew),
                         tr("&New"), this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen),
                          tr("&Load..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    //connect(openAction, &QAction::triggered, this, &MainWindow::open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(load()));

    saveAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave),
                          tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the document to disk"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    sendSingleAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew),
                            tr("&Send Single Voice"), this);
    //sendSingleAction->setShortcuts(QKeySequence::New);
    sendSingleAction->setStatusTip(tr("Send a Single Voice"));
    //connect(sendSingleAction, &QAction::triggered, this, &MainWindow::sendSingle);

    sendBulkAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew),
                            tr("Send &Bulk Voices"), this);
    //sendBulkAction->setShortcuts(QKeySequence::New);
    sendBulkAction->setStatusTip(tr("Send Bulk Voices"));
    //connect(sendBulkAction, &QAction::triggered, this, &MainWindow::sendBulk);

    requestSingleAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew),
                            tr("Request Single Voice"), this);
    //requestSingleAction->setShortcuts(QKeySequence::New);
    requestSingleAction->setStatusTip(tr("Request a Single Voice"));
    //connect(requestSingleAction, &QAction::triggered, this, &MainWindow::requestSingle);

    requestBulkAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew),
                            tr("&Request Bulk Voices"), this);
    //requestBulkAction->setShortcuts(QKeySequence::New);
    requestBulkAction->setStatusTip(tr("Request Bulk Voices"));
    //connect(requestBulkAction, &QAction::triggered, this, &MainWindow::requestBulk);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    midiMenu = menuBar()->addMenu(tr("&Midi"));
    midiMenu->addAction(sendSingleAction);
    midiMenu->addAction(sendBulkAction);
    midiMenu->addAction(requestSingleAction);
    midiMenu->addAction(requestBulkAction);
}
