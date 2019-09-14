#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QSizeGrip>
#include <QMessageBox>
#include <QScrollArea>

#include "Headers/Canvas.h"
#include "Headers/ResizeImage.h"
#include "Headers/StretchImage.h"

namespace Ui
{ class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setBrushColor();                       //set brush color by check selected color on palette
    void setFillColor(QColor);                  //set fill color or brush color
    void setShapes(QString);                    //set shape of pencil


protected:
    void closeEvent(QCloseEvent *) override;    //close event


private:
    Ui::MainWindow *ui;                         //object of main window
    Canvas * canvas;                            //drawing object
    QColor previousPaletteColor;                //previous checked color in palette
    QSizeGrip * sizeGrip;                       //grip to increase image
    int initMBsave();                           //message box dialog with save question


private slots:
    void on_White_clicked();                    //palette colors click events
    void on_Black_clicked();
    void on_Grey_clicked();
    void on_Red_clicked();
    void on_Yellow_clicked();
    void on_Blue_clicked();
    void on_Green_clicked();
    void on_Pink_clicked();
    void on_Purple_clicked();
    void on_Orange_clicked();
    void on_Palette_clicked();


private slots:
    void on_Rubber_clicked();                   //click/valuechange events on toolbar
    void on_Pencil_clicked();
    void on_Weight_valueChanged(int);
    void on_Line_clicked();
    void on_Square_clicked();
    void on_Circle_clicked();
    void on_Triangle_clicked();
    void on_Fill_clicked();

    void on_New_triggered();                    //menubar/file events
    void on_Open_triggered();
    void on_Save_As_triggered();
    void on_Exit_triggered();

    void on_Clear_Image_triggered();            //menubar/image events
    void on_Invert_Colors_triggered();
    void on_Rotate_triggered();
    void on_Change_Size_triggered();
    void on_Stretch_triggered();
    void on_Cut_triggered();
    void on_Paste_triggered();

    void on_Edit_Color_triggered();             //menubar/colors events

    void on_About_triggered();                  //menubar/help events
};

#endif // MAINWINDOW_H
