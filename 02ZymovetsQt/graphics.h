#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QObject>


#include <QWidget>
#include <QDebug>

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
    ~Graphics() = default;
public:
    inline void select_tool(const Tool tool);
    inline void deselect_tool();
private:
    virtual void paintEvent(QPaintEvent* event) override;
private:
    Tool _selectedTool;
};

inline void Graphics::select_tool(const Tool tool)
{
    _selectedTool = tool;
}

inline void Graphics::deselect_tool()
{
    _selectedTool = Tool::NONE;
}

#endif // GRAPHICS_H
