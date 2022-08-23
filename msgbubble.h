#ifndef MSGBUBBLE_H
#define MSGBUBBLE_H

#include <QListWidgetItem>
#include <QObject>

class MsgBubble: QListWidgetItem
{
public:
    MsgBubble(QString msg, bool mine);
};

#endif // MSGBUBBLE_H
