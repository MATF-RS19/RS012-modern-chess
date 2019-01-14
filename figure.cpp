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

// render figures
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

// check all sorts of constraints
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
                    } if(i == 6) {
                        if(!board[i-1][j].is_taken() && !board[i-2][j].is_taken()) {
                            result.push_back(board[i-2][j]);
                        }
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
                    } if(i == 1) {
                        if(!board[i+1][j].is_taken() && !board[i+2][j].is_taken()) {
                            result.push_back(board[i+2][j]);
                        }
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
        // the king must simulate the opponents movements
        // before he moves to a certain field we first must check
        // will there be a check if he goes there
        case King: {
            if(i-1>=0 && (!board[i-1][j].is_taken() || board[i-1][j].is_enemy())) {

                pos_i_ = i-1;
                pos_j_ = j;
                board[i][j].set_taken(false);
                board[i-1][j].set_taken(true);
                if(!check_if_check()) {
                    result.push_back(board[i-1][j]);
                }
                pos_i_ = i;
                pos_j_ = j;
                board[i][j].set_taken(true);
                board[i-1][j].set_taken(false);

            } if(i-1>=0 && j-1>=0 && (!board[i-1][j-1].is_taken() || board[i-1][j-1].is_enemy())) {

                pos_i_ = i-1;
                pos_j_ = j-1;
                board[i][j].set_taken(false);
                board[i-1][j-1].set_taken(true);
                if(!check_if_check()) {
                    result.push_back(board[i-1][j-1]);
                }
                pos_i_ = i;
                pos_j_ = j;
                board[i][j].set_taken(true);
                board[i-1][j-1].set_taken(false);

            } if(i-1>=0 && j+1<8 && (!board[i-1][j+1].is_taken() || board[i-1][j+1].is_enemy())) {

                pos_i_ = i-1;
                pos_j_ = j+1;
                board[i][j].set_taken(false);
                board[i-1][j+1].set_taken(true);
                if(!check_if_check()) {
                    result.push_back(board[i-1][j+1]);
                }
                pos_i_ = i;
                pos_j_ = j;
                board[i][j].set_taken(true);
                board[i-1][j+1].set_taken(false);


            } if(i+1<8 && (!board[i+1][j].is_taken() || board[i+1][j].is_enemy())) {

                pos_i_ = i+1;
                pos_j_ = j;
                board[i][j].set_taken(false);
                board[i+1][j].set_taken(true);
                if(!check_if_check()) {
                    result.push_back(board[i+1][j]);
                }
                pos_i_ = i;
                pos_j_ = j;
                board[i][j].set_taken(true);
                board[i+1][j].set_taken(false);

            } if(i+1<8 && j-1>=0 && (!board[i+1][j-1].is_taken() || board[i+1][j-1].is_enemy())) {

                pos_i_ = i+1;
                pos_j_ = j-1;
                board[i][j].set_taken(false);
                board[i+1][j-1].set_taken(true);
                if(!check_if_check()) {
                    result.push_back(board[i+1][j-1]);
                }
                pos_i_ = i;
                pos_j_ = j;
                board[i][j].set_taken(true);
                board[i+1][j-1].set_taken(false);

            } if(i+1<8 && j+1<8 && (!board[i+1][j+1].is_taken() || board[i+1][j+1].is_enemy())) {

                pos_i_ = i+1;
                pos_j_ = j+1;
                board[i][j].set_taken(false);
                board[i+1][j+1].set_taken(true);
                if(!check_if_check()) {
                    result.push_back(board[i+1][j+1]);
                }
                pos_i_ = i;
                pos_j_ = j;
                board[i][j].set_taken(true);
                board[i+1][j+1].set_taken(false);


            } if(j-1>=0 && (!board[i][j-1].is_taken() || board[i][j-1].is_enemy())) {

                pos_i_ = i;
                pos_j_ = j-1;
                board[i][j].set_taken(false);
                board[i][j-1].set_taken(true);
                if(!check_if_check()) {
                    result.push_back(board[i][j-1]);
                }
                pos_i_ = i;
                pos_j_ = j;
                board[i][j].set_taken(true);
                board[i][j-1].set_taken(false);


            } if(j+1<8 && (!board[i][j+1].is_taken() || board[i][j+1].is_enemy())) {

                pos_i_ = i;
                pos_j_ = j+1;
                board[i][j].set_taken(false);
                board[i][j+1].set_taken(true);
                if(!check_if_check()) {
                    result.push_back(board[i][j+1]);
                }
                pos_i_ = i;
                pos_j_ = j;
                board[i][j].set_taken(true);
                board[i][j+1].set_taken(false);


            }
            break;
        }
    }
    possible_fields_.clear();
    possible_fields_ = result;
}


extern std::vector<Figure*> white_fig;
extern std::vector<Figure*> black_fig;
extern Game game;
extern figure_color current_turn;
// check has there been a check
bool Figure::check_if_check() {
    if(color_ == White) {
        for(const auto &fig : black_fig) {
            if(fig->type_ == King) continue;
            current_turn = current_turn == White ? Black : White;
            fig->calculate_possible_fields(fig->pos_i(), fig->pos_j(), fig->type_, fig->color_);
            current_turn = current_turn == White ? Black : White;
            for(const auto &fieldEnemy : fig->possible_fields_) {
                for(const auto& figKing : white_fig) {
                    if(figKing->type_ == King) {
                        if(fieldEnemy == board[figKing->pos_i_][figKing->pos_j_]) {
//                            qDebug("---%c %c---", fig->get_hor(), fig->get_ver());
                            return true;
                        }
                        break;
                    }
                }
            }
        }
    } else if(color_ == Black) {
        for(const auto &fig : white_fig) {
            if(fig->type_ == King) continue;
            current_turn = current_turn == White ? Black : White;
            fig->calculate_possible_fields(fig->pos_i(), fig->pos_j(), fig->type_, fig->color_);
            current_turn = current_turn == White ? Black : White;
            for(const auto &fieldEnemy : fig->possible_fields_) {
                for(const auto& figKing : black_fig) {
                    if(figKing->type_ == King) {
                        if(fieldEnemy == board[figKing->pos_i_][figKing->pos_j_]) {
                            return true;
                        }
                        break;
                    }
                }
            }
        }
    }
    return false;
}

