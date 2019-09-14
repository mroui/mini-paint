#include "Headers/MainWindow.h"
#include "ui_MainWindow.h"


//set default settings & initiate objects
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


//public methods
//---------------------------------------------------------------------------------


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


void MainWindow::ifFillThenColor(QColor color)
{
    if(!ui->ButtonWypelnienie->isChecked())
        canvas->setColor(color);
    else canvas->setBrushColor(color);
}


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


//close window event
//-----------------------------------------------------------------------------------


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


//palette colors click events
//---------------------------------------------------------------------------------


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


//click/valuechange events on toolbar
//-----------------------------------------------------------------------------------


void MainWindow::on_SpinBoxGruboscLinii_valueChanged(int width)
{
    canvas->setWidth(width);
}


void MainWindow::on_ButtonGumka_clicked()
{
    on_ButtonOlowek_clicked();
    canvas->setColor(Qt::white);
}


void MainWindow::on_ButtonOlowek_clicked()
{
    setShapes("Pencil");
    canvas->setFloodFill(false);
    ui->ButtonWypelnienie->setChecked(false);
}


void MainWindow::on_ButtonLinia_clicked()
{
    setShapes("Line");
    canvas->setFloodFill(false);
    ui->ButtonWypelnienie->setChecked(false);
}


void MainWindow::on_ButtonKwadrat_clicked()
{
    setShapes("Square");
}


void MainWindow::on_ButtonKolo_clicked()
{
    setShapes("Circle");
}


void MainWindow::on_ButtonTrojkat_clicked()
{
    setShapes("Triangle");
}


void MainWindow::on_ButtonWypelnienie_clicked()
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


//menubar/file events
//----------------------------------------------------------------------------------


void MainWindow::on_action_Nowy_triggered()
{
    on_actionWyczy_obraz_triggered();
}


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


void MainWindow::on_actionZapisz_jako_triggered()
{
    canvas->saveImage();
}


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


//menubar/image events
//----------------------------------------------------------------------------------


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


void MainWindow::on_actionOdwr_kolory_triggered()
{
    canvas->invertColors();
}


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


void MainWindow::on_actionZmie_rozmiar_triggered()
{
    resizeimg resizeimg;
    resizeimg.setModal(false);

    resizeimg.set_textedit_width(canvas->getImage().width());
    resizeimg.set_textedit_height(canvas->getImage().height());

    if(resizeimg.exec() == QDialog::Accepted)
    {
        int w = resizeimg.get_textedit_width();
        int h = resizeimg.get_textedit_height();
        ui->widget->resize(w+22,h+22);
        canvas->resize(w,h);
        update();
    }
}


void MainWindow::on_actionRozci_gnij_triggered()
{
    stretchimg stretchimg;
    stretchimg.setModal(false);

    if(stretchimg.exec() == QDialog::Accepted)
    {
        int w = stretchimg.get_textedit_width()*canvas->getImage().width()/100;
        int h = stretchimg.get_textedit_height()*canvas->getImage().height()/100;

        QPixmap stretchedimg = canvas->getImage();

        canvas->clear();
        canvas->resize(w,h);
        ui->widget->resize(w+22,h+22);

        canvas->setImage(stretchedimg.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

        update();
    }
}


void MainWindow::on_actionWytnij_triggered()
{
    canvas->cutImage();
    ui->actionWytnij->setEnabled(false);
    ui->actionWklej->setEnabled(true);
}


void MainWindow::on_actionWklej_triggered()
{
    canvas->pasteImage();
    ui->actionWytnij->setEnabled(true);
    ui->actionWklej->setEnabled(false);
}


//menubar/colors events
//----------------------------------------------------------------------------------


void MainWindow::on_actionZmie_kolor_triggered()
{
    on_palette_2_clicked();
    ui->palette_2->setChecked(true);
}


//menubar/help events
//----------------------------------------------------------------------------------


void MainWindow::on_actionO_Oprogramie_triggered()
{
    QMessageBox::information(this, "MiniPaint", "Program: Mini Paint\nAutor: Martyna Rój \nWersja: 1.07", QMessageBox::Ok );
}
