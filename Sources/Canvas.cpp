#include "Headers/Canvas.h"


//set default settings & initiate objects
Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);

    drawingPixmap = QPixmap(width(),height());
    drawingPixmap.fill(Qt::white);

    isDrawing = false;
    mousePressed = false;
    isFill = false;

    shapePencil=true;
    shapeLine = false;
    shapeSquare = false;
    shapeCircle = false;
    shapeTriangle = false;
}


//set/get methods
//---------------------------------------------------------------------------------


void Canvas::setBrushColor(QColor color)
{
    brushColor = color;
}

QColor Canvas::getBrushColor()
{
    return brushColor;
}

void Canvas::setBrushWidth(int width)
{
    brushWidth = width;
}

int Canvas::getBrushWidth()
{
    return brushWidth;
}

void Canvas::setImage(QPixmap img)
{
    drawingPixmap = img;
}

QPixmap Canvas::getImage()
{
    return drawingPixmap;
}

void Canvas::setFloodFill(bool f)
{
    isFill = f;
}

bool Canvas::getFloodFill()
{
    return isFill;
}

void Canvas::setFillColor(QColor color)
{
    fillColor = color;
}

QColor Canvas::getFillColor()
{
    return fillColor;
}

void Canvas::setShapeLine(bool x)
{
    shapeLine = x;
}

void Canvas::setShapePencil(bool x)
{
    shapePencil = x;
}

void Canvas::setShapeSquare(bool x)
{
    shapeSquare = x;
}

void Canvas::setShapeCircle(bool x)
{
    shapeCircle = x;
}

void Canvas::setShapeTriangle(bool x)
{
    shapeTriangle = x;
}


//save image in JPEG/PNG/BMP format
//----------------------------------------------------------------------------------


bool Canvas::saveImage()
{
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save As..."), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp)" ));

    if (!imagePath.isEmpty())
    {
      if (drawingPixmap.save(imagePath))
        return true;
    }
    return false;
}


//open image in JPEG/PNG/BMP formats
//----------------------------------------------------------------------------------


bool Canvas::openImage()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open..."), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp)" ));

    if (!imagePath.isEmpty())
    {
      if (drawingPixmap.load(imagePath))
        return true;
    }
    return false;
}


//invert colors -> make new one with inverted colors and change with previous
//----------------------------------------------------------------------------------


void Canvas::invertColors()
{
    QImage image = drawingPixmap.toImage();
    image.invertPixels(QImage::InvertRgba);
    setImage(QPixmap::fromImage(image));
    update();
}


//cut image -> save&clear recent image
//----------------------------------------------------------------------------------


void Canvas::cutImage()
{
    cutPixmap = drawingPixmap;
    clearImage();
}


//paste image -> paste cut image in left top corner
//----------------------------------------------------------------------------------


void Canvas::pasteImage()
{
    QPainter pasteontop(&drawingPixmap);
    QRect rect = cutPixmap.rect();
    pasteontop.drawPixmap(rect,cutPixmap,rect);
    update();
}


//press mouse event
//----------------------------------------------------------------------------------


void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (shapePencil) lastPoint = event->pos();

        mousePressed = true;
        pointsLine.setP1(event->pos());
        pointsLine.setP2(event->pos());
        isDrawing = true;
    }
}


//move mouse event
//----------------------------------------------------------------------------------


void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && isDrawing)
        pointsLine.setP2(event->pos());
    update();
}


//release mouse event
//----------------------------------------------------------------------------------


void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        isDrawing = false;
        mousePressed = false;
        update();
    }
}


//drawing event - check drawing flag & shape & fill & draw
//----------------------------------------------------------------------------------


