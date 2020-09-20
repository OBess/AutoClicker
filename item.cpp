#include "item.h"

//Qt
Item::Item(QWidget *parent) : QWidget(parent), event{-1, -1}{
    this->setAutoFillBackground(true);
}
Item::~Item(){
    if(this->posLbl) delete this->posLbl;
    if(this->clicsLbl) delete this->clicsLbl;
    if(this->deleteBtn) delete this->deleteBtn;
    if(this->secondLbl) delete this->secondLbl;
    if(this->clicksEdit) delete this->clicksEdit;
    if(this->secondEdit) delete this->secondEdit;
}
//~Qt

//Main
void Item::Generete(unsigned num, QWidget* parent){
    this->isDeleted = false;

    this->setGeometry(9, 20 * (num + 1), 280, 20);

    this->posLbl = new QLabel("Position: unknown", this);
    this->posLbl->setGeometry(0, 0, 131, 20);
    this->posLbl->show();

    this->clicsLbl = new QLabel("Clicks", this);
    this->clicsLbl->setGeometry(131, 0, 31, 20);
    this->clicsLbl->show();

    this->clicksEdit = new QLineEdit("1", this);
    this->clicksEdit->setGeometry(156, 0, 17, 20);
    this->clicksEdit->setMaxLength(2);
    this->clicksEdit->setValidator(new QIntValidator(1, 99, this));
    this->clicksEdit->show();

    this->secondLbl = new QLabel("Sec", this);
    this->secondLbl->setGeometry(173, 0, 17, 20);
    this->secondLbl->show();

    this->secondEdit = new QLineEdit("1", this);
    this->secondEdit->setGeometry(190, 0, 30, 20);
    this->secondEdit->setMaxLength(4);
    this->secondEdit->setValidator(new QIntValidator(1, 9999, this));
    this->secondEdit->show();

    this->deleteBtn = new QPushButton("Delete", this);
    this->deleteBtn->setGeometry(280 - 50, 0, 51, 20);
    this->deleteBtn->show();

    if(num > 3){
        parent->setMaximumSize(parent->width(), parent->height() + 20);
        parent->setMinimumSize(parent->width(), parent->height() + 20);
        parent->setGeometry(parent->x(), parent->y(), parent->width(), parent->height() + 20);
    }

    connect(this->deleteBtn, &QPushButton::clicked, this, &Item::setDeleted);
    connect(this->secondEdit, &QLineEdit::textChanged, this, &Item::setMilliseconds);
    connect(this->clicksEdit, &QLineEdit::textChanged, this, &Item::setClicks);
}
//~Main

//Getters
QLabel* Item::getPosLbl(){
    return this->posLbl;
}
bool Item::getDeleted(){
    return this->isDeleted;
}
MouseEvent Item::getEvent(){
    return this->event;
}
//~Getters

//Setters
void Item::setBackground(QColor color){
    this->pal.setColor(QPalette::Background, color);
    this->setPalette(this->pal);
}
void Item::setEvent(MouseEvent event){
    this->event = event;
}
//~Setters

//Slots
void Item::setDeleted(){
    this->isDeleted = true;
}
void Item::setMilliseconds(const QString &value){
    this->event.milliseconds = value.toInt();
}
void Item::setClicks(const QString &value){
    this->event.clicks = value.toInt();
}
//~Slots
