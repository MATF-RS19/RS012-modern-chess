#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <string>
#include <QGraphicsItem>

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

class Figure : public QGraphicsItem {
public:
    Figure(figure_type type,
           uint8_t i, uint8_t j,
           figure_color color,
           QRectF rect)
        : type_(type)
        , pos_i_(i)
        , pos_j_(j)
        , color_(color)
        , rect_(rect) { }

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

protected:
    void advance(int step) override;

private:
    figure_type type_;
    uint8_t pos_i_, pos_j_;
    figure_color color_;
    QRectF rect_;
};

#endif // FIGURE_HPP
