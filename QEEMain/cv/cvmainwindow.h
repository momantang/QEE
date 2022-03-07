#ifndef CVMAINWINDOW_H
#define CVMAINWINDOW_H
#include <opencv2/opencv.hpp>
#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QToolBar>
#include <QListView>
#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../utils.h"


#include "aboutwidget.h"
enum MorphologyType{};
class CVMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CVMainWindow(QWidget *parent = nullptr);
    static CVMainWindow* inst();
    ~CVMainWindow();
private:
    void initUI();
    void createAction();
    void createToolBar();
    void showImage(QString path);
    void showDstMat(cv::Mat);
    void morphology(const cv::Mat& src, cv::Mat& dst, const QString action = "1");
signals:
    void updateStatus(QString status);
    void push_back(cv::Mat,QString name);


private slots:
    void openImage();
    void zoomIn();
    void zoomOut();
    void prevImage();
    void nextImage();
    void saveAs();
    void openCamera();
    void stopCamera();
    void releaseCamera();
    void captureImage();
    void updateToolBar(QString tips);
    void addMat(cv::Mat,QString name);
  
private:
    QMenu *fileMenu;
    QMenu* toolMenu;
    QMenu *editMenu;

    QMenu* aboutMenu;
    QMenu* settingMenu;


    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QToolBar* morphologyToolBar;
    //基本action
    QAction* openImageAction;
    QAction* saveDstAction;

    //toolaction
    QAction* splitAction;

    //形态学action
    QComboBox* kernelCombobox;
    QComboBox* kernelWidthCombobox;
    QComboBox* kernelHeightCombobox;
    QComboBox* morphologyCombobox;
    //QAction * 
    QAction* openCameraAction;
    QAction* openVideoAction;
    QAction* exitAction;

    QAction *zoomInAction;
    QAction *zoomOutAction;


    QAction* aboutAction;
    QAction* donateAction;



    //QAction* openImageAction;
    //QAction* openImageAction;
    //QAction *openImageAction;
    QGraphicsScene* imageSrcScene, *imageDstScene;
    QGraphicsView* imageSrcView;
    QGraphicsView* imageDstView;

    QListView* image_list;
    QStandardItemModel* list_model;

    QStatusBar* mainStatusBar;
    QLabel* mainStatusLabel;

    QLabel *statusLabel;
    cv::Mat currentMat;
    QList<cv::Mat> mats;

    AboutWidget* aboutWidget=nullptr;
};

#endif // CVMAINWINDOW_H
