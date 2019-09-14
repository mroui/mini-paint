#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QSizeGrip>
#include <QMessageBox>
#include <QScrollArea>

#include <Headers/Canvas.h>
#include <Headers/ResizeImage.h>
#include <Headers/StretchImage.h>

namespace Ui
{ class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setColorBiggerFunction();              //sprawdza ktory kolor (button) zostal wciśnięty i ten kolor ustawia na pędzlu w canvasie
    void ifFillThenColor(QColor);               //sprawdza czy nacisnieto przycisk wypelnienia wtedy ustawia kolor pedzla/wypelnienia
    void setShapes(QString);                    //ustawia kolor pedzla + ustawia ksztalty na false poza tym w argumencie

private slots:
    void on_Bialy_clicked();
    void on_Czarny_clicked();
    void on_Szary_clicked();
    void on_Czerwony_clicked();
    void on_Zolty_clicked();
    void on_Niebieski_clicked();                //eventy buttonclicked kolorow
    void on_Zielony_clicked();
    void on_Rozowy_clicked();
    void on_Fioletowy_clicked();
    void on_Pomaranczowy_clicked();
    void on_palette_2_clicked();

protected:
    void closeEvent(QCloseEvent *) override;    //event zamykania okna

private:
    Ui::MainWindow *ui;

    Canvas * canvas;                            //obiekt obrazu
    QColor previouspalettecolor;                //poprzedni kolor wybrany z palety (dialogcolor) - by go zapamiętać
    QSizeGrip * sizeGrip;                       //suwak do zwiększania obrazu

private slots:
    void on_ButtonGumka_clicked();
    void on_ButtonOlowek_clicked();
    void on_SpinBoxGruboscLinii_valueChanged(int);
    void on_ButtonLinia_clicked();
    void on_ButtonKwadrat_clicked();            //eventy buttonclicked/valuechanged na narzedziach (kolo, trojkat, olowek, gumka, wypelnienie...)
    void on_ButtonKolo_clicked();
    void on_ButtonTrojkat_clicked();
    void on_ButtonWypelnienie_clicked();


    void on_action_Nowy_triggered();
    void on_action_Otworz_triggered();
    void on_actionZapisz_jako_triggered();      //eventy dla menubar/Plik: nowy, otworz, zapisz, zakoncz
    void on_actionZako_cz_triggered();

    void on_actionWyczy_obraz_triggered();
    void on_actionOdwr_kolory_triggered();
    void on_actionOdwr_triggered();             //eventy dla menubar/Obraz: wyczyscObraz, odwrocKolory, odwrocObraz, zmienRozmiar, rozciagnij, wytnij, wklej
    void on_actionZmie_rozmiar_triggered();
    void on_actionRozci_gnij_triggered();
    void on_actionWytnij_triggered();
    void on_actionWklej_triggered();

    void on_actionZmie_kolor_triggered();       //event dla menubar/Kolory: zmien kolor

    void on_actionO_Oprogramie_triggered();     //event dla menubar/Pomoc: o programie
};

#endif // MAINWINDOW_H
