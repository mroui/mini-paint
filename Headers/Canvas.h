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

    void setBrushColor(QColor);
    QColor getBrushColor();

    void setBrushWidth(int);
    int getBrushWidth();

    void setImage(QPixmap);
    QPixmap getImage();

    void setFloodFill(bool);
    bool getFloodFill();

    void setFillColor(QColor);
    QColor getFillColor();

    void setShapeLine(bool);
    void setShapePencil(bool);
    void setShapeSquare(bool);
    void setShapeCircle(bool);
    void setShapeTriangle(bool);

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
