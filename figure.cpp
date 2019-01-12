#include "figure.hpp"
#include "field.hpp"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include "game.hpp"

QRectF Figure::boundingRect() const {
    return rect_;
}

QPainterPath Figure::shape() const {
    QPainterPath path;
    path.addRect(rect_);
    return path;
}

void Figure::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
    QImage image;
    switch(type_) {
        case Pawn:
            image = QImage(QString("D:\\qt_vezbanje\\projekat\\figures\\") +
                           QString(color_ == White ? "white_pawn.png" : "black_pawn.png"));
            break;
        case Rook:
            image = QImage(QString("D:\\qt_vezbanje\\projekat\\figures\\") +
                       QString(color_ == White ? "white_rook.png" : "black_rook.png"));
            break;
        case Knight:
            image = QImage(QString("D:\\qt_vezbanje\\projekat\\figures\\") +
                       QString(color_ == White ? "white_knight.png" : "black_knight.png"));
            break;
        case Bishop:
            image = QImage(QString("D:\\qt_vezbanje\\projekat\\figures\\") +
                       QString(color_ == White ? "white_bishop.png" : "black_bishop.png"));
            break;
        case Queen:
            image = QImage(QString("D:\\qt_vezbanje\\projekat\\figures\\") +
                       QString(color_ == White ? "white_queen.png" : "black_queen.png"));
            break;
        case King:
            image = QImage(QString("D:\\qt_vezbanje\\projekat\\figures\\") +
                       QString(color_ == White ? "white_king.png" : "black_king.png"));
            break;
    }
    painter->drawImage(QPointF(rect_.x(), rect_.y()), image);
    return;
}

