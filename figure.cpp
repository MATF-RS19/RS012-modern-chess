#include "figure.hpp"
#include <QPainter>

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

void Figure::mousePressEvent(QGraphicsSceneMouseEvent * event) {

}

void Figure::advance(int step) {

}
