#include "Headers/ResizeImage.h"
#include "ui_ResizeImage.h"

resizeimg::resizeimg(QWidget *parent) : QDialog(parent), ui(new Ui::resizeimg)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}



resizeimg::~resizeimg()
{
    delete ui;
}



void resizeimg::set_textedit_height(int nmb)
{
    QString nmb_str = QString::number(nmb);
    ui->te_wysokosc->setText(nmb_str);
}



int resizeimg::get_textedit_height()
{
    QString nmb_str =  ui->te_wysokosc->toPlainText();
    int nmb = nmb_str.toInt();
    return nmb;
}



void resizeimg::set_textedit_width(int nmb)
{
    QString nmb_str = QString::number(nmb);
    ui->te_szerokosc->setText(nmb_str);
}



int resizeimg::get_textedit_width()
{
    QString nmb_str =  ui->te_szerokosc->toPlainText();
    int nmb = nmb_str.toInt();
    return nmb;
}
