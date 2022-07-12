#include "InstructionShower.h"
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QIcon>

InstructionShower::InstructionShower
(
        const QString& path,
        const QString& filename,
        QWidget* parent
)
    : QWidget(parent),
      _textBrowser(new QTextBrowser)
{
    setWindowIcon(QIcon(":/resourses/icons/icons8-помощь-32.png"));
    setWindowTitle("Instruction");
    resize(500, 500);
    _textBrowser->setSearchPaths(QStringList() << path);
    _textBrowser->setSource(filename);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(_textBrowser);
    setLayout(layout);
}

InstructionShower::~InstructionShower()
{
    delete _textBrowser;
    _textBrowser = nullptr;
}
