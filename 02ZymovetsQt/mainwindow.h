#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "graphics.h"

#include<QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void connect_action_to_tool(QAction*, const Graphics::Tool);
    void connect_all_actions_to_tools();
private:
    Ui::MainWindow *ui;
    Graphics* _graphics;

    QAction* _checkedAction;
};
#endif // MAINWINDOW_H
