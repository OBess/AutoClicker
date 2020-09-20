#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//qt
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

//c++
#include <thread>
#include <chrono>
#include <windows.h>
#include <vector>

//custom
#include "MouseEvent.h"
#include "item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeBackground(unsigned, QColor);
private slots:
    void on_actionAdd_triggered();
    void on_actionPlay_triggered();
    void on_actionStop_triggered();

private:
    void start();

    static void executeEvents(std::vector<Item*>*, bool*);
    static void checkDeletedItem(std::vector<Item*>*, bool*);
    static void observerMouseClick(std::vector<Item*>*, bool*, QLabel*);

    Ui::MainWindow *ui;
    QWidget* parent;

    std::vector<Item*> items;

    bool isWork;
    bool isDeleted;
    bool traceMouse;
    const short MIN_SEC = 1000;
    const unsigned MAX_SEC = 3600000;
};
#endif // MAINWINDOW_H
