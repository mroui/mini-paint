#ifndef DIALOGSIZE_H
#define DIALOGSIZE_H

#include <QDialog>

namespace Ui { class DialogSize; }

class DialogSize : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSize(QWidget *parent = nullptr);
    ~DialogSize();

    void set_textedit_height(int);              //set/get textedit field - height of image
    int get_textedit_height();
    void set_textedit_width(int);               //set/get textedit field - width of image
    int get_textedit_width();
    void set_labels(QString);                   //set labels of units (px/%)

private:
    Ui::DialogSize *ui;
};

#endif // DIALOGSIZE_H
