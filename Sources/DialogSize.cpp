#include "Headers/DialogSize.h"
#include "ui_DialogSize.h"


DialogSize::DialogSize(QWidget *parent) : QDialog(parent), ui(new Ui::DialogSize)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
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
    ui->te_height->setText(nmb_str);
}


int DialogSize::get_textedit_height()
{
    QString nmb_str =  ui->te_height->toPlainText();
    int nmb = nmb_str.toInt();
    return nmb;
}


void DialogSize::set_textedit_width(int nmb)
{
    QString nmb_str = QString::number(nmb);
    ui->te_width->setText(nmb_str);
}


int DialogSize::get_textedit_width()
{
    QString nmb_str =  ui->te_width->toPlainText();
    int nmb = nmb_str.toInt();
    return nmb;
}


void DialogSize::set_labels(QString str)
{
    ui->label1->setText(str);
    ui->label2->setText(str);
}
