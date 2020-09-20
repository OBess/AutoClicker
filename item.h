#ifndef ITEM_H
#define ITEM_H

//qt
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QColor>
#include <QDoubleValidator>
#include <QIntValidator>

//custom
#include "MouseEvent.h"

class Item : public QWidget
{
public:
    Item(QWidget *parent = nullptr);
    ~Item();

    QLabel* getPosLbl();
    bool getDeleted();
    MouseEvent getEvent();

    void Generete(unsigned, QWidget *);
    void setBackground(QColor);
    void setEvent(MouseEvent);
private slots:
    void setDeleted();
    void setMilliseconds(const QString &);
    void setClicks(const QString &);

private:
    QLabel* posLbl;
    QLabel* secondLbl;
    QLabel* clicsLbl;
    QPushButton* deleteBtn;
    QLineEdit* secondEdit;
    QLineEdit* clicksEdit;
    QPalette pal;

    bool isDeleted;

    MouseEvent event;
};

#endif // ITEM_H
