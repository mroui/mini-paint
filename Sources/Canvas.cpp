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





///////////////////////todo

//czyszczenie obrazka
void Canvas::clearImage()
{
    drawingPixmap.fill(Qt::white);
    update();
}



//zapis obrazka - otwiera FileDialog gdzie mozna wybraz z 3 formatow: JPEG, PNG, BMP
bool Canvas::saveImage()
{
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Zapisz jako..."), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp)" ));

    if (!imagePath.isEmpty())
    {
      if (drawingPixmap.save(imagePath))
        return true;
    }
    return false;
}



//otworzenie obrazka -  otwiera FileDialog gdzie mozna wybraz z 3 formatow: JPEG, PNG, BMP
bool Canvas::openImage()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Otwórz..."), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp)" ));

    if (!imagePath.isEmpty())
    {
      if (drawingPixmap.load(imagePath))
        return true;
    }
    return false;
}



//odwrocenie kolorow obrazka - tworzy nowy obraz z odwroconymi kolorami i zamienia z poprzednim
void Canvas::invertColors()
{
    QImage image = drawingPixmap.toImage();
    image.invertPixels(QImage::InvertRgba);
    setImage(QPixmap::fromImage(image));

    update();
}



//wycinanie obrazka - zapisuje obecny obraz w CuttedImage i czysci okno
void Canvas::cutImage()
{
    cutPixmap = drawingPixmap;
    clearImage();
}



//wklejenie obrazka - wkleja na obecny obraz ten wycięty zapisany w pamięci - w lewy górny róg
void Canvas::pasteImage()
{
    QPainter pasteontop(&drawingPixmap);
    QRect rect = cutPixmap.rect();
    pasteontop.drawPixmap(rect,cutPixmap,rect);

    update();
}


//------------------------------------------------------------------------eventy press/move/release/paint/resize



//event wcisnietej myszki - ustawia punkty dla linii P1 i P2 od pozycji kliknietej myszki
//+ dla olowka ustawia dodatkowo last point
//ustawia rysowanie i wcisniecie myszki na true
void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (shapePencil)
                lastPoint = event->pos();

        mousePressed = true;
        pointsLine.setP1(event->pos());
        pointsLine.setP2(event->pos());
        isDrawing = true;
    }
}



//event zmiany ruchu kursora myszki - sprawdza czy wcisniety lewy przycisk myszki i czy jest ustawione rysowanie
//wtedy sczytuje nowa pozycje kursora i wpisuje do punktu drugiego linii
void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && isDrawing)
        pointsLine.setP2(event->pos());

    update();
}



//event 'odcisniecia' myszki - sprawdza czy wcisniety lewy przycisk myszki i czy jest ustawione rysowanie
//ustawia rysowanie i wcisnieta myszke na false
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        isDrawing = false;
        mousePressed = false;
        update();
    }
}




