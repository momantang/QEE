#pragma once
#include <QMenu>
#include <QtWidgets>
#include <QToolBar>
#include <QAction>
#include <QMainWindow>
#include <QDebug>
#include <QtWidgets>
#include <opencv2/opencv.hpp>
#include <map>
#include "camera.h"
#include "BlurWidget.h"
//namespace Ui { class CVMainWindow; };

class CVMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	CVMainWindow(QWidget *parent = Q_NULLPTR);
	~CVMainWindow();
	cv::Mat& getCurrentMat() { return currentMat; }
signals:
	void updateCurrentMat(cv::Mat& mat,QString name);
private:
	void initUI();
	void initActions();
	void initAOI();
private :
	void showImage(cv::Mat& mat,QString name);
private:
	Camera* camera;
	QTimer* cameraTimer;
	cv::Mat currentMat;
	QImage currentImage;
	std::map<QString, cv::Mat> mat_map;

	BlurWidget* blurWidget = nullptr;
	QDockWidget* blurDockWidget=nullptr;


	QMenu* fileMenu;
	QAction* openImageAction;
	QAction* openCameraAction;
	QAction* pauseCameraAction;
	QAction* closeCameraAction;
	
	QAction* settingAction;
	QAction* exitAction;

	QMenu* toolMenu;
	QAction* eqblurAction;
	
	QMenu* aoiMenu;
	QAction* medianBlurAction;


	QStatusBar* mainStatusBar;
	QLabel* mainStatusLabel;
	QLabel* actionStatusLabel;

	QGraphicsScene* imageScene;
	QGraphicsView* imageView;

	QPlainTextEdit* textEdit;
	//Ui::CVMainWindow *ui;
};
