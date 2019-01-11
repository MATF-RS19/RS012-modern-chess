#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>

// C++17 je neophodan za zaglavlje <optional>
// Obratite paznju na pro datoteku, neophodno je dodati zastavicu --std=c++17.
// alternativa -> boost::optional
// Domaci: pokusajte zameniti std::optional sa boost::optional tipom.
#include <optional>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pick_field_clicked(bool);
    void on_next_turn_clicked(bool);

private:
    void populateScene();

    QGraphicsScene* scene_;
    Ui::MainWindow *ui_;
};

#endif // MAINWINDOW_HPP
