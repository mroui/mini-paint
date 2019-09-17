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

    void set_textedit_height(int);
    void set_textedit_width(int);
    void set_labels(QString);
    int get_textedit_height();
    int get_textedit_width();

private:
    Ui::DialogSize *ui;
};

#endif // DIALOGSIZE_H
