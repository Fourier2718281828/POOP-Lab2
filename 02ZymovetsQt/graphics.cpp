#include "graphics.h"
#include <QPainter>
#include <QMouseEvent>

using Tool = Graphics::Tool;

Graphics::Graphics(QWidget *parent)
    : QWidget{parent},
      _selectedTool(Tool::NONE),
      _canvas(size(), QImage::Format_RGB32),
      _phantomCanvas(nullptr),
      _painter(),
      _mouseStepVector(nullptr),
      _mouseDisplacementVector(nullptr),
      _scale(1),
      _phantomDrawingMode(false)
{
    _canvas.fill(Qt::white);
}

Graphics::~Graphics()
{
    delete _mouseStepVector;
    delete _mouseDisplacementVector;
    _mouseStepVector            = nullptr;
    _mouseDisplacementVector    = nullptr;
}

void Graphics::paintEvent(QPaintEvent *event)
{
    if(_phantomDrawingMode)
    {
        do_phantom_drawings();
        depict_canvas(*_phantomCanvas);
    }
    else
    {
        do_drawings();
        depict_canvas(_canvas);
    }
}

void Graphics::mouseMoveEvent(QMouseEvent *event)
{
    if(event->type() != QEvent::MouseMove) return;
    evaluateMouseDisplacement(event);
    update();
}

void Graphics::mousePressEvent(QMouseEvent *event)
{
    _mouseStepVector = new QLine(event->pos() / _scale, event->pos() / _scale);
    _mouseDisplacementVector = new QLine(event->pos() / _scale, event->pos() / _scale);

    //_phantomDrawingMode = is_phantom_tool_equiped();
    if(is_phantom_tool_equiped())
        set_phantom_mode(true);
}

void Graphics::mouseReleaseEvent(QMouseEvent *event)
{
    delete _mouseStepVector;
    delete _mouseDisplacementVector;
    _mouseStepVector            = nullptr;
    _mouseDisplacementVector    = nullptr;

    //_phantomDrawingMode = false;
    set_phantom_mode(false);
}

void Graphics::evaluateMouseDisplacement(QMouseEvent* event)
{
    if(_mouseStepVector)
        _mouseStepVector->setPoints(_mouseStepVector->p2(), event->pos() / _scale);
    else
        _mouseStepVector = new QLine(event->pos() / _scale, event->pos() / _scale);

    if(_mouseDisplacementVector)
        _mouseDisplacementVector->setPoints(_mouseDisplacementVector->p1(), event->pos() / _scale);
    else
        _mouseDisplacementVector = new QLine(event->pos() / _scale, event->pos() / _scale);
}

void Graphics::do_drawings()
{

    _painter.begin(&_canvas);

    switch(_selectedTool)
    {
    case Tool::NONE:
        break;
    case Tool::PENCIL:
        if(_mouseStepVector)
            _painter.drawLine(*_mouseStepVector);
        break;
    case Tool::LINE:
        //if(_mouseDisplacementVector)
            //_painter.drawLine(*_mouseDisplacementVector);
        break;
    case Tool::TRIANGLE:
        break;
    case Tool::RECTANGLE:
        break;
    case Tool::RHOMBUS:
        break;
    case Tool::POLYGON:
        break;
    case Tool::CIRCLE:
        break;
    case Tool::ELLIPSE:
        break;
    }

    _painter.end();
}

void Graphics::do_phantom_drawings()
{
    delete _phantomCanvas;
    _phantomCanvas = new QImage(_canvas);

    _painter.begin(_phantomCanvas);

    switch(_selectedTool)
    {
    case Tool::NONE:
        break;
    case Tool::PENCIL:
        break;
    case Tool::LINE:
        if(_mouseDisplacementVector)
            _painter.drawLine(*_mouseDisplacementVector);
        break;
    case Tool::TRIANGLE:
        break;
    case Tool::RECTANGLE:
        break;
    case Tool::RHOMBUS:
        break;
    case Tool::POLYGON:
        break;
    case Tool::CIRCLE:
        break;
    case Tool::ELLIPSE:
        break;
    }

    _painter.end();
}

void Graphics::depict_canvas(const QImage& canvas)
{
    _painter.begin(this);
    _painter.drawImage(rect(), canvas);
    _painter.end();
}

bool Graphics::is_phantom_tool_equiped()
{
    return _selectedTool != Tool::NONE && _selectedTool != Tool::PENCIL;
}

void Graphics::set_phantom_mode(bool phantomMode)
{
    _phantomDrawingMode = phantomMode;

    if(!phantomMode && _phantomCanvas)
    {
        _canvas = *_phantomCanvas;
        delete _phantomCanvas;
        _phantomCanvas = nullptr;
    }
}

void Graphics::reset()
{
    _canvas.fill(Qt::white);
    delete _phantomCanvas; _phantomCanvas = nullptr;
    delete _mouseStepVector; _mouseStepVector = nullptr;
    delete _mouseDisplacementVector; _mouseDisplacementVector = nullptr;
    _phantomDrawingMode = false;
}
