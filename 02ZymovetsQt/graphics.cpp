#include "graphics.h"
#include <QPainter>


Graphics::Graphics(QWidget *parent)
    : QWidget{parent},
      _selectedTool(Tool::NONE)
{

}

void Graphics::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    painter.drawLine(0, 0, width(), height());

    painter.end();
}