//event rysowania
//rysuje poczatkowo czysty obraz i sprawdza czy zostala wcisnieta myszka
//jesli wcisnieto to sprawdzajac ktory jest ksztalt, bedzie on rysowany
//olowek rysowany jest bezposrednio na obrazku (co jeden ruch myszki o 1px to rysowana linia)
//natomiast reszta rysowana jest na oddzielnej pixmapie, co umozliwia najpeirw wybranie wielkosci danego ksztaltu (ruch myszka i wiekszy ksztalt)
//a w momencie puszczenia dopiero dany ksztalt sie zatwierdza
//dodatkowo ksztalty: kolko/kwadrat/trojkat moga byc wypelnione sprawdzajac zmienna floodfill
//narysowany ksztalt w momencie puszczenia przycisku myszki (wasPressed) jest zlaczany z obrazkiem (drawImage)
void Canvas::paintEvent(QPaintEvent *event)
{
    static bool wasPressed = false;
    QRect dirtyRect = event->rect();
    QPainter painter(this);

    painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect); //bierze wymiary okna przez event->rect() i rysuje poczatkowo czysty obraz(poczatkowe uruchomienie programu!)


        if(mousePressed)                                                                            //sprawdzajac czy jest wcisnieta myszka
        {
            wasPressed = true;                                                                      //ustawia odcisniecie na true
            painter.setPen(QPen(brushColor, brushWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));         //ustawia wlasciwosci pedzla


            if(shapePencil)                                                                        //jesli wybrany ksztalt olowka
            {
                QPainter paintimg(&drawingPixmap);                                                          //to rysowany jest bezposrednio na obrazku
                paintimg.setPen(QPen(brushColor, brushWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));    //ustawia jego wlasciwosci pedzla
                paintimg.drawLine(lastPoint, pointsLine.p2());                                      //i rysuje co kazdy ruch myszki o nowe punkty
                lastPoint = pointsLine.p2();                                                        //przypisujac ostatni pkt punktowi p2
            }

            else if(shapeLine)
            {
                painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect);                             //dla reszty ksztaltow rysowane bedzie na osobnych pixmapach
                painter.drawLine(pointsLine);                                                       //rysuje linie o 2 punktach z QLine pointsLine
            }

            else if(shapeSquare)
            {
                painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect);

                QRect rect;
                rect.setTopLeft(pointsLine.p1());                                                   //dla kwadratu bierze punkty lewy górny i dolny prawy
                rect.setBottomRight(pointsLine.p2());

                painter.drawRect(rect);                                                             //rysuje prostokat

                if (isFill)                                                                      //jesli wlaczone jest wypelnianie
                {
                    QBrush fillbrush(fillColor);
                    QPainterPath path;
                    path.addRoundedRect(rect,brushWidth, brushWidth);
                    painter.fillPath(path,fillbrush);                                               //to wypelnia prostokat kolorem wypelnienia
                }
            }

            else if(shapeTriangle)
            {
                painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect);

                QPoint *points = new QPoint[3];
                points[0] = QPoint(pointsLine.x1(),pointsLine.y2());
                points[1] = QPoint(((pointsLine.x1()+pointsLine.x2())/2),pointsLine.y1());          //dla trojkata potrzebne sa ze wzorow punkty
                points[2] = QPoint(pointsLine.x2(), pointsLine.y2());

                QPolygon polygon;
                polygon<<points[0]<<points[1]<<points[2];                                           //tworzony jest wielokat z tych 3 punktow

                painter.drawPolygon(polygon);                                                       //i rysowany jest na obrazku

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
                rect.setBottomRight(pointsLine.p2());                                               //dla kola bierze punkty lewy gorny i dolny prawy

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

        else if(wasPressed)                                                                          //rysowanie obrazka juz w oknie - "zlaczenie"
        {
            wasPressed = false;

            QPainter PixmapPainter(&drawingPixmap);
            PixmapPainter.setPen(QPen(brushColor, brushWidth, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));

            if(shapePencil)
            {
                painter.drawImage(dirtyRect,drawingPixmap.toImage(),dirtyRect);                               //to rysuje normalnie obraz
            }

            else if(shapeLine)
            {
                PixmapPainter.drawLine(pointsLine);                                                   //dla reszty ksztaltow najpierw rysuje na pixmapie
                painter.drawPixmap(0, 0, drawingPixmap);                                                      //a potem obrazek wypełnia pixmapą
            }                                                                                         //jest to by moc najpierw wybrac gdzie ksztalt ustawimy
                                                                                                      //a dopiero potem go narysowac

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



//event resize obrazka - jezeli nowa szerokosc i wysokosc sa wieksze to bierze maksymalne wymiary z okna a obrazka i wywoluje resize
//jesli sa mniejsze to bierze minimalna wartosc
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



//resize obrazka - jezeli zmieniaja sie wymiary to tworzy nowa pixmape o nowych wymiarach
//czysci go na bialo i na nim rysuje od punktu (0,0) stary obrazek i zastepuje je
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
