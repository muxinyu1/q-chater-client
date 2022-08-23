#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(const QVector<QString>& friends,
                       const QString& acc_name,
                       QTcpSocket* client,
                       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow), friends_list(nullptr), client(client), acc_name(acc_name),
    target_name(), current_chat(nullptr), list_map(new QHash<QString, QListWidget*>())
    , animation_close(new QPropertyAnimation(this, "windowOpacity"))
    , animation_minimize(new QPropertyAnimation(this, "windowOpacity"))
{
    ui->setupUi(this);
    this->ui->accName->setText(acc_name);
    this->friends_list = new QListWidget(this);
    this->friends_list->setGeometry(this->ui->friends_list->geometry());
    this->friends_list->setFont(QFont(this->ui->send->font().family(), 12));
    auto set = QSet<QString>();
    for (auto& i: friends) {
        if (!set.contains(i)) {
            this->friends_list->addItem(i);
            //每个好友对应一个chat, 但是初始不显示任何chat
            auto chats = new QListWidget(this);
            chats->setGeometry(this->ui->msg_area->geometry());
            this->list_map->insert(i, chats);
            this->list_map->value(i)->hide();
            set.insert(i);
        }
    }
    this->setWindowFlag(Qt::FramelessWindowHint);
    //点击×关闭窗口
    connect(this->ui->close, &QPushButton::clicked, [this]() {
       char request[1024];
       sprintf(request, "5 %s", this->acc_name.toStdString().c_str());
       this->client->write(request);
       this->close();
    });
//    //动画结束后关闭窗口，并发送注销请求
//    connect(this->animation_close, &QPropertyAnimation::finished, [this]() {
//        char request[1024];
//        sprintf(request, "5 %s", this->acc_name.toStdString().c_str());
//        this->client->write(request);
//        qDebug() << request;
//        this->close();
//    });
//    //点击close开始渐变动画
//    connect(this->ui->close, &ClickableLabel::clicked, [this]() {
//        this->animation_close->setDuration(100);
//        this->animation_close->setStartValue(1);
//        this->animation_close->setEndValue(0);
//        this->animation_close->start();
//    });
    //点击-最小化窗口
    connect(this->ui->minimize, &QPushButton::clicked, [this]() {
        this->animation_minimize->setDuration(100);
        this->animation_minimize->setStartValue(1);
        this->animation_minimize->setEndValue(0);
        this->animation_minimize->start();
    });
    connect(this->animation_minimize, &QPropertyAnimation::finished, [this]() {
        this->showMinimized();
        this->setProperty("windowOpacity", 1);
    });
    //添加好友
    connect(this->ui->add, &QPushButton::clicked, [this]() {
        if (this->ui->search_friend_edit_text->text() == "") {
            auto pop_up = LoginHint("Empty Account!", this);
            pop_up.exec();
        } else if (this->ui->search_friend_edit_text->text() == this->ui->accName->text()) {
            auto pop_up = LoginHint("Can't Add Yourself!", this);
            pop_up.exec();
        } else if (this->list_map->contains(this->ui->search_friend_edit_text->text())) {
            auto pop_up = LoginHint("Already Added!", this);
            pop_up.exec();
        } else {
            QString request = "3 " + this->acc_name + " " + this->ui->search_friend_edit_text->text();
            this->client->write(request.toStdString().c_str());
        }
    });
    //选中某一好友开始聊天
    connect(this->friends_list, &QListWidget::itemClicked, [this](QListWidgetItem* item) {
        this->target_name = item->text();
        this->ui->chat_target->setText(target_name);
        //对应的chat也得切换
        if (this->current_chat != nullptr) {
            this->current_chat->hide();
        }
        this->current_chat = this->list_map->value(item->text());
        this->current_chat->show();
    });
    //发送消息
    connect(this->ui->send, &QPushButton::clicked,this, &ChatWindow::send_msg);
    //ui->scrollAreaWidgetContents.
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::addFriend(const QString& friend_acc)
{
    this->friends_list->addItem(friend_acc);
    auto chats = new QListWidget(this);
    chats->setGeometry(this->ui->msg_area->geometry());
    this->list_map->insert(friend_acc, chats);
    this->list_map->value(friend_acc)->hide();
    this->ui->search_friend_edit_text->clear();
}

void ChatWindow::recieve(const QString& who, const QString& what)
{
    //接受信息
    if (!this->list_map->contains(who)) {
        auto chats = new QListWidget(this);
        chats->setGeometry(this->ui->msg_area->geometry());
        this->list_map->insert(who, chats);
    }
    const auto mapped_chat = this->list_map->value(who);
    mapped_chat->addItem(new MsgBubble(what, false));
}

Ui::ChatWindow* ChatWindow::get_ui()
{
    return this->ui;
}

void ChatWindow::send_msg()
{
    auto msg = this->ui->edit_text->toPlainText();
    if (this->target_name == "") {
        //未选择聊天对象
        QApplication::beep();
        auto pop_up = LoginHint("Choose A Friend!", this);
        pop_up.exec();
        return;
    }
    if (msg == "") {
        //发送了空消息
        QApplication::beep();
        auto pop_up = LoginHint("Empty Message!", this);
        pop_up.exec();
        return;
    }
    char request[2048];
    this->ui->edit_text->clear();
    //从何而来的消息，去到哪，内容是什么
    sprintf(request, "4 %s %s %s",
            this->acc_name.toStdString().c_str(),
            this->target_name.toStdString().c_str(),
            msg.toStdString().c_str()
            );
    //如果当前好友还没有与之对应的聊天窗口
    if (!this->list_map->contains(this->target_name)) {
        //就创建一个
        auto chats = new QListWidget(this);
        //大小和msg_area一样（msg_area是预设好的空的Qlabel）
        chats->setGeometry(this->ui->msg_area->geometry());
        //创建完了，加到map中
        this->list_map->insert(this->target_name, chats);
    }
    this->list_map->value(this->target_name)->addItem(new MsgBubble(msg, true));
    this->client->write(request);
}

void ChatWindow::mouseMoveEvent(QMouseEvent* event)
{
    QPoint y = event->globalPos();
    QPoint x = y - this->z;
    this->move(x);
}

void ChatWindow::mousePressEvent(QMouseEvent* event)
{
    QPoint y = event->globalPos();
    QPoint x = this->geometry().topLeft();
    this->z = y - x;
}

void ChatWindow::mouseReleaseEvent(QMouseEvent* event)
{
    this->z = QPoint();
}

void ChatWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
        this->ui->send->click();
        break;
    case Qt::Key_Return:
        this->ui->send->click();
        break;
    default:
        break;
    }
}
