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
    //void scale_graphics(const float);
    bool increment_graphics_scale();
    bool decrement_graphics_scale();
    void connect_action_to_tool(QAction*, const Graphics::Tool);
    void connect_all_actions_to_tools();
private:
    Ui::MainWindow *ui;
    Graphics* _graphics;
    QAction* _checkedAction;
    qint32 _graphicsLogScale;
private:
    static const qreal ZOOM_SCALE_FACTOR;
    static const qint32 MAX_GRAPHICS_LOGSCALE;
    static const qint32 MIN_GRAPHICS_LOGSCALE;
};
#endif // MAINWINDOW_H
