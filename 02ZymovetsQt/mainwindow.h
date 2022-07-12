#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "graphics.h"
#include "InstructionShower.h"

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
    bool increment_graphics_scale();
    bool decrement_graphics_scale();
    void connect_action_to_tool(QAction*, const Graphics::Tool);
    void connect_all_actions_to_slots();
    void save_graphics();
    void save_as_graphics();
    void load_graphics();
    void show_instruction();
    void change_pen_size();
private:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
private:
    Ui::MainWindow *ui;
    Graphics* _graphics;
    QAction* _checkedAction;
    qint32 _graphicsLogScale;
    bool _hasBeenSaved;
    QString* _savedPath;
    InstructionShower* shower;
private:
    static const qreal ZOOM_SCALE_FACTOR;
    static const qint32 MAX_GRAPHICS_LOGSCALE;
    static const qint32 MIN_GRAPHICS_LOGSCALE;
    static const QString FILE_FILTERS;
};
#endif // MAINWINDOW_H
