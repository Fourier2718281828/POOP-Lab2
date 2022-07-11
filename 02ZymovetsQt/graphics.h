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
        POLYGON,
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
    inline void save(const QFile&);
private:
    void evaluateMouseDisplacement(QMouseEvent* event);
    void do_drawings();
    void do_phantom_drawings();
    void depict_canvas(const QImage&);
    bool is_phantom_tool_equiped();
    void set_phantom_mode(bool);
    void reset();
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
    reset();
    update();
}

inline void Graphics::save(const QFile& file)
{

}
#endif // GRAPHICS_H
