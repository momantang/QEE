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
#include "../MatOperator.h"
#include "settingsdialog.h"

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
	void showCommand_signal(QString cmd);
private:
	void initUI();
	void initActions();
	void initAOI();
private :
	void showCommand(QString cmd);
	void showImage(cv::Mat& mat,QString name);
	void showImageInListView(cv::Mat& mat, QString name);
private:
	Camera* camera;
	QTimer* cameraTimer;
	cv::Mat currentMat;
	std::map<QString, cv::Mat> mat_map;
	QImage currentImage;

	BlurWidget* blurWidget = nullptr;
	QDockWidget* blurDockWidget=nullptr;


	QMenu* fileMenu;
	QToolBar* fileToolBar;
	QAction* openImageAction;
	QAction* openCameraAction;
	QAction* pauseCameraAction;
	QAction* closeCameraAction;
	

	QAction* settingAction;
	QAction* exitAction;
	
	QMenu* toolMenu;
	QAction* eqblurAction;


	
	QMenu* aoiMenu;
	QAction* readGrayAction;
	QAction* medianBlurAction;
	QAction* calculateLightAction;
	QAction* removeLight1Action;
	QAction* removeLight2Action;


	QStatusBar* mainStatusBar;
	QLabel* mainStatusLabel;
	QLabel* actionStatusLabel;

	QGraphicsScene* imageScene;
	QGraphicsView* imageView;


	QListView* image_listview;
	QStandardItemModel* item_model;
	QPlainTextEdit* textEdit;

	SettingsDialog settingsDialog;
	//Ui::CVMainWindow *ui;
};
