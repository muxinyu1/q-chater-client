#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent): QLabel(parent)
{

}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    switch (event->button()) {
    case Qt::LeftButton:
        emit this->clicked();
        break;
    default:
        break;
    }
    QLabel::mousePressEvent(event);
}
