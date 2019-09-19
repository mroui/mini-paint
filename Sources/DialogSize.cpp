#include "Headers/DialogSize.h"
#include "ui_DialogSize.h"

#include <QIntValidator>


//set default settings & initiate objects
DialogSize::DialogSize(QWidget *parent) : QDialog(parent), ui(new Ui::DialogSize)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->text_width->setValidator( new QIntValidator(0, 9999, this) );
    ui->text_height->setValidator( new QIntValidator(0, 9999, this) );
}


DialogSize::~DialogSize()
{
    delete ui;
}


//set/get methods
//---------------------------------------------------------------------------------


void DialogSize::set_textedit_height(int nmb)
{
    QString nmb_str = QString::number(nmb);
    ui->text_height->setText(nmb_str);
}


int DialogSize::get_textedit_height()
{
    QString nmb_str =  ui->text_height->text();
    int nmb = nmb_str.toInt();
    return nmb;
}


void DialogSize::set_textedit_width(int nmb)
{
    QString nmb_str = QString::number(nmb);
    ui->text_width->setText(nmb_str);
}


int DialogSize::get_textedit_width()
{
    QString nmb_str =  ui->text_width->text();
    int nmb = nmb_str.toInt();
    return nmb;
}


void DialogSize::set_labels(QString str)
{
    ui->label1->setText(str);
    ui->label2->setText(str);
}
