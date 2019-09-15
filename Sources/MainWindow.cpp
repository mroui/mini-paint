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

    on_Black_clicked();
    canvas->setWidth(1);

    ui->Cut->setEnabled(true);
    ui->Paste->setEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}


//public methods
//---------------------------------------------------------------------------------


void MainWindow::setBrushColor()
{
    QColor color;
    if (ui->White->isChecked())
        color = ui->White->palette().color(QPalette::Button);
    else if (ui->Black->isChecked())
        color = ui->Black->palette().color(QPalette::Button);
    else if (ui->Grey->isChecked())
        color = ui->Grey->palette().color(QPalette::Button);
    else if (ui->Red->isChecked())
        color = ui->Red->palette().color(QPalette::Button);
    else if (ui->Yellow->isChecked())
        color = ui->Yellow->palette().color(QPalette::Button);
    else if (ui->Blue->isChecked())
        color = ui->Blue->palette().color(QPalette::Button);
    else if (ui->Green->isChecked())
        color = ui->Green->palette().color(QPalette::Button);
    else if (ui->Pink->isChecked())
        color = ui->Pink->palette().color(QPalette::Button);
    else if (ui->Purple->isChecked())
        color = ui->Purple->palette().color(QPalette::Button);
    else if (ui->Orange->isChecked())
        color = ui->Orange->palette().color(QPalette::Button);
    else if (ui->Palette->isChecked())
        color = previousPaletteColor;

    canvas->setColor(color);
}


void MainWindow::setFillColor(QColor color)
{
    if(!ui->Fill->isChecked())
        canvas->setColor(color);
    else canvas->setBrushColor(color);
}


void MainWindow::setShapes(QString string)
{
    setBrushColor();

    canvas->setShapePen(false);
    canvas->setShapeLine(false);
    canvas->setShapeSquare(false);
    canvas->setShapeCircle(false);
    canvas->setShapeTriangle(false);

    if (string == "Pencil")
        canvas->setShapePen(true);
    else if (string == "Line")
        canvas->setShapeLine(true);
    else if (string == "Square")
        canvas->setShapeSquare(true);
    else if (string == "Circle")
        canvas->setShapeCircle(true);
    else if (string == "Triangle")
        canvas->setShapeTriangle(true);
}


//close window event
//-----------------------------------------------------------------------------------


void MainWindow::closeEvent(QCloseEvent * event)
{
    event->ignore();
    QMessageBox MBsave(QMessageBox::Question, tr("MiniPaint"), tr("Are you sure you want to exit without saving?"), QMessageBox::Yes | QMessageBox::No, this);
    MBsave.setButtonText(QMessageBox::Yes, tr("Yes"));
    MBsave.setButtonText(QMessageBox::No, tr("No"));
    MBsave.setDefaultButton(QMessageBox::No);

    if (MBsave.exec() == QMessageBox::Yes)
        event->accept();
}


//palette colors click events
//---------------------------------------------------------------------------------


