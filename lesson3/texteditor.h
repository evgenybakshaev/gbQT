#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
#include <QString>

class TextEditor
{
    QString text;
public:
    TextEditor();

    void setText(QString);
    QString getText();
};

#endif // TEXTEDITOR_H