// if check occured the kings movements have been constrained
void Figure::limit_king_movement() {
    std::vector<Field> checked;
    if(color_ == White) {
        for(const auto &fig : black_fig) {
            int k = 0;
            for(auto &&fieldKing : possible_fields_) {
                for(const auto &fieldEnemy : fig->possible_fields_) {
                    if(fieldKing == fieldEnemy) {
                        bool cont = false;
                        for(const auto &c : checked) {
                            if(c == fieldKing) {
                                cont = true;
                                break;
                            }
                        }
                        if(!cont) {
                            checked.push_back(fieldKing);
                            possible_fields_.erase(possible_fields_.begin() + k);
                        }
                    }
                }
                k++;
            }
        }
    } else if(color_ == Black) {
        for(const auto &fig : white_fig) {
            int k = 0;
            for(auto &&fieldKing : possible_fields_) {
                for(const auto &fieldEnemy : fig->possible_fields_) {
                    if(fieldKing == fieldEnemy) {
                        bool cont = false;
                        for(const auto &c : checked) {
                            if(c == fieldKing) {
                                cont = true;
                                break;
                            }
                        }
                        if(!cont) {
                            checked.push_back(fieldKing);
                            possible_fields_.erase(possible_fields_.begin() + k);
                        }
                    }
                }
                k++;
            }
        }
    }
}

// limit the movement of friendly figures if check occured
// they must defend their king
void Figure::in_case_of_check() {
    std::vector<Field> tmp_possible_fields;
    for(auto&& field : possible_fields_) {
        if(!field.is_taken()) {
            board[field.i()][field.j()].set_taken(true);
            bool check = check_if_check();
            board[field.i()][field.j()].set_taken(false);
            if(!check) {
                tmp_possible_fields.push_back(field);
            }
        } else if(field.is_enemy()) {
            if(color_ == Black) {
                int k = 0;
                for(auto&& enemyFig : white_fig) {
                    if(enemyFig->pos_i_ == field.i() && enemyFig->pos_j_ == field.j()) {
                        auto tmp = *(white_fig.begin() + k);
                        white_fig.erase(white_fig.begin() + k);
                        bool check = check_if_check();
                        white_fig.push_back(tmp);
                        if(!check) {
                            tmp_possible_fields.push_back(field);
                        }
                        break;
                    }
                    k++;
                }
            } else if(color_ == White) {
                int k = 0;
                for(auto&& enemyFig : black_fig) {
                    if(enemyFig->pos_i_ == field.i() && enemyFig->pos_j_ == field.j()) {
                        auto tmp = *(black_fig.begin() + k);
                        black_fig.erase(black_fig.begin() + k);
                        bool check = check_if_check();
                        black_fig.push_back(tmp);
                        if(!check) {
                            tmp_possible_fields.push_back(field);
                        }
                        break;
                    }
                    k++;
                }
            }
        }
    }
    possible_fields_ = tmp_possible_fields;
    if(color_ == White) {
        for(const auto &fig : white_fig) {
            if(fig->type_ == King) {
                board[fig->pos_i_][fig->pos_j_].set_color(Qt::darkRed);
                break;
            }
        }
    } else if(color_ == Black) {
        for(const auto &fig : black_fig) {
            if(fig->type_ == King) {
                board[fig->pos_i_][fig->pos_j_].set_color(Qt::darkRed);
                break;
            }
        }
    }
}

// this function is called if check occured
// it check has checkmate occured
bool Figure::is_checkmate() {
    if(color_ == White) {
        for(auto&& fig : white_fig) {
            fig->calculate_possible_fields(fig->pos_i(), fig->pos_j(), fig->type_, fig->color());
            fig->in_case_of_check();
            if(fig->possible_fields_.size() != 0) {
                return false;
            }
        }
    } else if(color_ == Black) {
        for(auto&& fig : black_fig) {
            fig->calculate_possible_fields(fig->pos_i(), fig->pos_j(), fig->type_, fig->color());
            fig->in_case_of_check();
            if(fig->possible_fields_.size() != 0) {
                qDebug("Nije sah mat zbog %c %c", fig->get_hor(), fig->get_ver());
                return false;
            }
        }
    }
    return true;
}

// color all avaivable fields of the clicked figure
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
    bool check = check_if_check();

    if(type_ == King) {
        limit_king_movement();
    }
    if(check) {
        qDebug() << "Sah";
        in_case_of_check();
        bool checkmate = is_checkmate();
        if(checkmate) {
            qDebug() << "CHECKMATE";
            exit(EXIT_SUCCESS);
        }
    }
    board[pos_i_][pos_j_].set_color(Qt::green);
    for(auto &&field : possible_fields_) {
        if(field.is_enemy()) {
            field.set_color(Qt::red);
        } else {
            field.set_color(Qt::blue);
        }
    }
    return;
}

void Figure::advance(int step) {

}
