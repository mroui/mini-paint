#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);


    void setColor(QColor color) { Color = color; }                      //set/get kolor pedzla
    QColor getColor() { return Color; }


    void setWidth(int width) { Width = width; }                         //set/get szerokosc pedzla
    int getWidth() { return Width; }


    void setImage(QPixmap img) { Image = img; }                         //set/get obrazka
    QPixmap getImage() { return Image; }


    void setFloodFill(bool x) { floodfill = x; }                        //set/get wypelnienia
    bool getFloodFill() { return floodfill; }


    void setBrushColor(QColor color) { BrushColor = color; }            //set/get kolor wypelnienia
    QColor getBrushColor() { return BrushColor; }


    void setShapeLine(bool x) { shape_line = x;}
    void setShapePen(bool x) { shape_pencil = x;}
    void setShapeSquare(bool x) { shape_square = x;}                    //set ksztaltow
    void setShapeCircle(bool x) { shape_circle = x;}
    void setShapeTriangle(bool x) { shape_triangle = x;}


    bool saveImage();                                                   //zapis obrazka
    bool openImage();                                                   //otworzenie obrazka
    void invertColors();                                                //odwrocenie kolorow obrazka
    void cutImage();                                                    //wyciecie obrazka
    void pasteImage();                                                  //wklejenie obrazka


public slots:
    void clear();                                                       //wyczyszczenie obrazka


protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;                     //eventy na zmiane wymiarow/rysowanie/myszke
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;

private:
    QColor Color;           //kolor pedzla
    QColor BrushColor;      //kolor wypelnienia
    int Width;              //grubosc pedzla

    QPixmap Image;          //pixmapa po ktorej bedzie rysowane
    QPixmap CuttedImage;    //pixmapa na wyciety obrazek

    bool drawing;           //czy jest teraz rysowane
    bool mousePressed;      //czy wcisnieto przycisk myszki
    bool floodfill;         //czy wypelniac

    QPoint lastPoint;       //ostatni pkt dla olowka (dla eventow press/move/release mouse)
    QLine pointsLine;       //zapisuje 2 punkty rysowanych linii

    bool shape_pencil;
    bool shape_line;
    bool shape_square;      //ksztalty
    bool shape_circle;
    bool shape_triangle;


    void resizeImage(QPixmap *, QSize);                                 //zmiana rozmiaru obrazka o nowe wymiary
};

#endif // CANVAS_H
