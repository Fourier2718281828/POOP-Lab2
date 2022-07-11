#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>


#include <QDebug>

using Tool = Graphics::Tool;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _graphics(new Graphics(centralWidget())),
      _checkedAction(nullptr)
{
    ui->setupUi(this);

    qDebug() << (centralWidget()->layout() == nullptr);
    centralWidget()->layout()->addWidget(_graphics);
    connect_all_actions_to_tools();
}

MainWindow::~MainWindow()
{
    delete ui;
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

/*void MainWindow::set_actions_checkable()
{
    ui->actionCircle->setCheckable(true);
    ui->actionDraw->setCheckable(true);
    ui->actionEllipse->setCheckable(true);
    ui->actionLine->setCheckable(true);
    ui->actionPolygon->setCheckable(true);
    ui->actionRectangle->setCheckable(true);
    ui->actionRhombus->setCheckable(true);
    ui->actionTriangle->setCheckable(true);
}*/
