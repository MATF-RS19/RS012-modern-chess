#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <vector>
#include "figure.hpp"
#include "field.hpp"

Field board[8][8];
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene * scene = new QGraphicsScene(0, 0, 500, 500);
    std::vector<Figure*> white_fig;
    std::vector<Figure*> black_fig;
    for(int8_t i = 0; i < 8; i++) {
        for(int8_t j = 0; j < 8; j++) {
            QRectF rect(120+j*50, 120+i*50, 50, 50);
            board[i][j].set_rect(rect);
            board[i][j].set_initial_color((i+j) % 2 ? Qt::darkCyan : Qt::gray);
            board[i][j].set_color((i+j) % 2 ? Qt::darkCyan : Qt::gray);
            scene->addItem(board[i][j].rect_item());
        }
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
                scene->addItem(white_fig.back());
            } else if(i == 1) { // Pawn
                if(j==7 || j == 4 || j == 3) continue;
                white_fig.push_back(new Figure(Pawn, i, j, White, rect));
                board[i][j].set_taken(true);
                scene->addItem(white_fig.back());
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
                scene->addItem(black_fig.back());
            } else if(i == 6) { // Pawn
                board[i][j].set_taken(true);
                black_fig.push_back(new Figure(Pawn, i, j, Black, rect));
                scene->addItem(black_fig.back());
            }
        }
    }

    // add a view to visualize the scene
    QGraphicsView * view = new QGraphicsView(scene);

    view->show();
    return a.exec();
}
