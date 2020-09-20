#include "mainwindow.h"
#include "ui_mainwindow.h"

//Qt
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->start();
}
MainWindow::~MainWindow()
{
    this->isWork = false;
    this->isDeleted = false;
    this->traceMouse = false;

    for (size_t i = 0; i < this->items.size(); i++)
        delete this->items.at(i);
    this->items.clear();

    delete ui;
}
//~Qt

//Main
void MainWindow::start(){
    this->parent = this;
    this->isWork = false;
    this->isDeleted = true;
    this->traceMouse = false;

    std::thread (this->checkDeletedItem, &this->items, &this->isDeleted).detach();
}
//~Main

//Excecutable functions
void MainWindow::executeEvents(std::vector<Item*>* items, bool* isWork){
    POINT startPos;
    while(*isWork){
        for(size_t i = 0; i < items->size(); i++)
        {
            if(!*isWork){
                for(size_t j = 0; j < items->size(); j++)
                    items->at(j)->setBackground(QColor("#F0F0F0"));
                break;
            }
            GetCursorPos(&startPos);
            SetCursorPos(items->at(i)->getEvent().x, items->at(i)->getEvent().y);
            items->at(i)->setBackground(QColor("#75e4fa"));
            for(size_t j = 0; j < items->at(i)->getEvent().clicks; j++){
                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, items->at(i)->getEvent().x, items->at(i)->getEvent().y, 0, 0);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            SetCursorPos(startPos.x, startPos.y);
            std::this_thread::sleep_for(std::chrono::seconds(items->at(i)->getEvent().milliseconds));
            items->at(i)->setBackground(QColor("#F0F0F0"));
        }
        if(items->size() == 0)
            *isWork = false;
    }
    for(size_t j = 0; j < items->size(); j++)
        items->at(j)->setBackground(QColor("#F0F0F0"));
}
void MainWindow::observerMouseClick(std::vector<Item*>* items, bool* traceMouse, QLabel* item){
    POINT mousePos;
    *traceMouse = true;
    while(*traceMouse){
        GetCursorPos(&mousePos);
        item->setText("Mouse position: " + QString(std::to_string(mousePos.x).c_str()) + " - " + QString(std::to_string(mousePos.y).c_str()));
        if((GetKeyState(VK_LBUTTON) & 0x100) != 0){
            *traceMouse = false;
            break;
        }
    }
    items->at(items->size() - 1)->setEvent({mousePos.x, mousePos.y});
}
void MainWindow::checkDeletedItem(std::vector<Item *> *items, bool *isDeleted){
    while(*isDeleted){
        for(size_t i = 0; i < items->size(); i++){
            if(items->at(i)->getDeleted()){
                items->at(i)->hide();
                items->erase(items->begin() + i);

                for(size_t j = i; j < items->size(); j++)
                    items->at(j)->setGeometry(items->at(j)->x(), items->at(j)->y() - 20, items->at(j)->width(), items->at(j)->height());
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
//~Excecutable functions

//Slots
void MainWindow::on_actionAdd_triggered()
{
    if(this->traceMouse)
        return;
    Item* item = new Item(this);
    this->items.push_back(item);
    item->Generete(this->items.size() - 1, this);
    item->show();

    std::thread (this->observerMouseClick, &this->items, &this->traceMouse, item->getPosLbl()).detach();
}
void MainWindow::on_actionPlay_triggered()
{
    this->isWork = true;
    if(this->isWork)
        std::thread (this->executeEvents, &this->items, &this->isWork).detach();
}
void MainWindow::on_actionStop_triggered()
{
    this->isWork = false;
    for(size_t j = 0; j < this->items.size(); j++)
        this->items.at(j)->setBackground(QColor("#F0F0F0"));
}
//~Slots
