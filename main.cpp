#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <vector>
#include "figure.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create a scene
    QGraphicsScene * scene = new QGraphicsScene(0, 0, 500, 500);

    QGraphicsRectItem *table[8][8];
    std::vector<Figure*> white_fig;
    std::vector<Figure*> black_fig;
    for(uint8_t i = 0; i < 8; i++) {
        for(uint8_t j = 0; j < 8; j++) {
            table[i][j] = new QGraphicsRectItem();
            QRectF rect(120+j*50, 120+i*50, 50, 50);
            table[i][j]->setRect(rect);
            table[i][j]->setBrush((i+j) % 2 ? Qt::darkCyan : Qt::gray);
            scene->addItem(table[i][j]);
        }
    }
    for(uint8_t i = 0; i < 8; i++) {
        for(uint8_t j = 0; j < 8; j++) {
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
                scene->addItem(white_fig.back());
            } else if(i == 1) { // Pawn
                white_fig.push_back(new Figure(Pawn, i, j, White, rect));
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
                scene->addItem(black_fig.back());
            } else if(i == 6) { // Pawn
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
