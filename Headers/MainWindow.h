#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QSizeGrip>
#include <QMessageBox>
#include <QScrollArea>

#include "Headers/Canvas.h"
#include "Headers/ResizeImage.h"
#include "Headers/StretchImage.h"

namespace Ui
{ class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setColorBiggerFunction();              //set brush color by check selected color on palette
    void ifFillThenColor(QColor);               //set fill color or brush color
    void setShapes(QString);                    //set shape of pencil

private slots:
    void on_Bialy_clicked();
    void on_Czarny_clicked();
    void on_Szary_clicked();
    void on_Czerwony_clicked();
    void on_Zolty_clicked();
    void on_Niebieski_clicked();
    void on_Zielony_clicked();
    void on_Rozowy_clicked();
    void on_Fioletowy_clicked();
    void on_Pomaranczowy_clicked();
    void on_palette_2_clicked();

protected:
    void closeEvent(QCloseEvent *) override;

private:
    Ui::MainWindow *ui;
    Canvas * canvas;                            //drawing object
    QColor previouspalettecolor;                //previous checked color in palette
    QSizeGrip * sizeGrip;                       //grip to increase image

private slots:
    void on_ButtonGumka_clicked();
    void on_ButtonOlowek_clicked();
    void on_SpinBoxGruboscLinii_valueChanged(int);
    void on_ButtonLinia_clicked();
    void on_ButtonKwadrat_clicked();            //clicked/valuechanged events on toolbar
    void on_ButtonKolo_clicked();
    void on_ButtonTrojkat_clicked();
    void on_ButtonWypelnienie_clicked();

    void on_action_Nowy_triggered();
    void on_action_Otworz_triggered();
    void on_actionZapisz_jako_triggered();      //menubar/file events
    void on_actionZako_cz_triggered();

    void on_actionWyczy_obraz_triggered();
    void on_actionOdwr_kolory_triggered();
    void on_actionOdwr_triggered();             //menubar/image events
    void on_actionZmie_rozmiar_triggered();
    void on_actionRozci_gnij_triggered();
    void on_actionWytnij_triggered();
    void on_actionWklej_triggered();

    void on_actionZmie_kolor_triggered();       //menubar/colors events

    void on_actionO_Oprogramie_triggered();     //menubar/help events
};

#endif // MAINWINDOW_H
