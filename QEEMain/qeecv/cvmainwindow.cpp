#include "cvmainwindow.h"
#include "../Utils.h"
//#include "ui_cvmainwindow.h"

CVMainWindow::CVMainWindow(QWidget* parent)
	: QMainWindow(parent)
{

	connect(this, &CVMainWindow::updateCurrentMat, this, [this](cv::Mat& mat, QString name) {
		mat_map.emplace(name, mat);
		currentMat = mat;
		this->showImage(mat, name);
		this->showImageInListView(mat, name);
		});
	this->setWindowTitle("CV demo");
	this->resize(1024, 768);
	this->initUI();
	this->initActions();
	this->initAOI();

	connect(this, &CVMainWindow::showCommand_signal, this, &CVMainWindow::showCommand);
	//camera

	cameraTimer = new QTimer(this);
	connect(cameraTimer, &QTimer::timeout, this, [=]() {
		this->camera->takeMat(currentMat);

		emit updateCurrentMat(currentMat, "live");
		});
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
	blurDockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::LeftDockWidgetArea);
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
	image_listview = new QListView(this);
	image_listview->setViewMode(QListView::IconMode);
	image_listview->setResizeMode(QListView::Adjust);
	image_listview->setSpacing(1);
	image_listview->setWrapping(false);
	image_listview->setMinimumHeight(145);
	image_listview->setMaximumHeight(145);
	item_model = new QStandardItemModel(this);
	image_listview->setModel(item_model);
	connect(image_listview, &QListView::clicked, this, [=](const QModelIndex& index) {
		qDebug() << index.row();
		qDebug() << "mats size: " << mat_map.size();
		auto item = item_model->itemFromIndex(index);
		//showDstMat(mats.at(index.row()));
		qDebug() << item->text();
		currentMat = mat_map.at(item->text());
		this->showImage(currentMat, item->text());
		});


	mainLayout->addWidget(image_listview, 2, 0);
	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(mainLayout);
}

void CVMainWindow::initActions()
{
	openImageAction = new QAction("&Open Image", this);
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
			QFileDialog dlg(this);
			dlg.setDirectory("D:/images");
			dlg.setFileMode(QFileDialog::ExistingFile);
			dlg.setNameFilter("Image(*.jpg *.png *.bmp *.pgm)");
			if (dlg.exec()) {
				auto path = dlg.selectedFiles();
				cv::Mat img = cv::imread(path.at(0).toStdString());
				emit this->updateCurrentMat(img, path.at(0));
			}
		}
		//打开摄像头
		if (act == openCameraAction) {
			camera = CameraFactory::instance("build-in");
			camera->openCamera();
			cameraTimer->setInterval(100);
			cameraTimer->start();
		}
		//暂停摄像头
		if (act == pauseCameraAction) {
			cameraTimer->stop();
		}
		//关闭摄像头
		if (act == closeCameraAction) {
			cameraTimer->stop();
			camera->closeCamera();
		}


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


}

void CVMainWindow::initAOI()
{
	aoiMenu = menuBar()->addMenu("&AOI");
	medianBlurAction = new QAction("&Median Blur", this);
	aoiMenu->addAction(medianBlurAction);
	connect(aoiMenu, &QMenu::triggered, this, [this](QAction* act) {
		if (act == medianBlurAction) {
			emit showCommand_signal("消除噪声");
			cv::Mat img_noise;
			cv::medianBlur(currentMat, img_noise, 3);
			emit updateCurrentMat(img_noise, "img_noise");
		}
		});


}


void CVMainWindow::showCommand(QString cmd)
{
	this->textEdit->insertPlainText(cmd);
}

void CVMainWindow::showImage(cv::Mat& mat, QString name)
{
	qDebug() << "showImage name:" << name << " mat: " << mat.size().area();

	imageScene->clear();
	QImage qimage = QEE::Utils::Mat2QImage(mat, false);
	QPixmap image = QPixmap::fromImage(qimage);
	imageScene->addPixmap(image);
	imageScene->update();
	imageView->setSceneRect(image.rect());
	QString status = "";
	if (name != "live") {

		status = QString("%1, %2x%3, %4 Bytes").arg(name).arg(image.width())
			.arg(image.height()).arg(QFile(name).size());
	}
	else {
		status = QString("%1, %2x%3,%4帧").arg(name).arg(image.width())
			.arg(image.height()).arg(1000 / cameraTimer->interval());
	}

	mainStatusLabel->setText(status);
	//currentImagePath = path;
}

void CVMainWindow::showImageInListView(cv::Mat& mat, QString name)
{
	auto items = item_model->findItems(name);
	QPixmap pixmap = QPixmap::fromImage(QEE::Utils::Mat2QImage(mat));
	QStandardItem* item = nullptr;
	if (items.size() > 0) {
		item = items.at(0);
	}
	else {
		item = new QStandardItem();
		item_model->appendRow(item);
	}
	QModelIndex index = item_model->indexFromItem(item);
	item_model->setData(index, pixmap.scaledToWidth(145), Qt::DecorationRole);
	item_model->setData(index, name, Qt::DisplayRole);
	image_listview->scrollTo(index);
	//}
}
