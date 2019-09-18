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

    void setBrushColor(QColor color) { brushColor = color; }                      //set/get kolor pedzla
    QColor getBrushColor() { return brushColor; }

    void setBrushWidth(int width) { brushWidth = width; }                         //set/get szerokosc pedzla
    int getBrushWidth() { return brushWidth; }

    void setImage(QPixmap img) { drawingPixmap = img; }                         //set/get obrazka
    QPixmap getImage() { return drawingPixmap; }

    void setFloodFill(bool x) { isFill = x; }                        //set/get wypelnienia
    bool getFloodFill() { return isFill; }

    void setFillColor(QColor color) { fillColor = color; }            //set/get kolor wypelnienia
    QColor getFillColor() { return fillColor; }

    void setShapeLine(bool x) { shapeLine = x;}
    void setShapePen(bool x) { shapePencil = x;}
    void setShapeSquare(bool x) { shapeSquare = x;}                    //set ksztaltow
    void setShapeCircle(bool x) { shapeCircle = x;}
    void setShapeTriangle(bool x) { shapeTriangle = x;}

    bool saveImage();                                                   //zapis obrazka
    bool openImage();                                                   //otworzenie obrazka
    void invertColors();                                                //odwrocenie kolorow obrazka
    void cutImage();                                                    //wyciecie obrazka
    void pasteImage();                                                  //wklejenie obrazka


protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;                     //eventy na zmiane wymiarow/rysowanie/myszke
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;


private:
    QColor brushColor;           //kolor pedzla
    QColor fillColor;      //kolor wypelnienia
    int brushWidth;              //grubosc pedzla

    QPixmap drawingPixmap;          //pixmapa po ktorej bedzie rysowane
    QPixmap cutPixmap;    //pixmapa na wyciety obrazek

    bool isDrawing;           //czy jest teraz rysowane
    bool mousePressed;      //czy wcisnieto przycisk myszki
    bool isFill;         //czy wypelniac

    QPoint lastPoint;       //ostatni pkt dla olowka (dla eventow press/move/release mouse)
    QLine pointsLine;       //zapisuje 2 punkty rysowanych linii

    bool shapePencil;
    bool shapeLine;
    bool shapeSquare;      //ksztalty
    bool shapeCircle;
    bool shapeTriangle;

    void resizeImage(QPixmap *, QSize);                                 //zmiana rozmiaru obrazka o nowe wymiary


public slots:
    void clearImage();                                                       //wyczyszczenie obrazka

};

#endif // CANVAS_H
