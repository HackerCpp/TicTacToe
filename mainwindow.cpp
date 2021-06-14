#include "mainwindow.h"
#include "playingfield.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_field = new PlayingField(this);
    setCentralWidget(m_field);
    resize(500,500);
}
