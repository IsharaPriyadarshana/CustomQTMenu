#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QToolButton>
#include <QPushButton>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Adding a menu to main menu
    QMenu* customMenu = new QMenu("Custom Menu", this);
    ui->menubar->addMenu(customMenu);

    // Add custom Menu
    createMenuAction("Action 1", customMenu);
    createMenuAction("Action 2", customMenu);
    createMenuAction("Action 3", customMenu);
    createMenuAction("Action 4", customMenu);
    createMenuAction("Action 5", customMenu);


}

void MainWindow::createMenuAction(QString text, QMenu* menu)
{
    // Create a complex widget to look like a one complex menu action
    QWidget* menuAct = new QWidget();

    // Tool button that will show right to the menu item
    QToolButton *toolBtn = new QToolButton(menuAct);
    // Push button with removed borders and backgrounds to look like the menu item
    QPushButton* act = new QPushButton(text, menuAct);
    act->setStyleSheet("QPushButton{border:none;}");
    // Chane the hover color
    menuAct->setStyleSheet("QWidget:hover{background-color:lightgreen;}");

    //This action can bear a widget
    QWidgetAction *btnAction= new QWidgetAction(menu);
    // Layout for the item menu with text and tool button
    QHBoxLayout* menuLyt = new QHBoxLayout(menuAct);
    menuLyt->addWidget(act);
    menuLyt->addItem(new QSpacerItem(10,0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    menuLyt->addWidget(toolBtn);
    toolBtn ->setIcon(QIcon(":Resources/bin.png"));
    btnAction->setDefaultWidget(menuAct);
    btnAction->setText(text);
    menu->addAction(btnAction);

    // Connecting button click signal to action trigger signal this can be used to perform some menu specific action
    connect(act, &QPushButton::clicked, btnAction, &QWidgetAction::triggered);

    // When delete tool button is clicked, the action is removed from the menu
    connect(toolBtn, &QToolButton::clicked, this, [menu, btnAction] () {menu->removeAction(btnAction);  delete btnAction; });
}

MainWindow::~MainWindow()
{
    delete ui;
}