extern Field board[8][8];
void Figure::calculate_possible_fields(int8_t i, int8_t j,
                                             figure_type type, QColor color) {
    std::vector<Field> result{};
    switch (type) {
        case Pawn: {
            if(color == Black) {
                if(i > 1) {
                    if(!board[i-1][j].is_taken()) {
                        result.push_back(board[i-1][j]);
                    } if(j >= 1 && board[i-1][j-1].is_taken() && board[i-1][j-1].is_enemy()) {
                        result.push_back(board[i-1][j-1]);
                    } if(j <= 6 && board[i-1][j+1].is_taken() && board[i-1][j+1].is_enemy()) {
                        result.push_back(board[i-1][j+1]);
                    }
                }
            } else if(color == White) {
                if(i <= 6) {
                    if(!board[i+1][j].is_taken()) {
                        result.push_back(board[i+1][j]);
                    } if(j >= 1 && board[i+1][j-1].is_taken() && board[i+1][j-1].is_enemy()) {
                        result.push_back(board[i+1][j-1]);
                    } if(j <= 6 && board[i+1][j+1].is_taken() && board[i+1][j+1].is_enemy()) {
                        result.push_back(board[i+1][j+1]);
                    }
                }
            }
            break;
        }
        case Rook: {
            for(int8_t tmp_i = i+1; tmp_i < 8; tmp_i++) {
                if(board[tmp_i][j].is_taken()) {
                    if(board[tmp_i][j].is_enemy()) {
                        result.push_back(board[tmp_i][j]);
                    } break;
                }
                result.push_back(board[tmp_i][j]);
            }
            for(int8_t tmp_i = i-1; tmp_i >= static_cast<int8_t>(0); tmp_i--) {
                if(board[tmp_i][j].is_taken()) {
//                    qDebug() << "aaaaaaaaaaaaaa";
                    if(board[tmp_i][j].is_enemy()) {
                        result.push_back(board[tmp_i][j]);
                    } break;
                }
                result.push_back(board[tmp_i][j]);
            }
            for(int8_t tmp_j = j+1; tmp_j < 8; tmp_j++) {
                if(board[i][tmp_j].is_taken()) {
                    if(board[i][tmp_j].is_enemy()) {
                        result.push_back(board[i][tmp_j]);
                    } break;
                }
                result.push_back(board[i][tmp_j]);
            }
            for(int8_t tmp_j = j-1; tmp_j >= static_cast<int8_t>(0); tmp_j--) {
                if(board[i][tmp_j].is_taken()) {
                    if(board[i][tmp_j].is_enemy()) {
                        result.push_back(board[i][tmp_j]);
                    } break;
                }
                result.push_back(board[i][tmp_j]);
            }
            break;
        }
        case Bishop: {
            for(int8_t tmp_i = i+1, tmp_j = j+1; tmp_i < 8 && tmp_j < 8; tmp_i++, tmp_j++) {
                if(board[tmp_i][tmp_j].is_taken()) {
                    if(board[tmp_i][tmp_j].is_enemy()) {
                        result.push_back(board[tmp_i][tmp_j]);
                    } break;
                }
                result.push_back(board[tmp_i][tmp_j]);
            }
            for(int8_t tmp_i = i+1, tmp_j = j-1; tmp_i < 8 && tmp_j >= 0; tmp_i++, tmp_j--) {
                if(board[tmp_i][tmp_j].is_taken()) {
                    if(board[tmp_i][tmp_j].is_enemy()) {
                        result.push_back(board[tmp_i][tmp_j]);
                    } break;
                }
                result.push_back(board[tmp_i][tmp_j]);
            }
            for(int8_t tmp_i = i-1, tmp_j = j+1; tmp_i >= 0 && tmp_j < 8; tmp_i--, tmp_j++) {
                if(board[tmp_i][tmp_j].is_taken()) {
                    if(board[tmp_i][tmp_j].is_enemy()) {
                        result.push_back(board[tmp_i][tmp_j]);
                    } break;
                }
                result.push_back(board[tmp_i][tmp_j]);
            }
            for(int8_t tmp_i = i-1, tmp_j = j-1; tmp_i >= 0 && tmp_j >= 0; tmp_i--, tmp_j--) {
                if(board[tmp_i][tmp_j].is_taken()) {
                    if(board[tmp_i][tmp_j].is_enemy()) {
                        result.push_back(board[tmp_i][tmp_j]);
                    } break;
                }
                result.push_back(board[tmp_i][tmp_j]);
            }
            break;
        }
        case Knight: {
            if(i+1<8 && j+2<8) {
                if(!board[i+1][j+2].is_taken() || board[i+1][j+2].is_enemy()) {
                    result.push_back(board[i+1][j+2]);
                }
            } if(i+1<8 && j-2>=0) {
                if(!board[i+1][j-2].is_taken() || board[i+1][j-2].is_enemy()) {
                    result.push_back(board[i+1][j-2]);
                }
            } if(i-1>=0 && j+2<8) {
                if(!board[i-1][j+2].is_taken() || board[i-1][j+2].is_enemy()) {
                    result.push_back(board[i-1][j+2]);
                }
            } if(i-1>=0 && j-2>=0) {
                if(!board[i-1][j-2].is_taken() || board[i-1][j-2].is_enemy()) {
                    result.push_back(board[i-1][j-2]);
                }
            }

            if(i+2<8 && j+1<8) {
                if(!board[i+2][j+1].is_taken() || board[i+2][j+1].is_enemy()) {
                    result.push_back(board[i+2][j+1]);
                }
            } if(i+2<8 && j-1>=0) {
                if(!board[i+2][j-1].is_taken() || board[i+2][j-1].is_enemy()) {
                    result.push_back(board[i+2][j-1]);
                }
            } if(i-2>=0 && j+1<8) {
                if(!board[i-2][j+1].is_taken() || board[i-2][j+1].is_enemy()) {
                    result.push_back(board[i-2][j+1]);
                }
            } if(i-2>=0 && j-1>=0) {
                if(!board[i-2][j-1].is_taken() || board[i-2][j-1].is_enemy()) {
                    result.push_back(board[i-2][j-1]);
                }
            }
            break;
        }
        case Queen: {
            for(int8_t tmp_i = i+1; tmp_i < 8; tmp_i++) {
                if(board[tmp_i][j].is_taken()) {
                    if(board[tmp_i][j].is_enemy()) {
                        result.push_back(board[tmp_i][j]);
                    } break;
                }
                result.push_back(board[tmp_i][j]);
            }
            for(int8_t tmp_i = i-1; tmp_i >= static_cast<int8_t>(0); tmp_i--) {
                if(board[tmp_i][j].is_taken()) {
    //                    qDebug() << "aaaaaaaaaaaaaa";
                    if(board[tmp_i][j].is_enemy()) {
                        result.push_back(board[tmp_i][j]);
                    } break;
                }
                result.push_back(board[tmp_i][j]);
            }
            for(int8_t tmp_j = j+1; tmp_j < 8; tmp_j++) {
                if(board[i][tmp_j].is_taken()) {
                    if(board[i][tmp_j].is_enemy()) {
                        result.push_back(board[i][tmp_j]);
                    } break;
                }
                result.push_back(board[i][tmp_j]);
            }
            for(int8_t tmp_j = j-1; tmp_j >= static_cast<int8_t>(0); tmp_j--) {
                if(board[i][tmp_j].is_taken()) {
                    if(board[i][tmp_j].is_enemy()) {
                        result.push_back(board[i][tmp_j]);
                    } break;
                }
                result.push_back(board[i][tmp_j]);
            }

            for(int8_t tmp_i = i+1, tmp_j = j+1; tmp_i < 8 && tmp_j < 8; tmp_i++, tmp_j++) {
                if(board[tmp_i][tmp_j].is_taken()) {
                    if(board[tmp_i][tmp_j].is_enemy()) {
                        result.push_back(board[tmp_i][tmp_j]);
                    } break;
                }
                result.push_back(board[tmp_i][tmp_j]);
            }
            for(int8_t tmp_i = i+1, tmp_j = j-1; tmp_i < 8 && tmp_j >= 0; tmp_i++, tmp_j--) {
                if(board[tmp_i][tmp_j].is_taken()) {
                    if(board[tmp_i][tmp_j].is_enemy()) {
                        result.push_back(board[tmp_i][tmp_j]);
                    } break;
                }
                result.push_back(board[tmp_i][tmp_j]);
            }
            for(int8_t tmp_i = i-1, tmp_j = j+1; tmp_i >= 0 && tmp_j < 8; tmp_i--, tmp_j++) {
                if(board[tmp_i][tmp_j].is_taken()) {
                    if(board[tmp_i][tmp_j].is_enemy()) {
                        result.push_back(board[tmp_i][tmp_j]);
                    } break;
                }
                result.push_back(board[tmp_i][tmp_j]);
            }
            for(int8_t tmp_i = i-1, tmp_j = j-1; tmp_i >= 0 && tmp_j >= 0; tmp_i--, tmp_j--) {
                if(board[tmp_i][tmp_j].is_taken()) {
                    if(board[tmp_i][tmp_j].is_enemy()) {
                        result.push_back(board[tmp_i][tmp_j]);
                    } break;
                }
                result.push_back(board[tmp_i][tmp_j]);
            }
            break;
        }
        case King: {
            if(i-1>=0 && (!board[i-1][j].is_taken() || board[i-1][j].is_enemy())) {
                result.push_back(board[i-1][j]);
            } if(i-1>=0 && j-1>=0 && (!board[i-1][j-1].is_taken() || board[i-1][j-1].is_enemy())) {
                result.push_back(board[i-1][j-1]);
            } if(i-1>=0 && j+1<8 && (!board[i-1][j+1].is_taken() || board[i-1][j+1].is_enemy())) {
                result.push_back(board[i-1][j+1]);
            } if(i+1<8 && (!board[i+1][j].is_taken() || board[i+1][j].is_enemy())) {
                result.push_back(board[i+1][j]);
            } if(i+1<8 && j-1>=0 && (!board[i+1][j-1].is_taken() || board[i+1][j-1].is_enemy())) {
                result.push_back(board[i+1][j-1]);
            } if(i+1<8 && j+1<8 && (!board[i+1][j+1].is_taken() || board[i+1][j+1].is_enemy())) {
                result.push_back(board[i+1][j+1]);
            } if(j-1>=0 && (!board[i][j-1].is_taken() || board[i][j-1].is_enemy())) {
                result.push_back(board[i][j-1]);
            } if(j+1<8 && (!board[i][j+1].is_taken() || board[i][j+1].is_enemy())) {
                result.push_back(board[i][j+1]);
            }
            break;
        }
    }
    possible_fields_.clear();
    possible_fields_ = result;
}

//extern QGraphicsScene* scene;

extern Game game;
void Figure::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if(game.turn() != color_) {
        qDebug() << "Nije tvoj red";
        return;
    }
    game.set_picked_figure(this);
    for(int8_t i = 0; i < 8; i++) {
        for(int8_t j = 0; j < 8; j++) {
            board[i][j].reset_color();
        }
    }
    calculate_possible_fields(pos_i_, pos_j_, type_, color_);
    for(auto &&field : possible_fields_) {
        field.set_color(Qt::darkRed);
//        scene->addItem(field.rect_item());
    }

    return;
}

void Figure::advance(int step) {
    setPos(115+4*50, 115+4*50);
}
