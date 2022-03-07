#ifndef B23MW_H
#define B23MW_H

#include <QMainWindow>

namespace Ui {
class B23MW;
}

class B23MW : public QMainWindow
{
    Q_OBJECT

public:
    explicit B23MW(QWidget *parent = nullptr);
    ~B23MW();

private:
    Ui::B23MW *ui;
};

#endif // B23MW_H
