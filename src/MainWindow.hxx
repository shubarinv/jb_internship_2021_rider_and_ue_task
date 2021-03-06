//
// Created by vhund on 01.03.2021.
//

#ifndef DB_QT_COURSEWORK_MAINWINDOW_HXX
#define DB_QT_COURSEWORK_MAINWINDOW_HXX

#include "SafeForwardList.hxx"
#include "Trie.hxx"
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStatusBar>
#include <iostream>
#include <mutex>


class MainWindow : public QMainWindow {
Q_OBJECT


public:
    explicit MainWindow(QPair<int, int> screenSize) {
        setFixedSize(screenSize.first / 2, screenSize.second / 2);
        initFields();
        setupLayout();
    }
    void terminate(){
        quit=true;
        trie->cancelAsync();
    };

private:
    QGridLayout *layout{};
    QStandardItemModel *itemModel{};
    QListView *searchResults{};
    QLineEdit *filepath{};
    QLineEdit *searchBox{};
    QPushButton *selectFile_btn{};
    QWidget *widget{};
    CompressedTrie *trie{};
    QLabel *loadLabel{};
    SafeList<std::string> queueToResultList;
    std::mutex m;
    bool quit{false};

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
        loadLabel=new QLabel(this);
        QFont f( "Arial", 25, QFont::Bold);
        loadLabel->setFont(f);
        loadLabel->setVisible(false);
        connect(selectFile_btn, &QPushButton::clicked, this, [this]() {
          selectFile();
        });
        connect(searchBox, &QLineEdit::textChanged, this, [this]() {
          searchWord();
        });
        trie = new CompressedTrie();
        std::thread t1([&] {
          while (!quit) {
              m.lock();
              if (queueToResultList.empty()) {
                  m.unlock();
                  using namespace std::chrono_literals;
                  std::this_thread::sleep_for(10ns);
              } else {
                  while (!queueToResultList.empty()) {
                      auto *res = new QStandardItem(queueToResultList.dequeue().c_str());
                      itemModel->appendRow(res);
                      m.unlock();
                      using namespace std::chrono_literals;
                      std::this_thread::sleep_for(1ms);
                  }

              }
              m.unlock();
          }
        });
        t1.detach();
    }
    void setupLayout() {
        setCentralWidget(widget);
        widget->setLayout(layout);
        layout->addWidget(filepath, 0, 0, 1, 1);
        layout->addWidget(selectFile_btn, 0, 1, 1, 1);
        layout->addWidget(searchResults, 1, 0, 1, 2);
        layout->addWidget(loadLabel, 1, 0, 1, 2);
        layout->addWidget(searchBox, 2, 0, 1, 2);
    }

    void selectFile() {
        filepath->setText(QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)")));
        loadLabel->setVisible(true);
        loadLabel->setText("Loading file...");
        QApplication::processEvents();
        trie->readFromFile(filepath->text().toStdString());
        loadLabel->setText("Optimizing file...");
        QApplication::processEvents();
        trie->compress();
        loadLabel->setVisible(false);
    }
    void searchWord() {
        clearResults();
        trie->cancelAsync();
        if (searchBox->text().length() >= 1) {
            trie->findRecursive(searchBox->text().toStdString(), &queueToResultList);
        }
    }

    void addResultToList(const std::string &result) {
        while (!m.try_lock()) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(5ns);
        }
        auto *res = new QStandardItem(result.c_str());
        itemModel->appendRow(res);
        m.unlock();
    }

    void clearResults() {
        while (!m.try_lock()) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(10ns);
        }

        while(!queueToResultList.empty()){
            queueToResultList.dequeue();
        }

        itemModel->clear();
        m.unlock();
    }
};


#endif//DB_QT_COURSEWORK_MAINWINDOW_HXX
