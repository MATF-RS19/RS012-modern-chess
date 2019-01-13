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
figure_color current_turn = White;
std::vector<Figure*> white_fig;
std::vector<Figure*> black_fig;

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

    connect(ui_->pick_field, SIGNAL(clicked(bool)),
                this, SLOT(on_pick_field_clicked(bool)));

    setCentralWidget(ui_->horizontalLayoutWidget);
}

// read from the input line and move the selected figure
void MainWindow::on_next_turn_clicked(bool) {
    if(game.current_phase() == pick_field &&
       ui_->field_code_text->text() != "") {
        std::string text(ui_->field_code_text->text().toStdString());
        std::string letters("ABCDEFGH");
        std::string digits("12345678");
        // is the input text legit generally
        if(text.size() != 2) {
            qDebug() << "Mora da ima tacno 2 karaktera";
        } else if(letters.find(text[0]) == std::string::npos) {
            qDebug() << "Mora da pocinje sa nekim od karaktera ABCDEFGH";
        } else if(digits.find(text[1]) == std::string::npos) {
            qDebug() << "Mora da se zavrsava sa nekim od karaktera 12345678";
        } else {
            // "Manhattan" distance
            int h = text[0] - game.picked_figure()->get_hor();
            int v = text[1] - game.picked_figure()->get_ver();

            // check is the input text a legit field
            bool legit_move = false;
            for(auto && field : game.picked_figure()->possible_fields()) {
                if(text[0]-'A' == field.i() && text[1]-'1' == field.j()) {
                    board[game.picked_figure()->get_hor()-'A']
                         [game.picked_figure()->get_ver()-'1'].set_taken(false);
                    board[field.i()][field.j()].set_taken(true);
                    board[field.i()][field.j()].set_fig_col(game.picked_figure()->color());
                    legit_move = true;
                }
            }
            if(!legit_move) {
                qDebug() << "Nelegalan potez";
                return;
            }

            // check for collisions
            if(game.picked_figure()->color() == Black) {
                int k = 0;
                std::for_each(white_fig.begin(), white_fig.end(),
                              [&](Figure* fig) -> void {
                                if(fig->pos_i() == text[0]-'A' && fig->pos_j() == text[1]-'1') {
                                    scene_->removeItem(fig);
                                    white_fig.erase(white_fig.begin()+k);
                                }
                                k++;
                              }
                );
            } else if(game.picked_figure()->color() == White) {
                int k = 0;
                std::for_each(black_fig.begin(), black_fig.end(),
                              [&](Figure* fig) -> void {
                                if(fig->pos_i() == text[0]-'A' && fig->pos_j() == text[1]-'1') {
                                    scene_->removeItem(fig);
                                    black_fig.erase(black_fig.begin()+k);
                                }
                                k++;
                              }
                );
            }

            // move the figure and end the turn
            game.picked_figure()->moveBy(v*50, h*50);
            game.picked_figure()->set_pos_i(text[0]-'A');
            game.picked_figure()->set_pos_j(text[1]-'1');
            game.end_turn();
            ui_->field_code_text->clear();
        }
    } else {
        qDebug() << "Nisi uneo nikakav tekst ili nisi izabrao figuru";
    }
}

void MainWindow::on_pick_field_clicked(bool) {
    if(game.picked_figure() != nullptr) {
        game.set_current_phase(pick_field);
    } else {
        qDebug() << "Nisi izabrao figuru";
    }
}


void MainWindow::populateScene() {
    scene_ = new QGraphicsScene(0, 0, 800, 800);

    for(int8_t i = 0; i < 8; i++) {
        for(int8_t j = 0; j < 8; j++) {
            QRectF rect(120+j*50, 120+i*50, 50, 50);
            board[i][j].set_i(i);
            board[i][j].set_j(j);
            if(i == 0 || i == 1) {
                board[i][j].set_fig_col(White);
            } else {
                board[i][j].set_fig_col(Black);
            }
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
                        board[i][j].set_taken(true);
                        break;
                    case 1: // knight
                    case 6:
                        white_fig.push_back(new Figure(Knight, i, j, White, rect));
                        board[i][j].set_taken(true);
                        break;
                    case 2: // bishop
                    case 5:
                        white_fig.push_back(new Figure(Bishop, i, j, White, rect));
                        board[i][j].set_taken(true);
                        break;
                    case 3: // queen
                        white_fig.push_back(new Figure(Queen, i, j, White, rect));
                        board[i][j].set_taken(true);
                        break;
                    case 4: // king
                        white_fig.push_back(new Figure(King, i, j, White, rect));
                        board[i][j].set_taken(true);
                        break;
                }
                scene_->addItem(white_fig.back());
            } else if(i == 1) { // Pawn
                white_fig.push_back(new Figure(Pawn, i, j, White, rect));
                board[i][j].set_taken(true);
                scene_->addItem(white_fig.back());
            } else if(i == 7) {
                switch(j) {
                    case 0: // rook
                    case 7:
                        black_fig.push_back(new Figure(Rook, i, j, Black, rect));
                        board[i][j].set_taken(true);
                        break;
                    case 1: // knight
                    case 6:
                        black_fig.push_back(new Figure(Knight, i, j, Black, rect));
                        board[i][j].set_taken(true);
                        break;
                    case 2: // bishop
                    case 5:
                        black_fig.push_back(new Figure(Bishop, i, j, Black, rect));
                        board[i][j].set_taken(true);
                        break;
                    case 4: // queen
                        black_fig.push_back(new Figure(Queen, i, j, Black, rect));
                        board[i][j].set_taken(true);
                        break;
                    case 3: // king
                        black_fig.push_back(new Figure(King, i, j, Black, rect));
                        board[i][j].set_taken(true);
                        break;
                }
                scene_->addItem(black_fig.back());
            } else if(i == 6) { // Pawn
                black_fig.push_back(new Figure(Pawn, i, j, Black, rect));
                board[i][j].set_taken(true);
                scene_->addItem(black_fig.back());
            }
        }
    }
//    QRectF rect3(115+2*50, 100+2*50, 50, 50);
//    QRectF rect4(115+3*50, 100+2*50, 50, 50);
//    QRectF rect5(115+3*50, 100+3*50, 50, 50);
//    QRectF rect6(115+5*50, 100+2*50, 50, 50);
//    black_fig.push_back(new Figure(Rook, 2, 2, Black, rect3));
//    scene_->addItem(black_fig.back());
//    black_fig.push_back(new Figure(Rook, 2, 3, Black, rect4));
//    scene_->addItem(black_fig.back());
//    black_fig.push_back(new Figure(Rook, 3, 3, Black, rect5));
//    scene_->addItem(black_fig.back());
//    black_fig.push_back(new Figure(Rook, 2, 5, Black, rect6));
//    scene_->addItem(black_fig.back());
//    board[2][2].set_taken(true);
//    board[2][3].set_taken(true);
//    board[3][3].set_taken(true);
//    board[2][5].set_taken(true);
}

MainWindow::~MainWindow()
{
    delete scene_;
    delete ui_;
}
