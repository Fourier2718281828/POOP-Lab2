#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>

using Tool = Graphics::Tool;

const qreal MainWindow::ZOOM_SCALE_FACTOR = 2.0;
const qint32 MainWindow::MAX_GRAPHICS_LOGSCALE = 3;
const qint32 MainWindow::MIN_GRAPHICS_LOGSCALE = -3;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _graphics(new Graphics(/*centralWidget()*/)),
      _checkedAction(nullptr),
      _graphicsLogScale(0)
{
    ui->setupUi(this);
    _graphics->setFixedSize(_graphics->size());
    QScrollArea* scrollArea = centralWidget()->findChildren<QScrollArea*>("scrollArea").first();
    scrollArea->setWidget(_graphics);
    //_graphics->setFixedSize(_graphics->size());
    connect_all_actions_to_tools();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::scale_graphics(const float factor)
{
    const QSize newSize = factor * _graphics->size();
    _graphics->setFixedSize(newSize);
}
*/

bool MainWindow::increment_graphics_scale()
{
    if(_graphicsLogScale == MAX_GRAPHICS_LOGSCALE)
    {
        return false;
    }

    ++_graphicsLogScale;
    //scale_graphics(ZOOM_SCALE_FACTOR);
    _graphics->scale(ZOOM_SCALE_FACTOR);
    return true;
}

bool MainWindow::decrement_graphics_scale()
{
    if(_graphicsLogScale == MIN_GRAPHICS_LOGSCALE)
    {
        return false;
    }

    --_graphicsLogScale;
    //scale_graphics(1 / ZOOM_SCALE_FACTOR);
    _graphics->scale(1 / ZOOM_SCALE_FACTOR);
    return true;
}

void MainWindow::connect_all_actions_to_tools()
{
    connect_action_to_tool(ui->actionDraw, Tool::PENCIL);
    connect_action_to_tool(ui->actionCircle, Tool::CIRCLE);
    connect_action_to_tool(ui->actionEllipse, Tool::ELLIPSE);
    connect_action_to_tool(ui->actionLine, Tool::LINE);
    connect_action_to_tool(ui->actionPolygon, Tool::POLYGON);
    connect_action_to_tool(ui->actionRectangle, Tool::RECTANGLE);
    connect_action_to_tool(ui->actionRhombus, Tool::RHOMBUS);
    connect_action_to_tool(ui->actionTriangle, Tool::TRIANGLE);

    connect(ui->actionZoom_in, &QAction::triggered,
            this, &MainWindow::increment_graphics_scale);
    connect(ui->actionZoom_out, &QAction::triggered,
            this, &MainWindow::decrement_graphics_scale);

    connect(ui->actionClear, &QAction::triggered,
            _graphics, &Graphics::clear);
}

void MainWindow::connect_action_to_tool(QAction* action, const Tool tool)
{
    auto _slot = [this, tool, action]
    {
        if(action == _checkedAction)
        {
            _graphics->deselect_tool();
            _checkedAction = nullptr;
        }
        else if(_checkedAction)
        {
            _checkedAction->setChecked(false);
            _checkedAction = action;
            _graphics->select_tool(tool);
        }
        else
        {
            _checkedAction = action;
            _graphics->select_tool(tool);
        }
    };

    connect(action, &QAction::triggered, _graphics, _slot);
}
