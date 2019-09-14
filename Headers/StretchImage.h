#ifndef STRETCHIMG_H
#define STRETCHIMG_H

#include <QDialog>

namespace Ui { class stretchimg; }

class stretchimg : public QDialog
{
    Q_OBJECT

public:
    explicit stretchimg(QWidget *parent = nullptr);
    ~stretchimg();

    void set_textedit_height(int);
    void set_textedit_width(int);                   //ustawia/pobiera w/z polach textedit wysokosc i szerokosc
    int get_textedit_height();
    int get_textedit_width();

private:
    Ui::stretchimg *ui;
};

#endif // STRETCHIMG_H
