//
// Created by vhund on 01.03.2021.
//

#ifndef DB_QT_COURSEWORK_MAINWINDOW_HXX
#define DB_QT_COURSEWORK_MAINWINDOW_HXX

#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <future>
#include <iostream>

class MainWindow : public QMainWindow {
    Q_OBJECT;

public:
    explicit MainWindow(QPair<int, int> screenSize, QApplication *app = nullptr) {
        setFixedSize(screenSize.first / 2, screenSize.second / 2);
    }

private:
};


#endif//DB_QT_COURSEWORK_MAINWINDOW_HXX
