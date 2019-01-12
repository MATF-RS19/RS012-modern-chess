#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDebug>

enum figure_type {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

enum figure_color {
    Black,
    White
};

extern figure_color current_turn;

class Field {
public:
//    Field(QGraphicsRectItem* rect_item = new QGraphicsRectItem(),
//          bool taken = false,
//          QColor color = Qt::black)
//        : rect_item_(rect_item_)
//        , taken_(taken)
//        , color_(color) { }

    Field(int8_t i=0, int8_t j=0,
          bool taken = false,
          figure_color fig_col = White)
        : i_(i)
        , j_(j)
        , taken_(taken)
        , fig_col_(fig_col) {
        rect_item_ = new QGraphicsRectItem();
    }

    void set_i(int8_t i) {
        i_ = i;
    }

    void set_j(int8_t j) {
        j_ = j;
    }

    int8_t i() const {
        return i_;
    }

    int8_t j() const {
        return j_;
    }

    bool is_taken() const {
        return taken_;
    }

    void set_taken(bool b) {
        taken_ = b;
    }

    bool is_enemy() const {
        if(taken_) {
            return fig_col_ != current_turn;
        } return false;
    }

    QGraphicsRectItem* rect_item() const {
        return rect_item_;
    }

    void set_rect(QRectF rect) {
        rect_item_->setRect(rect);
    }

    void set_initial_color(QColor color) {
        old_color_ = color;
    }

    void set_color(QColor color) {
        color_ = color;
        rect_item_->setBrush(color_);
    }

    void reset_color() {
        color_ = old_color_;
        rect_item_->setBrush(color_);
    }

    void set_fig_col(figure_color fig_col) {
        fig_col_ = fig_col;
    }

private:
    int8_t i_, j_;
    QGraphicsRectItem* rect_item_;
    bool taken_; 
    QColor color_;
    QColor old_color_;
    figure_color fig_col_;
};
