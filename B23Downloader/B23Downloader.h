#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_B23Downloader.h"

class B23Downloader : public QMainWindow
{
    Q_OBJECT

public:
    B23Downloader(QWidget *parent = Q_NULLPTR);

private:
    Ui::B23DownloaderClass ui;
};
