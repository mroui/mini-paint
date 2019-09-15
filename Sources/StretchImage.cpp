#include "Headers/StretchImage.h"
#include "ui_StretchImage.h"


stretchimg::stretchimg(QWidget *parent) : QDialog(parent), ui(new Ui::stretchimg)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    set_textedit_height(100);
    set_textedit_width(100);        //100% by default
}


stretchimg::~stretchimg()
{
    delete ui;
}


//set/get methods
//---------------------------------------------------------------------------------


void stretchimg::set_textedit_height(int nmb)
{
    QString nmb_str = QString::number(nmb);
    ui->te_wysokosc->setText(nmb_str);
}


int stretchimg::get_textedit_height()
{
    QString nmb_str =  ui->te_wysokosc->toPlainText();
    int nmb = nmb_str.toInt();
    return nmb;
}


void stretchimg::set_textedit_width(int nmb)
{
    QString nmb_str = QString::number(nmb);
    ui->te_szerokosc->setText(nmb_str);
}


int stretchimg::get_textedit_width()
{
    QString nmb_str =  ui->te_szerokosc->toPlainText();
    int nmb = nmb_str.toInt();
    return nmb;
}
