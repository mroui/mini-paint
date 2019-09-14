#include "Headers/Canvas.h"


//ustawia obraz do wymiaru okna i wypelnia go na bialo
//wszystko na false, tylko ksztalt olowka na true
Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);

    Image = QPixmap(width(),height());
    Image.fill(Qt::white);

    drawing = false;
    mousePressed = false;
    floodfill = false;

    shape_pencil=true;
    shape_line = false;
    shape_square = false;
    shape_circle = false;
    shape_triangle = false;
}


//--------------------------------------------------------------------------------------------funkcje publiczne


//czyszczenie obrazka
void Canvas::clear()
{
    Image.fill(Qt::white);
    update();
}



//zapis obrazka - otwiera FileDialog gdzie mozna wybraz z 3 formatow: JPEG, PNG, BMP
bool Canvas::saveImage()
{
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Zapisz jako..."), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp)" ));

    if (!imagePath.isEmpty())
    {
      if (Image.save(imagePath))
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
      if (Image.load(imagePath))
        return true;
    }
    return false;
}



//odwrocenie kolorow obrazka - tworzy nowy obraz z odwroconymi kolorami i zamienia z poprzednim
void Canvas::invertColors()
{
    QImage image = Image.toImage();
    image.invertPixels(QImage::InvertRgba);
    setImage(QPixmap::fromImage(image));

    update();
}



//wycinanie obrazka - zapisuje obecny obraz w CuttedImage i czysci okno
void Canvas::cutImage()
{
    CuttedImage = Image;
    clear();
}



//wklejenie obrazka - wkleja na obecny obraz ten wycięty zapisany w pamięci - w lewy górny róg
void Canvas::pasteImage()
{
    QPainter pasteontop(&Image);
    QRect rect = CuttedImage.rect();
    pasteontop.drawPixmap(rect,CuttedImage,rect);

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
        if (shape_pencil)
                lastPoint = event->pos();

        mousePressed = true;
        pointsLine.setP1(event->pos());
        pointsLine.setP2(event->pos());
        drawing = true;
    }
}



//event zmiany ruchu kursora myszki - sprawdza czy wcisniety lewy przycisk myszki i czy jest ustawione rysowanie
//wtedy sczytuje nowa pozycje kursora i wpisuje do punktu drugiego linii
void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing)
        pointsLine.setP2(event->pos());

    update();
}



