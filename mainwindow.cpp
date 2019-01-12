#include "mainwindow.hpp"

#include <QDebug>
#include <ui_mainwindow.h>
#include <QLineEdit>
#include <QStringList>
#include <QMessageBox>
#include <QPushButton>
#include "figure.hpp"
#include "field.hpp"
#include "game.hpp"

Field board[8][8];
Game game;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    populateScene();

    ui_->view = new QGraphicsView();

    ui_->view->setScene(scene_);

    ui_->view->setParent(ui_->horizontalLayoutWidget);
    ui_->view->resize(1000, 850);
    ui_->verticalSpacer->changeSize(50, 50);
    ui_->field_code_text;

    connect(ui_->pick_field, SIGNAL(clicked(bool)),
                this, SLOT(on_pick_field_clicked(bool)));

    setCentralWidget(ui_->horizontalLayoutWidget);
}

void MainWindow::on_next_turn_clicked(bool) {
    if(game.current_phase() == pick_field &&
       ui_->field_code_text->text() != "") {
        std::string text(ui_->field_code_text->text().toStdString());
        std::string letters("ABCDEFGH");
        std::string digits("12345678");
        if(text.size() != 2) {
            qDebug() << "Mora da ima tacno 2 karaktera";
        } else if(letters.find(text[0]) == std::string::npos) {
            qDebug() << "Mora da pocinje sa nekim od karaktera ABCDEFGH";
        } else if(digits.find(text[1]) == std::string::npos) {
            qDebug() << "Mora da se zavrsava sa nekim od karaktera 12345678";
        } else {
            qDebug() << ui_->field_code_text->text();
            int h = text[0] - game.picked_figure()->get_hor();
            int v = text[1] - game.picked_figure()->get_ver();
            bool legit_move = false;
            qDebug("%c, %c\n", game.picked_figure()->get_hor(), game.picked_figure()->get_ver());
            for(auto && field : game.picked_figure()->possible_fields()) {
                if(text[0]-'A' == field.i() && text[1]-'1' == field.j()) {
                    board[game.picked_figure()->get_hor()-'A']
                         [game.picked_figure()->get_ver()-'1'].set_taken(false);
                    field.set_taken(true);
                    legit_move = true;
                }
            }
            qDebug("%c, %c\n", game.picked_figure()->get_hor(), game.picked_figure()->get_ver());
            if(!legit_move) {
                qDebug() << "Not a legit move";
                return;
            }
            game.picked_figure()->moveBy(v*50, h*50);
            game.end_turn();
        }
    } else {
        qDebug() << "Nisi uneo nikakav tekst ili nisi izabrao figuru";
    }
}


void MainWindow::on_pick_field_clicked(bool) {
    if(game.picked_figure() != nullptr) {
        game.set_current_phase(pick_field);
        qDebug() << "Ok je, izabrao si figuru";
    } else {
        qDebug() << "Nisi izabrao figuru";
    }
}

void MainWindow::populateScene() {
    scene_ = new QGraphicsScene(0, 0, 800, 800);

    std::vector<Figure*> white_fig;
    std::vector<Figure*> black_fig;
    for(int8_t i = 0; i < 8; i++) {
        for(int8_t j = 0; j < 8; j++) {
            QRectF rect(120+j*50, 120+i*50, 50, 50);
            board[i][j].set_i(i);
            board[i][j].set_j(j);
            board[i][j].set_rect(rect);
            board[i][j].set_initial_color((i+j) % 2 ? Qt::darkCyan : Qt::gray);
            board[i][j].set_color((i+j) % 2 ? Qt::darkCyan : Qt::gray);
            scene_->addItem(board[i][j].rect_item());
        }
    }
    for(char c = 0; c < 8; c++) {
        QGraphicsTextItem *text = scene_->addText(QString('1'+c));
        text->setPos(125+50*c, 50);
        text->setScale(3);
    }

    for(char c = 0; c < 8; c++) {
        QGraphicsTextItem *text = scene_->addText(QString('A'+c));
        text->setPos(75, 110+50*c);
        text->setScale(3);
    }

    for(int8_t i = 0; i < 8; i++) {
        for(int8_t j = 0; j < 8; j++) {
            QRectF rect(115+j*50, 100+i*50, 50, 50);
            if(i == 0) {
                switch(j) {
                    case 0: // rook
                    case 7:
                        white_fig.push_back(new Figure(Rook, i, j, White, rect));
                        break;
                    case 1: // knight
                    case 6:
                        white_fig.push_back(new Figure(Knight, i, j, White, rect));
                        break;
                    case 2: // bishop
                    case 5:
                        white_fig.push_back(new Figure(Bishop, i, j, White, rect));
                        break;
                    case 3: // queen
                        white_fig.push_back(new Figure(Queen, i, j, White, rect));
                        break;
                    case 4: // king
                        white_fig.push_back(new Figure(King, i, j, White, rect));
                        break;
                }
                board[i][j].set_taken(true);
                scene_->addItem(white_fig.back());
            } else if(i == 1) { // Pawn
                if(j==7 || j == 4 || j == 3) continue;
                white_fig.push_back(new Figure(Pawn, i, j, White, rect));
                board[i][j].set_taken(true);
                scene_->addItem(white_fig.back());
            } else if(i == 7) {
                switch(j) {
                    case 0: // rook
                    case 7:
                        black_fig.push_back(new Figure(Rook, i, j, Black, rect));
                        break;
                    case 1: // knight
                    case 6:
                        black_fig.push_back(new Figure(Knight, i, j, Black, rect));
                        break;
                    case 2: // bishop
                    case 5:
                        black_fig.push_back(new Figure(Bishop, i, j, Black, rect));
                        break;
                    case 4: // queen
                        black_fig.push_back(new Figure(Queen, i, j, Black, rect));
                        break;
                    case 3: // king
                        black_fig.push_back(new Figure(King, i, j, Black, rect));
                        break;
                }
                board[i][j].set_taken(true);
                scene_->addItem(black_fig.back());
            } else if(i == 6) { // Pawn
                board[i][j].set_taken(true);
                black_fig.push_back(new Figure(Pawn, i, j, Black, rect));
                scene_->addItem(black_fig.back());
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete scene_;
    delete ui_;
}
