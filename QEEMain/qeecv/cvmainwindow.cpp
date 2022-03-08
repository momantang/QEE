#include "cvmainwindow.h"
//#include "ui_cvmainwindow.h"

CVMainWindow::CVMainWindow(QWidget *parent)
	: QMainWindow(parent)
{

	connect(this, &CVMainWindow::updateCurrentMat, this, &CVMainWindow::showImage);
	this->setWindowTitle("CV demo");
	this->resize(1024, 768);
	this->initUI();
	this->initActions();
	mat_map.clear();

	
	//ui = new Ui::CVMainWindow();
	//ui->setupUi(this);
	
}

CVMainWindow::~CVMainWindow()
{
	//delete ui;
}

void CVMainWindow::initUI()
{
	fileMenu = this->menuBar()->addMenu("&File");

	mainStatusBar = statusBar();
	mainStatusLabel = new QLabel(mainStatusBar);
	actionStatusLabel = new QLabel(mainStatusBar);
	mainStatusBar->addPermanentWidget(mainStatusLabel);
	mainStatusBar->addWidget(actionStatusLabel);
	mainStatusLabel->setText("Image Information will be here");
	actionStatusLabel->setText("any action....");

	blurDockWidget = new QDockWidget("Blur Dock Widget", this);
	blurDockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
	blurDockWidget->setAllowedAreas(Qt::TopDockWidgetArea|Qt::LeftDockWidgetArea);
	this->addDockWidget(Qt::TopDockWidgetArea, blurDockWidget);
	blurWidget = new BlurWidget(this);
	blurDockWidget->setWidget(blurWidget);
	blurDockWidget->setVisible(false);

	QHBoxLayout* conentLayout = new QHBoxLayout;

	imageScene = new QGraphicsScene(this);
	imageView = new QGraphicsView(imageScene);
	textEdit = new QPlainTextEdit(this);
	conentLayout->addWidget(imageView);
	conentLayout->addWidget(textEdit);
	QGridLayout* mainLayout = new QGridLayout;
	mainLayout->addLayout(conentLayout, 1, 0);
	mainLayout->addWidget(new QLabel("List view"),2,0);
	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(mainLayout);
}

void CVMainWindow::initActions()
{
	openImageAction = new QAction("&Open Image",this);
	openCameraAction = new QAction("&Open Camera", this);
	pauseCameraAction = new QAction("&pause Camera", this);
	closeCameraAction = new QAction("&Close Camer", this);
	exitAction = new QAction("&Exit", this);

	fileMenu->addAction(openImageAction);
	fileMenu->addAction(openCameraAction);
	fileMenu->addAction(pauseCameraAction);
	fileMenu->addAction(closeCameraAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
	connect(fileMenu, &QMenu::triggered, this, [this](QAction* act) {
		//打开图片
		if (act == openImageAction) {
			QFileDialog dlg;
			if (dlg.exec()) {
				QString path = dlg.getOpenFileName();
				cv::Mat img=cv::imread(path.toStdString());
				emit this->updateCurrentMat(img,path);
			}
		}
		//打开摄像头
		//暂停摄像头
		//关闭摄像头


		if (act == exitAction) {
			this->close();
		}
		});


	//Tool Menu;
	toolMenu = menuBar()->addMenu("&Tool");
	eqblurAction = new QAction("滤波");
	toolMenu->addAction(eqblurAction);
	connect(eqblurAction, &QAction::triggered, this, [=]() {
		blurDockWidget->setVisible(true);
		});


	//AOI Menu

	aoiMenu = menuBar()->addMenu("&AOI");
	medianBlurAction = new QAction("&Median Blur", this);
	aoiMenu->addAction(medianBlurAction);
}

void CVMainWindow::showImage(cv::Mat& mat,QString name)
{
	qDebug() << "showImage name:" << name << " mat: " << mat.size().area();
}
