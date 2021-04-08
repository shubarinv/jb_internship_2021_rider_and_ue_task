//
// Created by vhund on 01.03.2021.
//

#ifndef DB_QT_COURSEWORK_MAINWINDOW_HXX
#define DB_QT_COURSEWORK_MAINWINDOW_HXX

#include "Trie.hxx"
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QListView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStatusBar>
#include <future>
#include <iostream>

class MainWindow : public QMainWindow {
    Q_OBJECT;

public:
    explicit MainWindow(QPair<int, int> screenSize) {
        setFixedSize(screenSize.first / 2, screenSize.second / 2);
        initFields();
        setupLayout();
    }

private:
    QGridLayout *layout{};
    QStandardItemModel *itemModel{};
    QListView *searchResults{};
    QLineEdit *filepath{};
    QLineEdit *searchBox{};
    QPushButton *selectFile_btn{};
    QWidget *widget{};
    Trie *trie{};

    void initFields() {
        widget = new QWidget(this);

        layout = new QGridLayout(widget);

        itemModel = new QStandardItemModel(this);

        filepath = new QLineEdit(this);
        searchBox = new QLineEdit(this);

        selectFile_btn = new QPushButton(this);
        selectFile_btn->setText("Select File");
        selectFile_btn->setObjectName("add-btn");

        searchResults = new QListView(this);
        searchResults->setModel(itemModel);
        searchResults->setEditTriggers(QAbstractItemView::NoEditTriggers);

        connect(selectFile_btn, &QPushButton::clicked, this, [this]() {
            selectFile();
        });
        connect(searchBox, &QLineEdit::textChanged, this, [this]() {
                searchWord();
        });
        trie = new Trie();
    }
    void setupLayout() {
        setCentralWidget(widget);
        widget->setLayout(layout);
        layout->addWidget(filepath, 0, 0, 1, 1);
        layout->addWidget(selectFile_btn, 0, 1, 1, 1);
        layout->addWidget(searchResults, 1, 0, 1, 2);
        layout->addWidget(searchBox, 2, 0, 1, 2);
    }

    void selectFile() {
        filepath->setText(QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)")));
        trie->readFromFile(filepath->text().toStdString());
    }
    void searchWord() {
        clearResults();
        if (searchBox->text().length() >= 3) {
            // TODO: DO SOMETHING WITH THAT! It locks main thread
            trie->findRecursive(searchBox->text().toStdString(), [this](auto &&PH1) { addResultToList(std::forward<decltype(PH1)>(PH1)); });
        }
    }

    void addResultToList(const std::string &result) {
        LOG(INFO) << "Got new word: " << result;
        auto *res = new QStandardItem(result.c_str());
        itemModel->appendRow(res);
    }

    void clearResults() {
        itemModel->clear();
    }

};


#endif//DB_QT_COURSEWORK_MAINWINDOW_HXX
