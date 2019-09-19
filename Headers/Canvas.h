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

    void setBrushColor(QColor);                      //set/get methods of basic variables
    QColor getBrushColor();

    void setBrushWidth(int);
    int getBrushWidth();

    void setImage(QPixmap);
    QPixmap getImage();

    void setFloodFill(bool);
    bool getFloodFill();

    void setFillColor(QColor);
    QColor getFillColor();

    void setShapeLine(bool);                        //set selected shapes
    void setShapePencil(bool);
    void setShapeSquare(bool);
    void setShapeCircle(bool);
    void setShapeTriangle(bool);

    bool saveImage();                               //save image - QFileDialog with specific formats
    bool openImage();                               //open image - QFileDialog with specific formats
    void invertColors();                            //make new one image with inverted colors and change with previous
    void cutImage();                                //save recent image & clear canvas
    void pasteImage();                              //change recent image with the cut one


protected:
    void mousePressEvent(QMouseEvent *) override;   //set clicked mouse position points
    void mouseMoveEvent(QMouseEvent *) override;    //check mouse position changes & set new position
    void mouseReleaseEvent(QMouseEvent *) override; //set finish of drawing - mouse moving
    void paintEvent(QPaintEvent *) override;        //main drawing event
    void resizeEvent(QResizeEvent *) override;      //resize image event


private:
    QColor brushColor;
    QColor fillColor;
    int brushWidth;

    QPixmap drawingPixmap;                          //drawing field
    QPixmap cutPixmap;                              //cut image to paste it

    bool isDrawing;                                 //if is drawing - mouse pressed & moving
    bool mousePressed;                              //if mouse is pressed
    bool isFill;                                    //if fill button is clicked

    QPoint lastPoint;                               //last released point to draw by pencil
    QLine pointsLine;                               //points to draw line

    bool shapePencil;                               //selected shapes
    bool shapeLine;
    bool shapeSquare;
    bool shapeCircle;
    bool shapeTriangle;

    void resizeImage(QPixmap *, QSize);             //create & set new image with new dimensions


public slots:
    void clearImage();                              //fill image by white color

};

#endif // CANVAS_H
