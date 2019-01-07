#include <QGraphicsRectItem>
#include <QGraphicsView>

class Field {
public:
//    Field(QGraphicsRectItem* rect_item = new QGraphicsRectItem(),
//          bool taken = false,
//          QColor color = Qt::black)
//        : rect_item_(rect_item_)
//        , taken_(taken)
//        , color_(color) { }

    Field(bool taken = false)
        : taken_(taken) {
        rect_item_ = new QGraphicsRectItem();
    }

    bool is_taken() const {
        return taken_;
    }

    void set_taken(bool b) {
        taken_ = b;
    }

    bool is_enemy() const {
        return false; // TODO
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

private:
    QGraphicsRectItem* rect_item_;
    bool taken_;
    QColor color_;
    QColor old_color_;
};