//event 'odcisniecia' myszki - sprawdza czy wcisniety lewy przycisk myszki i czy jest ustawione rysowanie
//ustawia rysowanie i wcisnieta myszke na false
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing)
    {
        drawing = false;
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

    painter.drawImage(dirtyRect,Image.toImage(),dirtyRect); //bierze wymiary okna przez event->rect() i rysuje poczatkowo czysty obraz(poczatkowe uruchomienie programu!)


        if(mousePressed)                                                                            //sprawdzajac czy jest wcisnieta myszka
        {
            wasPressed = true;                                                                      //ustawia odcisniecie na true
            painter.setPen(QPen(Color, Width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));         //ustawia wlasciwosci pedzla


            if(shape_pencil)                                                                        //jesli wybrany ksztalt olowka
            {
                QPainter paintimg(&Image);                                                          //to rysowany jest bezposrednio na obrazku
                paintimg.setPen(QPen(Color, Width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));    //ustawia jego wlasciwosci pedzla
                paintimg.drawLine(lastPoint, pointsLine.p2());                                      //i rysuje co kazdy ruch myszki o nowe punkty
                lastPoint = pointsLine.p2();                                                        //przypisujac ostatni pkt punktowi p2
            }

            else if(shape_line)
            {
                painter.drawImage(dirtyRect,Image.toImage(),dirtyRect);                             //dla reszty ksztaltow rysowane bedzie na osobnych pixmapach
                painter.drawLine(pointsLine);                                                       //rysuje linie o 2 punktach z QLine pointsLine
            }

            else if(shape_square)
            {
                painter.drawImage(dirtyRect,Image.toImage(),dirtyRect);

                QRect rect;
                rect.setTopLeft(pointsLine.p1());                                                   //dla kwadratu bierze punkty lewy górny i dolny prawy
                rect.setBottomRight(pointsLine.p2());

                painter.drawRect(rect);                                                             //rysuje prostokat

                if (floodfill)                                                                      //jesli wlaczone jest wypelnianie
                {
                    QBrush fillbrush(BrushColor);
                    QPainterPath path;
                    path.addRoundedRect(rect,Width, Width);
                    painter.fillPath(path,fillbrush);                                               //to wypelnia prostokat kolorem wypelnienia
                }
            }

            else if(shape_triangle)
            {
                painter.drawImage(dirtyRect,Image.toImage(),dirtyRect);

                QPoint *points = new QPoint[3];
                points[0] = QPoint(pointsLine.x1(),pointsLine.y2());
                points[1] = QPoint(((pointsLine.x1()+pointsLine.x2())/2),pointsLine.y1());          //dla trojkata potrzebne sa ze wzorow punkty
                points[2] = QPoint(pointsLine.x2(), pointsLine.y2());

                QPolygon polygon;
                polygon<<points[0]<<points[1]<<points[2];                                           //tworzony jest wielokat z tych 3 punktow

                painter.drawPolygon(polygon);                                                       //i rysowany jest na obrazku

                if (floodfill)
                {
                    QBrush fillbrush(BrushColor);
                    QPainterPath path;
                    path.addPolygon(polygon);
                    painter.fillPath(path,fillbrush);
                }
            }

            else if(shape_circle)
            {
                painter.drawImage(dirtyRect,Image.toImage(),dirtyRect);

                QRect rect;
                rect.setTopLeft(pointsLine.p1());
                rect.setBottomRight(pointsLine.p2());                                               //dla kola bierze punkty lewy gorny i dolny prawy

                painter.drawEllipse(rect);

                if (floodfill)
                {
                    QBrush fillbrush(BrushColor);
                    QPainterPath path;
                    path.addEllipse(rect);
                    painter.fillPath(path,fillbrush);
                }
            }
        }

        else if(wasPressed)                                                                          //rysowanie obrazka juz w oknie - "zlaczenie"
        {
            wasPressed = false;

            QPainter PixmapPainter(&Image);
            PixmapPainter.setPen(QPen(Color, Width, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));

            if(shape_pencil)
            {
                painter.drawImage(dirtyRect,Image.toImage(),dirtyRect);                               //to rysuje normalnie obraz
            }

            else if(shape_line)
            {
                PixmapPainter.drawLine(pointsLine);                                                   //dla reszty ksztaltow najpierw rysuje na pixmapie
                painter.drawPixmap(0, 0, Image);                                                      //a potem obrazek wypełnia pixmapą
            }                                                                                         //jest to by moc najpierw wybrac gdzie ksztalt ustawimy
                                                                                                      //a dopiero potem go narysowac

            else if(shape_square)
            {
                QRect rect;
                rect.setTopLeft(pointsLine.p1());
                rect.setBottomRight(pointsLine.p2());

                PixmapPainter.drawRect(rect);

                if (floodfill)
                {
                    QBrush fillbrush(BrushColor);
                    QPainterPath path;
                    path.addRoundedRect(rect,Width, Width);
                    PixmapPainter.fillPath(path,fillbrush);
                }

                painter.drawPixmap(0, 0, Image);
            }

            else if(shape_circle)
            {
                QRect rect;
                rect.setTopLeft(pointsLine.p1());
                rect.setBottomRight(pointsLine.p2());

                PixmapPainter.drawEllipse(rect);

                if (floodfill)
                {
                    QBrush fillbrush(BrushColor);
                    QPainterPath path;
                    path.addEllipse(rect);
                    PixmapPainter.fillPath(path,fillbrush);
                }

                painter.drawPixmap(0, 0, Image);
            }

            else if(shape_triangle)
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

                if (floodfill)
                {
                    QBrush fillbrush(BrushColor);
                    QPainterPath path;
                    path.addPolygon(polygon);
                    PixmapPainter.fillPath(path,fillbrush);
                }

                painter.drawPixmap(0, 0, Image);
            }
        }
}



//event resize obrazka - jezeli nowa szerokosc i wysokosc sa wieksze to bierze maksymalne wymiary z okna a obrazka i wywoluje resize
//jesli sa mniejsze to bierze minimalna wartosc
void Canvas::resizeEvent(QResizeEvent *event)
{
    if (width() > Image.width() || height() > Image.height())
    {
        int newWidth = qMax(width(), Image.width());
        int newHeight = qMax(height(), Image.height());

        resizeImage(&Image, QSize(newWidth, newHeight));
        update();
    }
    else if (width() < Image.width() || height() < Image.height())
    {
        int newWidth = qMin(width(), Image.width());
        int newHeight = qMin(height(), Image.height());

        resizeImage(&Image, QSize(newWidth, newHeight));
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
