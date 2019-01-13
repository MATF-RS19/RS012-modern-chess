#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <string>
#include <QGraphicsItem>
#include "field.hpp"

extern Field board[8][8];
class Figure : public QGraphicsItem {
public:
    Figure(figure_type type,
           int8_t i, int8_t j,
           figure_color color,
           QRectF rect)
        : type_(type)
        , pos_i_(i)
        , pos_j_(j)
        , color_(color)
        , rect_(rect) { }

    char get_hor() const {
        return 'A' + pos_i_;
    }

    char get_ver() const {
        return '1' + pos_j_;
    }

    std::vector<Field> possible_fields() const {
        return possible_fields_;
    }

    void set_pos_i(int8_t i) {
        pos_i_ = i;
    }

    void set_pos_j(int8_t j) {
        pos_j_ = j;
    }

    int8_t pos_i() const {
        return pos_i_;
    }

    int8_t pos_j() const {
        return pos_j_;
    }

    figure_color color() const {
        return color_;
    }

    Figure(const Figure &other)
        : type_(other.type_)
        , pos_i_(other.pos_i_)
        , pos_j_(other.pos_j_)
        , color_(other.color_)
        , rect_(other.rect_) { }

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

    void clear_fields() {
        possible_fields_.clear();
        for(int8_t i = 0; i < 8; i++) {
            for(int8_t j = 0; j < 8; j++) {
                board[i][j].reset_color();
            }
        }
    }
protected:
    void advance(int step) override;

private:
    void calculate_possible_fields(int8_t i, int8_t j,
                                                 figure_type type, QColor color);
    bool check_if_check();
    void limit_king_movement();
    void in_case_of_check();
    bool is_checkmate();
    figure_type type_;
    int8_t pos_i_, pos_j_;
    figure_color color_;
    QRectF rect_;
    std::vector<Field> possible_fields_;
};

#endif // FIGURE_HPP
