#ifndef INSTRUCTIONSHOWER_H
#define INSTRUCTIONSHOWER_H

#include <QWidget>

class QTextBrowser;

class InstructionShower : public QWidget {
    Q_OBJECT

public:
    InstructionShower(const QString&, const QString&, QWidget* = nullptr);
    ~InstructionShower();
private:
    QTextBrowser* _textBrowser;
};
#endif // INSTRUCTIONSHOWER_H
