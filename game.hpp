#ifndef GAME_HPP
#define GAME_HPP

#include "figure.hpp"

enum phase {
    pick_figure,
    pick_field
};

class Game {
public:
    Game(figure_color turn = White, phase current_phase = pick_figure,
         Figure* picked_figure = nullptr)
        : turn_(turn)
        , current_phase_(current_phase)
        , picked_figure_(picked_figure) { }

    void end_turn() {
        turn_ = turn_ == White ? Black : White;
        current_phase_ = pick_figure;
        picked_figure_->clear_fields();
    }

    void set_current_phase(phase p) {
        current_phase_ = p;
    }

    phase current_phase() const {
        return current_phase_;
    }
    Figure* picked_figure() const {
        return picked_figure_;
    }
    void set_picked_figure(Figure* picked_figure) {
        picked_figure_ = picked_figure;
    }

    void set_scene(QGraphicsScene * scene) {
        scene_ = scene;
    }

    figure_color turn() const {
        return turn_;
    }

    QGraphicsScene* scene() const {
        return scene_;
    }

private:
    figure_color turn_;
    phase current_phase_;
    Figure* picked_figure_;
    QGraphicsScene* scene_;
};

#endif
