#include "texteditor.h"

TextEditor::TextEditor()
{

}

void TextEditor::setText(QString s)
{
    text = s;
}

QString TextEditor::getText()
{
    return text;
}
