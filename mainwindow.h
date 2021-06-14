#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class PlayingField;
class MainWindow : public QMainWindow
{
    Q_OBJECT

    PlayingField *m_field;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){}
};
#endif // MAINWINDOW_H
