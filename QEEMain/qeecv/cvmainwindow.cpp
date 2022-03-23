#include "cvmainwindow.h"
#include "../Utils.h"
#include "settingsdialog.h"
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
	this->resize(1920, 800);
	this->initUI();
	this->initActions();
	this->initAOI();

	connect(this, &CVMainWindow::showCommand_signal, this, &CVMainWindow::showCommand);
	emit showCommand_signal("命令提示窗口");
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
	textEdit->setReadOnly(true);
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
	settingAction = new QAction("&setting", this);
	fileMenu->addAction(settingAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	voiceAction = new QAction("&Voice Order", this);
	fileToolBar = addToolBar("file");
	fileToolBar->addAction(settingAction);
	fileToolBar->addAction(voiceAction);

	connect(fileMenu, &QMenu::triggered, this, [this](QAction* act) {
		//打开图片
		if (act == openImageAction) {
			QFileDialog dlg(this);
			dlg.setDirectory("D:/Qee/data/images");
			dlg.setFileMode(QFileDialog::ExistingFile);
			dlg.setNameFilter("Image(*.jpg *.png *.bmp *.pgm)");
			if (dlg.exec()) {
				auto path = dlg.selectedFiles();
				cv::Mat img = cv::imread(path.at(0).toStdString());
				emit this->updateCurrentMat(img, path.at(0));
				emit showCommand_signal("打开文件："+path.at(0));
			}
		}
		//打开摄像头
		if (act == openCameraAction) {
			camera = CameraFactory::instance("build-in");
			camera->openCamera();
			cameraTimer->setInterval(100);
			cameraTimer->start();
			emit showCommand_signal("打开内置摄像头" );
		}
		//暂停摄像头
		if (act == pauseCameraAction) {
			cameraTimer->stop();
			emit showCommand_signal("暂停内置摄像头定时器" );
		}
		//关闭摄像头
		if (act == closeCameraAction) {
			cameraTimer->stop();
			camera->closeCamera();
			emit showCommand_signal("release 内置摄像头");
		}
		if (act == settingAction) {
			settingsDialog.show();
			settingsDialog.setFocus();
		}
		if (act == voiceAction) {
			audioDialog = new AudioDialog(this);
			audioDialog->show();
		}

		if (act == exitAction) {
			this->close();
		}
		});
	connect(voiceAction, &QAction::triggered, this, [this]() {
		audioDialog = new AudioDialog(this);
		audioDialog->show();
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
	readGrayAction = new QAction("&read gray img", this);
	medianBlurAction = new QAction("&Median Blur", this);
	calculateLightAction = new QAction("&calculateLightAction", this);
	removeLight1Action = new QAction("&removeLight1", this);
	removeLight2Action = new QAction("&removeLight2Action", this);
	aoiMenu->addAction(readGrayAction);
	aoiMenu->addAction(medianBlurAction);
	aoiMenu->addAction(calculateLightAction);
	aoiMenu->addAction(removeLight1Action);
	aoiMenu->addAction(removeLight2Action);
	//aoiMenu->addAction(medianBlurAction);
	connect(aoiMenu, &QMenu::triggered, this, [this](QAction* act) {
		if (act == readGrayAction) {
			cv::Mat gray = MatOperator::read2Gray("d:/qee/data/images/test_noise.pgm");
			emit updateCurrentMat(gray, "aoi_gray");
		}else
		if (act == medianBlurAction) {
			emit showCommand_signal("消除噪声");
			cv::Mat img_noise;
			cv::medianBlur(currentMat, img_noise, 3);
			emit updateCurrentMat(img_noise, "aoi_img_noise");
		}else
		if (act == calculateLightAction) {
			cv::Mat pattern = MatOperator::calculateLightPattern(currentMat);
			emit updateCurrentMat(pattern, "aoi_pattern");
		}
		else if (act == removeLight1Action) {
			cv::Mat aux = MatOperator::removeLight(mat_map.at("aoi_img_noise"),mat_map.at("aoi_pattern"),1);
			emit updateCurrentMat(aux, "aoi_aux");
		}
		else if (act == removeLight2Action) {
			cv::Mat aux = MatOperator::removeLight(mat_map.at("aoi_img_noise"), mat_map.at("aoi_pattern"), 0);
			emit updateCurrentMat(aux, "aoi_aux");
		}
		});


}


void CVMainWindow::showCommand(QString cmd)
{
	this->textEdit->insertPlainText(cmd+"\n");
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
