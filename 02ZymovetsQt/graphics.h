#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QFile>

class Graphics : public QWidget
{
    Q_OBJECT
public:
    enum class Tool
    {
        NONE,
        PENCIL,
        LINE,
        TRIANGLE,
        RECTANGLE,
        RHOMBUS,
        CIRCLE,
        ELLIPSE,
    };

public:
    explicit Graphics(QWidget *parent = nullptr);
    ~Graphics();
public:
    inline void select_tool(const Tool tool);
    inline void deselect_tool();
    inline void scale(const qreal);
    inline void clear();
    inline void save(const QString&);
    inline void load(const QString&);
    inline void reset();
    inline void set_pen_colour(const QColor&);
    inline void set_pen_size(const qreal);
    inline qreal get_pen_size();
private:
    void evaluateMouseDisplacement(QMouseEvent* event);
    void do_drawings();
    void do_phantom_drawings();
    void depict_canvas(const QImage&);
    bool is_phantom_tool_equiped();
    void set_phantom_mode(bool);
private:
    virtual void paintEvent(QPaintEvent* event)         override;
    virtual void mouseMoveEvent(QMouseEvent *event)     override;
    virtual void mousePressEvent(QMouseEvent *event)    override;
    virtual void mouseReleaseEvent(QMouseEvent *event)  override;
private:
    Tool _selectedTool;
    QImage _canvas;
    QImage* _phantomCanvas;
    QPainter _painter;
    QLine* _mouseStepVector;
    QLine* _mouseDisplacementVector;
    qreal _scale;
    bool _phantomDrawingMode;
    QColor _currentPenColor;
    qreal _penSize;
private:
    static const QSize DEFAULT_SIZE;
};

inline void Graphics::select_tool(const Tool tool)
{
    _selectedTool = tool;
}

inline void Graphics::deselect_tool()
{
    _selectedTool = Tool::NONE;
}

inline void Graphics::scale(const qreal factor)
{
    setFixedSize(factor * size());
    _scale *= factor;
}

inline void Graphics::clear()
{
    _canvas.fill(Qt::white);
    delete _phantomCanvas; _phantomCanvas = nullptr;
    delete _mouseStepVector; _mouseStepVector = nullptr;
    delete _mouseDisplacementVector; _mouseDisplacementVector = nullptr;
    _phantomDrawingMode = false;
    update();
}

inline void Graphics::save(const QString& path)
{
    _canvas.save(path);
}

inline void Graphics::load(const QString& path)
{
    reset();
    _canvas.load(path);
    setFixedSize(_canvas.size());
    update();
}


inline void Graphics::reset()
{
    scale(1 / _scale);
    _canvas = QImage(DEFAULT_SIZE, QImage::Format_RGB32);
    _canvas.fill(Qt::white);
    setFixedSize(_canvas.size());
    delete _phantomCanvas; _phantomCanvas = nullptr;
    delete _mouseStepVector; _mouseStepVector = nullptr;
    delete _mouseDisplacementVector; _mouseDisplacementVector = nullptr;
    _phantomDrawingMode = false;
    update();
}

inline void Graphics::set_pen_colour(const QColor& color)
{
    _currentPenColor = color;
}

inline void Graphics::set_pen_size(const qreal new_size)
{
    _penSize = new_size;
}

inline qreal Graphics::get_pen_size()
{
    return _penSize;
}


#endif // GRAPHICS_H
