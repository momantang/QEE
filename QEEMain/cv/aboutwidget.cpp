#include "aboutwidget.h"
#include <qgridlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("关于");
    QGridLayout* layout = new QGridLayout;
    QLabel* title = new QLabel("                    关于     ", this);
    QLabel* content = new QLabel;
    content->setText("基于Qt6.2.3 &OpenCV4.5.4<br>版本：0.0.1<br>更新时间：2022年3月20日<br>作者email：momantang@163.com，欢迎交流<br>源代码：todo");
    QPushButton* closeBtn = new QPushButton("关闭");
    layout->addWidget(title);
    layout->addWidget(content);
    layout->addWidget(closeBtn);
    //layout->addWidget(new)
    this->setLayout(layout);
    connect(closeBtn, &QPushButton::clicked, this, [=]() {
        this->close();
        });
}

AboutWidget::~AboutWidget()
{
  
}
