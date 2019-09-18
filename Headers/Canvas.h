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

    bool saveImage();
    bool openImage();
    void invertColors();
    void cutImage();
    void pasteImage();


protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;


private:
    QColor brushColor;
    QColor fillColor;
    int brushWidth;

    QPixmap drawingPixmap;
    QPixmap cutPixmap;

    bool isDrawing;
    bool mousePressed;
    bool isFill;

    QPoint lastPoint;
    QLine pointsLine;

    bool shapePencil;
    bool shapeLine;
    bool shapeSquare;
    bool shapeCircle;
    bool shapeTriangle;

    void resizeImage(QPixmap *, QSize);


public slots:
    void clearImage();

};

#endif // CANVAS_H