void MainWindow::on_White_clicked()
{
    QColor color = ui->White->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Black_clicked()
{
    QColor color = ui->Black->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Grey_clicked()
{
    QColor color = ui->Grey->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Red_clicked()
{
    QColor color = ui->Red->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Yellow_clicked()
{
    QColor color = ui->Yellow->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Blue_clicked()
{
    QColor color = ui->Blue->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Green_clicked()
{
    QColor color = ui->Green->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Pink_clicked()
{
    QColor color = ui->Pink->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Purple_clicked()
{
    QColor color = ui->Purple->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Orange_clicked()
{
    QColor color = ui->Orange->palette().color(QPalette::Button);
    setFillColor(color);
}

void MainWindow::on_Palette_clicked()
{
    QColor color = QColorDialog::getColor();
    previousPaletteColor = color;
    setFillColor(color);
}


//click/valuechange events on toolbar
//-----------------------------------------------------------------------------------


void MainWindow::on_Weight_valueChanged(int width)
{
    canvas->setWidth(width);
}


void MainWindow::on_Rubber_clicked()
{
    on_Pencil_clicked();  //same settings like pencil
    canvas->setColor(Qt::white);
}


void MainWindow::on_Pencil_clicked()
{
    setShapes("Pencil");
    canvas->setFloodFill(false);
    ui->Fill->setChecked(false);
}


void MainWindow::on_Line_clicked()
{
    setShapes("Line");
    canvas->setFloodFill(false);
    ui->Fill->setChecked(false);
}


void MainWindow::on_Square_clicked()
{
    setShapes("Square");
}


void MainWindow::on_Circle_clicked()
{
    setShapes("Circle");
}


void MainWindow::on_Triangle_clicked()
{
    setShapes("Triangle");
}


void MainWindow::on_Fill_clicked()
{
    if (ui->Pencil->isChecked() || ui->Rubber->isChecked() || ui->Line->isChecked())
        ui->Fill->setChecked(false);

    if (!canvas->getFloodFill())
    {
        canvas->setFloodFill(true);

        QColor brushcolor;
        if (ui->White->isChecked())
            brushcolor = ui->White->palette().color(QPalette::Button);
        else if (ui->Black->isChecked())
            brushcolor = ui->Black->palette().color(QPalette::Button);
        else if (ui->Grey->isChecked())
            brushcolor = ui->Grey->palette().color(QPalette::Button);
        else if (ui->Red->isChecked())
            brushcolor = ui->Red->palette().color(QPalette::Button);
        else if (ui->Yellow->isChecked())
            brushcolor = ui->Yellow->palette().color(QPalette::Button);
        else if (ui->Blue->isChecked())
            brushcolor = ui->Blue->palette().color(QPalette::Button);
        else if (ui->Green->isChecked())
            brushcolor = ui->Green->palette().color(QPalette::Button);
        else if (ui->Pink->isChecked())
            brushcolor = ui->Pink->palette().color(QPalette::Button);
        else if (ui->Purple->isChecked())
            brushcolor = ui->Purple->palette().color(QPalette::Button);
        else if (ui->Orange->isChecked())
            brushcolor = ui->Orange->palette().color(QPalette::Button);
        else if (ui->Palette->isChecked())
            brushcolor = previousPaletteColor;

        canvas->setBrushColor(brushcolor);
    }
    else
    {
        canvas->setFloodFill(false);

        QColor color = canvas->getColor();
        if (color == ui->White->palette().color(QPalette::Button))
            ui->White->setChecked(true);
        else if (color == ui->Black->palette().color(QPalette::Button))
            ui->Black->setChecked(true);
        else if (color == ui->Grey->palette().color(QPalette::Button))
            ui->Grey->setChecked(true);
        else if (color == ui->Red->palette().color(QPalette::Button))
            ui->Red->setChecked(true);
        else if (color == ui->Yellow->palette().color(QPalette::Button))
            ui->Yellow->setChecked(true);
        else if (color == ui->Blue->palette().color(QPalette::Button))
            ui->Blue->setChecked(true);
        else if (color == ui->Green->palette().color(QPalette::Button))
            ui->Green->setChecked(true);
        else if (color == ui->Pink->palette().color(QPalette::Button))
            ui->Pink->setChecked(true);
        else if (color == ui->Purple->palette().color(QPalette::Button))
            ui->Purple->setChecked(true);
        else if (color == ui->Orange->palette().color(QPalette::Button))
            ui->Orange->setChecked(true);
        else
            ui->Palette->setChecked(true);
    }
}


//menubar/file events
//----------------------------------------------------------------------------------


void MainWindow::on_New_triggered()
{
    on_Clear_Image_triggered();
}


void MainWindow::on_Open_triggered()
{
    int choice = initMBsave();
    if (choice == QMessageBox::Yes || choice == QMessageBox::No)
    {
        if (choice == QMessageBox::Yes)
            canvas->saveImage();
        canvas->openImage();
        ui->widget->resize(canvas->getImage().width()+22,canvas->getImage().height()+22);
        canvas->resize(canvas->getImage().width(),canvas->getImage().height());
    }
}


void MainWindow::on_Save_As_triggered()
{
    canvas->saveImage();
}


void MainWindow::on_Exit_triggered()
{
    switch(initMBsave())
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


//init save image message box
//---------------------------------------------------------------------------------


int MainWindow::initMBsave()
{
    QMessageBox MBsave(QMessageBox::Question, tr("MiniPaint"), tr("Do you want to save changes?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);
    MBsave.setButtonText(QMessageBox::Yes, tr("Yes"));
    MBsave.setButtonText(QMessageBox::No, tr("No"));
    MBsave.setButtonText(QMessageBox::Cancel, tr("Cancel"));
    MBsave.setDefaultButton(QMessageBox::Yes);
    return MBsave.exec();
}


//menubar/image events
//----------------------------------------------------------------------------------


void MainWindow::on_Clear_Image_triggered()
{
    switch(initMBsave())
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


void MainWindow::on_Invert_Colors_triggered()
{
    canvas->invertColors();
}


void MainWindow::on_Rotate_triggered()
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


void MainWindow::on_Change_Size_triggered()
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


void MainWindow::on_Stretch_triggered()
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


void MainWindow::on_Cut_triggered()
{
    canvas->cutImage();
    ui->Cut->setEnabled(false);
    ui->Paste->setEnabled(true);
}


void MainWindow::on_Paste_triggered()
{
    canvas->pasteImage();
    ui->Cut->setEnabled(true);
    ui->Paste->setEnabled(false);
}


//menubar/colors events
//----------------------------------------------------------------------------------


void MainWindow::on_Edit_Color_triggered()
{
    on_Palette_clicked();
    ui->Palette->setChecked(true);
}


//menubar/help events
//----------------------------------------------------------------------------------


void MainWindow::on_About_triggered()
{
    QMessageBox::information(this, "MiniPaint", "Program: MiniPaint\nAuthor: Martyna Roj \nVersion: 1.07", QMessageBox::Ok );
}
