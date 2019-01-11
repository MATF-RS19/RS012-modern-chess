#include "field.hpp"
#include "game.hpp"
#include <QDebug>


extern Game game;
void Field::mousePressEvent(QGraphicsSceneMouseEvent * event) {

    qDebug() << "tu sam jebem ti mater";
    if(game.current_phase() == pick_field) {
        Figure fig = game.picked_figure();
        fig.update(rect_item_->rect());
        game.end_turn();
    }
}

void Field::advance(int step) {

}
