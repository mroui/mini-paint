#ifndef RESIZEIMG_H
#define RESIZEIMG_H

#include <QDialog>
#include <QTextEdit>

namespace Ui { class resizeimg; }

class resizeimg : public QDialog
{
    Q_OBJECT

public:
    explicit resizeimg(QWidget *parent = nullptr);
    ~resizeimg();

    void set_textedit_height(int);
    void set_textedit_width(int);                   //ustawia/pobiera w/z polach textedit wysokosc i szerokosc
    int get_textedit_height();
    int get_textedit_width();

private:
    Ui::resizeimg *ui;
};

#endif // RESIZEIMG_H
