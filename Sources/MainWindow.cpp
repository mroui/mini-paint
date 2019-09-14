#include "Headers/MainWindow.h"
#include "ui_MainWindow.h"



//stworzenie obiektu obrazu, dodanie scrolla i samego obrazu na widgecie, dodanie suwaka do widgetu
//defaultowo klikniety czarny kolor pedzla (on_czarny_clicked()) i ustalona szerokosc pedzla 1
//dodatkowo wygaszona opcja wklejenia obrazu a wlaczona opcja wyciecia
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    canvas = new Canvas;
    canvas->setAttribute(Qt::WA_DeleteOnClose);

    QScrollArea * scrollArea = new QScrollArea;
    scrollArea->setWidget(ui->widget);
    setCentralWidget(scrollArea);
    ui->gridLayout->addWidget(canvas);

    ui->widget->setWindowFlags(Qt::SubWindow);

    sizeGrip = new QSizeGrip(canvas);
    ui->gridLayout->addWidget(sizeGrip, 0,0,1,1,Qt::AlignBottom | Qt::AlignRight);

    on_Czarny_clicked();
    canvas->setWidth(1);

    ui->actionWytnij->setEnabled(true);
    ui->actionWklej->setEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------funkcje publiczne: setColorBiggerFunction() i ifFillThenColor()

//sprawdza po kazdym przycisku koloru czy jest wcisniety - ten zostaje ustawiony jako kolor pedzla
void MainWindow::setColorBiggerFunction()
{
    QColor color;
    if (ui->Bialy->isChecked())
        color = ui->Bialy->palette().color(QPalette::Button);
    else if (ui->Czarny->isChecked())
        color = ui->Czarny->palette().color(QPalette::Button);
    else if (ui->Szary->isChecked())
        color = ui->Szary->palette().color(QPalette::Button);
    else if (ui->Czerwony->isChecked())
        color = ui->Czerwony->palette().color(QPalette::Button);
    else if (ui->Zolty->isChecked())
        color = ui->Zolty->palette().color(QPalette::Button);
    else if (ui->Niebieski->isChecked())
        color = ui->Niebieski->palette().color(QPalette::Button);
    else if (ui->Zielony->isChecked())
        color = ui->Zielony->palette().color(QPalette::Button);
    else if (ui->Rozowy->isChecked())
        color = ui->Rozowy->palette().color(QPalette::Button);
    else if (ui->Fioletowy->isChecked())
        color = ui->Fioletowy->palette().color(QPalette::Button);
    else if (ui->Pomaranczowy->isChecked())
        color = ui->Pomaranczowy->palette().color(QPalette::Button);
    else if (ui->palette_2->isChecked())
        color = previouspalettecolor;

    canvas->setColor(color);
}


//sprawdza czy wcisniety przycisk wypelniania - jesli tak to ustawia kolor wypelnienia, jak nie - pedzla
void MainWindow::ifFillThenColor(QColor color)
{
    if(!ui->ButtonWypelnienie->isChecked())
        canvas->setColor(color);
    else canvas->setBrushColor(color);
}


//ustawia kolor w zaleznosci od kliknietego koloru (setColorBiggerFunction)
//ustawia ksztalty na false poza tym w argumencie
void MainWindow::setShapes(QString string)
{
    setColorBiggerFunction();

    canvas->setShapePen(false);
    canvas->setShapeLine(false);
    canvas->setShapeSquare(false);
    canvas->setShapeCircle(false);
    canvas->setShapeTriangle(false);

    if (string == "Pencil")
        canvas->setShapePen(true);
    if (string == "Line")
        canvas->setShapeLine(true);
    if (string == "Square")
        canvas->setShapeSquare(true);
    if (string == "Circle")
        canvas->setShapeCircle(true);
    if (string == "Triangle")
        canvas->setShapeTriangle(true);
}
//---------------------------------------------------------------------------------click kolory

