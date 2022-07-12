#include "graphics.h"
#include <QPainter>
#include <QtMath>
#include <QMouseEvent>

using Tool = Graphics::Tool;

const QSize Graphics::DEFAULT_SIZE(2000, 850);

Graphics::Graphics(QWidget *parent)
    : QWidget{parent},
      _selectedTool(Tool::NONE),
      _canvas(DEFAULT_SIZE, QImage::Format_RGB32),
      _phantomCanvas(nullptr),
      _painter(),
      _mouseStepVector(nullptr),
      _mouseDisplacementVector(nullptr),
      _scale(1),
      _phantomDrawingMode(false),
      _currentPenColor(Qt::black),
      _penSize(1)
{
    _canvas.fill(Qt::white);
    setFixedSize(_canvas.size());
    setAcceptDrops(true);
}

Graphics::~Graphics()
{
    delete _mouseStepVector;
    delete _mouseDisplacementVector;
    _mouseStepVector            = nullptr;
    _mouseDisplacementVector    = nullptr;
}

void Graphics::paintEvent(QPaintEvent*)
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

void Graphics::mouseMoveEvent(QMouseEvent* event)
{
    if(event->type() != QEvent::MouseMove) return;
    evaluateMouseDisplacement(event);
    update();
}

void Graphics::mousePressEvent(QMouseEvent* event)
{
    _mouseStepVector = new QLine(event->pos() / _scale, event->pos() / _scale);
    _mouseDisplacementVector = new QLine(event->pos() / _scale, event->pos() / _scale);

    if(is_phantom_tool_equiped())
        set_phantom_mode(true);
}

void Graphics::mouseReleaseEvent(QMouseEvent*)
{
    delete _mouseStepVector;
    delete _mouseDisplacementVector;
    _mouseStepVector            = nullptr;
    _mouseDisplacementVector    = nullptr;

    set_phantom_mode(false);
}

void Graphics::evaluateMouseDisplacement(QMouseEvent* event)
{
    if(_mouseStepVector)
        _mouseStepVector->setPoints(_mouseStepVector->p2(), event->pos() / _scale);
    else
        _mouseStepVector = new QLine(event->pos()/ _scale, event->pos() / _scale);

    if(_mouseDisplacementVector)
        _mouseDisplacementVector->setPoints(_mouseDisplacementVector->p1(), event->pos() / _scale);
    else
        _mouseDisplacementVector = new QLine(event->pos() / _scale, event->pos() / _scale);
}

void Graphics::do_drawings()
{

    _painter.begin(&_canvas);
    _painter.setPen(QPen(_currentPenColor, _penSize));

    switch(_selectedTool)
    {
    case Tool::NONE:
        break;
    case Tool::PENCIL:
        if(_mouseStepVector)
            _painter.drawLine(*_mouseStepVector);
        break;
    case Tool::LINE:
        break;
    case Tool::TRIANGLE:
        break;
    case Tool::RECTANGLE:
        break;
    case Tool::RHOMBUS:
        break;
    case Tool::CIRCLE:
        break;
    case Tool::ELLIPSE:
        break;
    case Graphics::Tool::ERASER:
        _painter.setPen(QPen(Qt::white, _penSize));
        if(_mouseStepVector)
            _painter.drawEllipse(QPointF(_mouseStepVector->p2()), 2*_penSize, 2*_penSize);
        _painter.setPen(QPen(_currentPenColor, _penSize));
        break;
    }

    _painter.end();
}

void Graphics::do_phantom_drawings()
{
    delete _phantomCanvas;
    _phantomCanvas = new QImage(_canvas);

    if(!_mouseDisplacementVector) return;

    _painter.begin(_phantomCanvas);
    _painter.setPen(QPen(_currentPenColor,_penSize));
    QRect rect(_mouseDisplacementVector->p1(), _mouseDisplacementVector->p2());
    QPoint* rectSideCentres= new QPoint[4]
    {
            (rect.topLeft() + rect.topRight()) / 2,
            (rect.topRight() + rect.bottomRight()) / 2,
            (rect.bottomRight() + rect.bottomLeft()) / 2,
            (rect.bottomLeft() + rect.topLeft()) / 2
    };
    switch(_selectedTool)
    {
    case Tool::NONE:
        break;
    case Tool::PENCIL:
        break;
    case Tool::LINE:
        _painter.drawLine(*_mouseDisplacementVector);
        break;
    case Tool::TRIANGLE:
    {
        QPoint* triangleVertices = new QPoint[3]
        {
            rect.bottomLeft(),
            rect.bottomRight(),
            (rect.topLeft() + rect.topRight()) / 2
        };
        _painter.drawPolygon(triangleVertices, 3);
        delete[] triangleVertices;
        break;
    }
    case Tool::RECTANGLE:
        _painter.drawRect(rect);
        break;
    case Tool::RHOMBUS:
        _painter.drawPolygon(rectSideCentres, 4);
        break;
    case Tool::CIRCLE:
    {
        QPoint p1 = _mouseDisplacementVector->p1();
        QPoint p2 = _mouseDisplacementVector->p2();
        QPoint v = p2 - p1;
        QPointF p1f(p1);
        qreal radius = qSqrt(QPoint::dotProduct(v, v));
        _painter.drawEllipse(p1f, radius, radius);
        break;
    }
    case Tool::ELLIPSE:
        _painter.drawEllipse(rect);
        break;
    case Graphics::Tool::ERASER:
        break;
    }
    delete[] rectSideCentres; rectSideCentres = nullptr;
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
    return _selectedTool != Tool::NONE && _selectedTool != Tool::PENCIL &&
            _selectedTool != Tool::ERASER;
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