void Canvas::paintEvent(QPaintEvent *event)
{
    static bool wasPressed = false;
    QRect dirtyRect = event->rect();
    QPainter painter(this);

    painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect); //get dimensions & draw white image in the beginning

    if(mousePressed)
    {
        wasPressed = true;
        painter.setPen(QPen(brushColor, brushWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));   //set brush settings

        if(shapePencil)
        {
            QPainter paintimg(&drawingPixmap);
            paintimg.setPen(QPen(brushColor, brushWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            paintimg.drawLine(lastPoint, pointsLine.p2());
            lastPoint = pointsLine.p2();
        }
        else if(shapeLine)
        {
            painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect);
            painter.drawLine(pointsLine);
        }
        else if(shapeSquare)
        {
            painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect);

            QRect rect;
            rect.setTopLeft(pointsLine.p1());
            rect.setBottomRight(pointsLine.p2());
            painter.drawRect(rect);

            if (isFill) //check if fill in square, triangle, circle
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addRoundedRect(rect,brushWidth, brushWidth);
                painter.fillPath(path,fillbrush);
            }
        }
        else if(shapeTriangle)
        {
            painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect);

            QPoint *points = new QPoint[3];
            points[0] = QPoint(pointsLine.x1(),pointsLine.y2());
            points[1] = QPoint(((pointsLine.x1()+pointsLine.x2())/2),pointsLine.y1());
            points[2] = QPoint(pointsLine.x2(), pointsLine.y2());

            QPolygon polygon;
            polygon<<points[0]<<points[1]<<points[2];
            painter.drawPolygon(polygon);

            if (isFill)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addPolygon(polygon);
                painter.fillPath(path,fillbrush);
            }
        }
        else if(shapeCircle)
        {
            painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect);

            QRect rect;
            rect.setTopLeft(pointsLine.p1());
            rect.setBottomRight(pointsLine.p2());
            painter.drawEllipse(rect);

            if (isFill)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addEllipse(rect);
                painter.fillPath(path,fillbrush);
            }
        }
    }
    else if(wasPressed) //joining with current image
    {
        wasPressed = false;

        QPainter PixmapPainter(&drawingPixmap);
        PixmapPainter.setPen(QPen(brushColor, brushWidth, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));

        if(shapePencil)
        {
            painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect);
        }
        else if(shapeLine)
        {
            PixmapPainter.drawLine(pointsLine);
            painter.drawPixmap(0, 0, drawingPixmap);
        }
        else if(shapeSquare)
        {
            QRect rect;
            rect.setTopLeft(pointsLine.p1());
            rect.setBottomRight(pointsLine.p2());
            PixmapPainter.drawRect(rect);

            if (isFill)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addRoundedRect(rect,brushWidth, brushWidth);
                PixmapPainter.fillPath(path,fillbrush);
            }

            painter.drawPixmap(0, 0, drawingPixmap);
        }
        else if(shapeCircle)
        {
            QRect rect;
            rect.setTopLeft(pointsLine.p1());
            rect.setBottomRight(pointsLine.p2());
            PixmapPainter.drawEllipse(rect);

            if (isFill)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addEllipse(rect);
                PixmapPainter.fillPath(path,fillbrush);
            }

            painter.drawPixmap(0, 0, drawingPixmap);
        }
        else if(shapeTriangle)
        {
            QRect rect;
            rect.setTopLeft(pointsLine.p1());
            rect.setBottomRight(pointsLine.p2());

            QPoint *points = new QPoint[3];
            points[0] = QPoint(pointsLine.x1(),pointsLine.y2());
            points[1] = QPoint(((pointsLine.x1()+pointsLine.x2())/2),pointsLine.y1());
            points[2] = QPoint(pointsLine.p2());

            QPolygon polygon;
            polygon<<points[0]<<points[1]<<points[2];
            PixmapPainter.drawPolygon(polygon);

            if (isFill)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addPolygon(polygon);
                PixmapPainter.fillPath(path,fillbrush);
            }

            painter.drawPixmap(0, 0, drawingPixmap);
        }
    }
}


//resize image event
//----------------------------------------------------------------------------------


void Canvas::resizeEvent(QResizeEvent *event)
{
    if (width() > drawingPixmap.width() || height() > drawingPixmap.height())
    {
        int newWidth = qMax(width(), drawingPixmap.width());
        int newHeight = qMax(height(), drawingPixmap.height());
        resizeImage(&drawingPixmap, QSize(newWidth, newHeight));
        update();
    }
    else if (width() < drawingPixmap.width() || height() < drawingPixmap.height())
    {
        int newWidth = qMin(width(), drawingPixmap.width());
        int newHeight = qMin(height(), drawingPixmap.height());
        resizeImage(&drawingPixmap, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


//resize image - create new pixmap with new dimensions
//----------------------------------------------------------------------------------


void Canvas::resizeImage(QPixmap *image, QSize newSize)
{
    if (image->size() == newSize)
        return;

    QPixmap newImage(newSize);
    newImage.fill(Qt::white);

    QPainter painter(&newImage);
    painter.drawPixmap(QPoint(0, 0), *image);

    *image = newImage;
}


//clear image - fill white color
//----------------------------------------------------------------------------------


void Canvas::clearImage()
{
    drawingPixmap.fill(Qt::white);
    update();
}