void MainWindow::on_Bialy_clicked()
{
    QColor color = ui->Bialy->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_Czarny_clicked()
{
    QColor color = ui->Czarny->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_Szary_clicked()
{
    QColor color = ui->Szary->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_Czerwony_clicked()
{
    QColor color = ui->Czerwony->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_Zolty_clicked()
{
    QColor color = ui->Zolty->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_Niebieski_clicked()
{
    QColor color = ui->Niebieski->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_Zielony_clicked()
{
    QColor color = ui->Zielony->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_Rozowy_clicked()
{
    QColor color = ui->Rozowy->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_Fioletowy_clicked()
{
    QColor color = ui->Fioletowy->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_Pomaranczowy_clicked()
{
    QColor color = ui->Pomaranczowy->palette().color(QPalette::Button);

    ifFillThenColor(color);
}

void MainWindow::on_palette_2_clicked()
{
    QColor color = QColorDialog::getColor();
    previouspalettecolor = color;

    ifFillThenColor(color);
}



//-----------------------------------------------------------------------------------zamkniecie okna event


//przed zamknieciem okna wyrzuca messageboxa czy napewno chce wyjsc bez zapisywania - jesli tak to zamyka, jak nie to nic
void MainWindow::closeEvent(QCloseEvent * event)
{
    event->ignore();
    QMessageBox MBzapis(QMessageBox::Question, tr("MiniPaint"), tr("Czy chcesz wyjść bez zapisywania?"), QMessageBox::Yes | QMessageBox::No, this);

    MBzapis.setButtonText(QMessageBox::Yes, tr("Tak"));
    MBzapis.setButtonText(QMessageBox::No, tr("Nie"));

    MBzapis.setDefaultButton(QMessageBox::No);

    int buttonclicked = MBzapis.exec();

    switch(buttonclicked)
    {
        case QMessageBox::Yes:
            event->accept();
            break;
        case QMessageBox::No:
            break;
    }
}


//-----------------------------------------------------------------------------------click toolsy


//ustawia grubosc pedzla
void MainWindow::on_SpinBoxGruboscLinii_valueChanged(int width)                                            //GRUBOSC PEDZLA
{
    canvas->setWidth(width);
}


//dziala jak olowek (mazanie) - wiec wywolywane jest klikniecie olowka + zmienia kolor na bialy
void MainWindow::on_ButtonGumka_clicked()                                                                  //GUMKA
{
    on_ButtonOlowek_clicked();
    canvas->setColor(Qt::white);
}


//ustawia kolor+ksztalt olowka i wylacza wypelninie (nie wypelnia sie olowka)
void MainWindow::on_ButtonOlowek_clicked()                                                                 //OLOWEK
{
    setShapes("Pencil");

    canvas->setFloodFill(false);
    ui->ButtonWypelnienie->setChecked(false);
}


//ustawia kolor+ksztalt linii i wylacza wypelninie (nie wypelnia sie linii)
void MainWindow::on_ButtonLinia_clicked()                                                                  //LINIA
{
    setShapes("Line");

    canvas->setFloodFill(false);
    ui->ButtonWypelnienie->setChecked(false);
}


//ustawia kolor+ksztalt kwadratu
void MainWindow::on_ButtonKwadrat_clicked()                                                                //KWADRAT
{
    setShapes("Square");
}


//ustawia kolor+ksztalt kola
void MainWindow::on_ButtonKolo_clicked()                                                                   //KOLO
{
    setShapes("Circle");
}


//ustawia kolor+ksztalt trojkata
void MainWindow::on_ButtonTrojkat_clicked()                                                                //TROJKAT
{
    setShapes("Triangle");
}


//wypelnienie - sczytuje czy zaznaczone sa ksztalty olowka/gumki/linii - wtedy nie ma wypelniania
//wiec ustawia na false,
//sprawdza czy jest wylaczone wypelnianie - wtedy ustawia na true i ustawia kolor wypelnienia
//jesli wlaczone - to je wylacza i ustawia poprzedni (przed kliknieciem wypelnienia) kolor pedzla
void MainWindow::on_ButtonWypelnienie_clicked()                                                            //WYPELNIENIE
{
    if (ui->ButtonOlowek->isChecked() || ui->ButtonGumka->isChecked() || ui->ButtonLinia->isChecked())
        ui->ButtonWypelnienie->setChecked(false);

    if (!canvas->getFloodFill())
    {
        canvas->setFloodFill(true);

        QColor brushcolor;
        if (ui->Bialy->isChecked())
            brushcolor = ui->Bialy->palette().color(QPalette::Button);
        else if (ui->Czarny->isChecked())
            brushcolor = ui->Czarny->palette().color(QPalette::Button);
        else if (ui->Szary->isChecked())
            brushcolor = ui->Szary->palette().color(QPalette::Button);
        else if (ui->Czerwony->isChecked())
            brushcolor = ui->Czerwony->palette().color(QPalette::Button);
        else if (ui->Zolty->isChecked())
            brushcolor = ui->Zolty->palette().color(QPalette::Button);
        else if (ui->Niebieski->isChecked())
            brushcolor = ui->Niebieski->palette().color(QPalette::Button);
        else if (ui->Zielony->isChecked())
            brushcolor = ui->Zielony->palette().color(QPalette::Button);
        else if (ui->Rozowy->isChecked())
            brushcolor = ui->Rozowy->palette().color(QPalette::Button);
        else if (ui->Fioletowy->isChecked())
            brushcolor = ui->Fioletowy->palette().color(QPalette::Button);
        else if (ui->Pomaranczowy->isChecked())
            brushcolor = ui->Pomaranczowy->palette().color(QPalette::Button);
        else if (ui->palette_2->isChecked())
            brushcolor = previouspalettecolor;

        canvas->setBrushColor(brushcolor);
    }

    else
    {
        canvas->setFloodFill(false);

        QColor color = canvas->getColor();
        if (color == ui->Bialy->palette().color(QPalette::Button))
            ui->Bialy->setChecked(true);
        else if (color == ui->Czarny->palette().color(QPalette::Button))
            ui->Czarny->setChecked(true);
        else if (color == ui->Szary->palette().color(QPalette::Button))
            ui->Szary->setChecked(true);
        else if (color == ui->Czerwony->palette().color(QPalette::Button))
            ui->Czerwony->setChecked(true);
        else if (color == ui->Zolty->palette().color(QPalette::Button))
            ui->Zolty->setChecked(true);
        else if (color == ui->Niebieski->palette().color(QPalette::Button))
            ui->Niebieski->setChecked(true);
        else if (color == ui->Zielony->palette().color(QPalette::Button))
            ui->Zielony->setChecked(true);
        else if (color == ui->Rozowy->palette().color(QPalette::Button))
            ui->Rozowy->setChecked(true);
        else if (color == ui->Fioletowy->palette().color(QPalette::Button))
            ui->Fioletowy->setChecked(true);
        else if (color == ui->Pomaranczowy->palette().color(QPalette::Button))
            ui->Pomaranczowy->setChecked(true);
        else
            ui->palette_2->setChecked(true);
    }
}



//----------------------------------------------------------------------------------click menubar


//wyczyszczenie obrazu - messagebox czy zapisac obraz potem czysci obraz
void MainWindow::on_actionWyczy_obraz_triggered()
{
    QMessageBox MBzapis(QMessageBox::Question, tr("MiniPaint"), tr("Czy chcesz zapisać obraz?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);

    MBzapis.setButtonText(QMessageBox::Yes, tr("Tak"));
    MBzapis.setButtonText(QMessageBox::No, tr("Nie"));
    MBzapis.setButtonText(QMessageBox::Cancel, tr("Anuluj"));

    MBzapis.setDefaultButton(QMessageBox::Yes);

    int buttonclicked = MBzapis.exec();

    switch(buttonclicked)
    {
        case QMessageBox::Yes:
            if(canvas->saveImage())
                canvas->clear();
            break;
        case QMessageBox::No:
            canvas->clear();
            break;
    }
}



//zapis obrazu
void MainWindow::on_actionZapisz_jako_triggered()
{
    canvas->saveImage();
}



//wyjscie z programu - messagebox czy zapisac obraz potem zamyka aplikacje
void MainWindow::on_actionZako_cz_triggered()
{
    QMessageBox MBzapis(QMessageBox::Question, tr("MiniPaint"), tr("Czy chcesz zapisać obraz?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);

    MBzapis.setButtonText(QMessageBox::Yes, tr("Tak"));
    MBzapis.setButtonText(QMessageBox::No, tr("Nie"));
    MBzapis.setButtonText(QMessageBox::Cancel, tr("Anuluj"));

    MBzapis.setDefaultButton(QMessageBox::Yes);

    int buttonclicked = MBzapis.exec();

    switch(buttonclicked)
    {
        case QMessageBox::Yes:
            if (canvas->saveImage())
                QApplication::quit();
            break;
        case QMessageBox::No:
            QApplication::quit();
            break;
    }
}



//nowy obraz - to samo co wyczyszczenie
void MainWindow::on_action_Nowy_triggered()
{
    on_actionWyczy_obraz_triggered();
}



//o programie - messagebox o programie
void MainWindow::on_actionO_Oprogramie_triggered()
{
    QMessageBox::information(this, "MiniPaint", "Program: Mini Paint\nAutor: Martyna Rój \nWersja: 1.07", QMessageBox::Ok );
}



//otworz obraz - messagebox czy zapisac obraz potem zapisz->otworz->resize widgetu i obrazka LUB otworz->resize widgetu i obrazka
void MainWindow::on_action_Otworz_triggered()
{
    QMessageBox MBzapis(QMessageBox::Question, tr("MiniPaint"), tr("Czy chcesz zapisać obraz?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);

    MBzapis.setButtonText(QMessageBox::Yes, tr("Tak"));
    MBzapis.setButtonText(QMessageBox::No, tr("Nie"));
    MBzapis.setButtonText(QMessageBox::Cancel, tr("Anuluj"));

    MBzapis.setDefaultButton(QMessageBox::Yes);

    int buttonclicked = MBzapis.exec();

    switch(buttonclicked)
    {
        case QMessageBox::Yes:
            canvas->saveImage();
            canvas->openImage();
            ui->widget->resize(canvas->getImage().width()+22,canvas->getImage().height()+22);
            canvas->resize(canvas->getImage().width(),canvas->getImage().height());
            break;
        case QMessageBox::No:
            canvas->openImage();
            ui->widget->resize(canvas->getImage().width()+22,canvas->getImage().height()+22);
            canvas->resize(canvas->getImage().width(),canvas->getImage().height());
            break;
    }
}



//zmien kolor - otwiera okno z paleta i zaznacza button balety na zaznaczony
void MainWindow::on_actionZmie_kolor_triggered()
{
    on_palette_2_clicked();
    ui->palette_2->setChecked(true);
}



//odwroc kolory
void MainWindow::on_actionOdwr_kolory_triggered()
{
    canvas->invertColors();
}



//odwrocenie obrazu - bierze centralny pkt obrazu i ustala macierz, ktora obraca o 90*
//czysci obrazek ze spodu i wstawia nowy obrocony + resize widgetu i okna
void MainWindow::on_actionOdwr_triggered()
{
    QPoint center = canvas->getImage().rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.rotate(90);
    QPixmap rotatedImg = canvas->getImage().transformed(matrix);

    int w = rotatedImg.width();
    int h = rotatedImg.height();
    ui->widget->resize(w+22, h+22);
    canvas->resize(w,h);
    canvas->clear();
    canvas->setImage(rotatedImg);
    update();
}



//zmien rozmiar - tworzy obiekt resizeimg ktory ma okno na wpisywanie nowych wartosci
//sczytuje je i resizeuje widget i obrazek
void MainWindow::on_actionZmie_rozmiar_triggered()
{
    resizeimg resizeimg;
    resizeimg.setModal(false);                                      //ustawia ze nie mozna otworzyc wiecej okien

    resizeimg.set_textedit_width(canvas->getImage().width());       //wstawia defaultowo wymiary obrazka
    resizeimg.set_textedit_height(canvas->getImage().height());

    if(resizeimg.exec() == QDialog::Accepted)                       //jak kliknie sie OK w dialogu resizeimg
    {
        int w = resizeimg.get_textedit_width();
        int h = resizeimg.get_textedit_height();
        ui->widget->resize(w+22,h+22);
        canvas->resize(w,h);
        update();
    }
}



//rozciagniecie obrazu - tworzy obiekt stretchimg ktory ma okno na wpisywanie procentu o ile rozszerzyc okno
//po szerokosci i wysokosci - sczytuje procent mnozy o rozmiar obrazka i /100 co daje nowe wymiary i resizuje
//widget i obrazek, ustawia nowy obrazek
void MainWindow::on_actionRozci_gnij_triggered()
{
    stretchimg stretchimg;
    stretchimg.setModal(false);                                                     //ustawia ze nie mozna otworzyc wiecej okien

    if(stretchimg.exec() == QDialog::Accepted)
    {
        int w = stretchimg.get_textedit_width()*canvas->getImage().width()/100;     //nowe wymiary obrazka
        int h = stretchimg.get_textedit_height()*canvas->getImage().height()/100;

        QPixmap stretchedimg = canvas->getImage();

        canvas->clear();
        canvas->resize(w,h);
        ui->widget->resize(w+22,h+22);

        canvas->setImage(stretchedimg.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

        update();
    }
}



//wytnij obraz - wycina + wygasza przycisk ponownego wycinania a wlacza do wklejenia
void MainWindow::on_actionWytnij_triggered()
{
    canvas->cutImage();
    ui->actionWytnij->setEnabled(false);
    ui->actionWklej->setEnabled(true);
}



//wklej obraz - wkleja wyciety poprzednio obraz i wygasza przycisk wklejania a wlacza wycinania
void MainWindow::on_actionWklej_triggered()
{
    canvas->pasteImage();
    ui->actionWytnij->setEnabled(true);
    ui->actionWklej->setEnabled(false);
}
