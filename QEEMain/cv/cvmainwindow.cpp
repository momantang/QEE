#include "cvmainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QGridLayout>
#include <QMessageBox>
#include <vector>
#include "utils.h"


Q_GLOBAL_STATIC(CVMainWindow, cvmw)
CVMainWindow::CVMainWindow(QWidget* parent) :
	QMainWindow(parent)
{
	connect(this, &CVMainWindow::push_back, this, &CVMainWindow::addMat);
	this->setWindowTitle("OpenCV4 Demo");
	this->initUI();
	this->initBaseToolBar();
	this->showImage("D:/images/car.jpg");
	/*
		this->statusLabel=new QLabel("当前状态");
		connect(this,&CVMainWindow::updateStatus,this,[=](QString status){
			this->statusLabel->setText(status);
		});
		connect(ui->actionOpen_Image,&QAction::triggered,this,[=](){
			QString filename=QFileDialog::getOpenFileName(this,"请选择打开的图片","d:/","image(*.jpg);;");
			if(filename.isEmpty())
				return;
			qDebug()<<filename;
			emit updateStatus("打开文件 "+filename);
			mats.clear();
			cv::Mat source=cv::imread(filename.toStdString());
			mats.push_back(source);
			QImage sourceImage;
			Utils::Mat2QImage(source,sourceImage);
			ui->souce_label->setPixmap(QPixmap::fromImage(sourceImage));

		});
	*/
}
CVMainWindow* CVMainWindow::inst() {
	return cvmw();
}
CVMainWindow::~CVMainWindow()
{
}

void CVMainWindow::initUI()
{
	this->resize(1024, 768);
	fileMenu = menuBar()->addMenu("&File");
	toolMenu = menuBar()->addMenu("&Tool");
	editMenu = menuBar()->addMenu("&Edit");
	aboutMenu = menuBar()->addMenu("&About");

	fileToolBar = addToolBar("File");
	editToolBar = addToolBar("edit");
	morphologyToolBar = addToolBar("morphology");
	morphologyToolBar->setVisible(false);


	//main center;
	QGridLayout* main_layout = new QGridLayout;
	QHBoxLayout* imageLayout = new QHBoxLayout;
	imageSrcScene = new QGraphicsScene(this);
	imageSrcView = new QGraphicsView(imageSrcScene);
	imageDstScene = new QGraphicsScene(this);
	imageDstView = new QGraphicsView(imageDstScene);

	imageLayout->addWidget(imageSrcView);
	imageLayout->addWidget(imageDstView);
	main_layout->addLayout(imageLayout, 0, 0);
	image_list = new QListView(this);
	image_list->setViewMode(QListView::IconMode);
	image_list->setResizeMode(QListView::Adjust);
	image_list->setSpacing(5);
	image_list->setWrapping(false);
	image_list->setMinimumHeight(145);
	image_list->setMaximumHeight(145);
	list_model = new QStandardItemModel(this);
	image_list->setModel(list_model);
	connect(image_list, &QListView::clicked, this, [=](const QModelIndex& index) {
		qDebug() << index.row();
		qDebug() << "mats size: " << mats.size();
		showDstMat(mats.at(index.row()));
		currentMat = mats.at(index.row());
		for (int i = 0; i < mats.size(); i++) {
			auto name = QString("mat %1").arg(i).toStdString();
			//cv::imshow(name, mats.at(i));
		}
		});
	main_layout->addWidget(image_list, 1, 0);
	//main_layout->setRowStretch(0, 3);
	//main_layout->setRowStretch(1, 1);

	QWidget* widget = new QWidget();
	widget->setLayout(main_layout);
	setCentralWidget(widget);


	this->createAction();
	


}
void CVMainWindow::initBaseToolBar() {
	baseToolBar = addToolBar("&base");
	cvColorComboBox = new QComboBox(this);
	cvColorComboBox->addItem("BGR2Gray");
	cvColorComboBox->addItem("Gray2BGR");
	cvColorComboBox->addItem("BGR2HSV");
	cvColorComboBox->addItem("BGR2RGB");
	cvColorComboBox->addItem("BGR2BGRA");
	baseToolBar->addWidget(new QLabel("转换："));
	baseToolBar->addWidget(cvColorComboBox);
	connect(cvColorComboBox, &QComboBox::activated, this, [this](int index) {
		qDebug() << index;
		cv::Mat mat;
		switch (index)
		{
		case 0:
			cv::cvtColor(currentMat, mat, cv::COLOR_BGR2GRAY);
			break;
		case 1:
			cv::cvtColor(currentMat, mat, cv::COLOR_GRAY2BGR);
			break;
		case 2:
			cv::cvtColor(currentMat, mat, cv::COLOR_BGR2HSV);
			break;
		case 3:
			cv::cvtColor(currentMat, mat, cv::COLOR_BGR2RGB);
			break;
		case 4:
			cv::cvtColor(currentMat, mat, cv::COLOR_BGR2BGRA);
			break;
		default:
			break;
		}
		if (mat.empty())
		{
			return;
		}
		push_back(mat, "cvColco");
		});
}

void CVMainWindow::createAction()
{
	openImageAction = new QAction("&Open Image", this);
	fileMenu->addAction(openImageAction);

	exitAction = new QAction("&Exit", this);
	fileMenu->addAction(exitAction);

	fileToolBar->addAction(openImageAction);
	fileToolBar->addAction(exitAction);



	zoomInAction = new QAction("&Zoom In", this);
	editMenu->addAction(zoomInAction);
	editToolBar->addAction(zoomInAction);


	zoomOutAction = new QAction("&Zoom Out", this);
	editMenu->addAction(zoomOutAction);
	editToolBar->addAction(zoomOutAction);

	//ToolMenu

	splitAction = new QAction("Split", this);
	toolMenu->addAction(splitAction);
	connect(splitAction, &QAction::triggered, this, [=]() {
		//
		qDebug() << "split action";
		if (currentMat.type() != CV_8UC3) {
			QMessageBox::warning(this, "操作错误","不能被split");
			return;
		}
		std::vector<cv::Mat> splits;
		cv::split(currentMat, splits);
		qDebug() << splits.size();
		this->push_back(splits.at(0), "R");
		this->push_back(splits.at(1), "G");
		this->push_back(splits.at(2), "B");
		});

	//形态学
	kernelCombobox = new QComboBox;
	kernelCombobox->addItem("矩形");
	kernelCombobox->addItem("椭圆形");
	kernelCombobox->addItem("星十字");
	kernelWidthCombobox = new QComboBox;
	kernelHeightCombobox = new QComboBox;
	for (int i = 1; i < 20;) {
		kernelWidthCombobox->addItem(QString("%1").arg(i));
		kernelHeightCombobox->addItem(QString("%1").arg(i));
		i = i + 2;
	}
	morphologyCombobox = new QComboBox;
	morphologyCombobox->addItem("腐蚀");
	morphologyCombobox->addItem("膨胀");
	morphologyCombobox->addItem("开运算");
	morphologyCombobox->addItem("闭运算");
	morphologyCombobox->addItem("形态学梯度");
	morphologyCombobox->addItem("顶帽");
	morphologyCombobox->addItem("黑帽");
	morphologyToolBar->addWidget(new QLabel("内核："));
	morphologyToolBar->addWidget(kernelCombobox);
	morphologyToolBar->addWidget(new QLabel("内核X："));
	morphologyToolBar->addWidget(kernelWidthCombobox);
	morphologyToolBar->addWidget(new QLabel("内核Y："));
	morphologyToolBar->addWidget(kernelHeightCombobox);
	morphologyToolBar->addWidget(new QLabel("命令："));
	morphologyToolBar->addWidget(morphologyCombobox);

	//about menu
	aboutAction = new QAction("关于", this);
	donateAction = new QAction("捐赠", this);
	aboutMenu->addAction(aboutAction);
	aboutMenu->addAction(donateAction);

	connect(aboutAction, &QAction::triggered, this, [=]() {
		if (aboutWidget == nullptr) {
			aboutWidget = new AboutWidget;
		}
		aboutWidget->show();
		});
	connect(donateAction, &QAction::triggered, this, [=]() {
		QMessageBox::information(this, "捐赠", "谢谢你捐赠");
		});

	connect(morphologyCombobox, &QComboBox::activated, this, [=](int index) {
		qDebug() << "morphologyCombobox" << index;
		if (currentMat.empty()) {
			QMessageBox::warning(this, "no mat", "请打开图片");
			return;
		}
		});




	//editToolBar->setVisible(false);


	connect(openImageAction, &QAction::triggered, this, &CVMainWindow::openImage);
	connect(zoomInAction, &QAction::triggered, this, &CVMainWindow::zoomIn);
	connect(zoomOutAction, &QAction::triggered, this, &CVMainWindow::zoomOut);
	connect(exitAction, &QAction::triggered, this, [=]() {
		this->close();
		});

}


void CVMainWindow::createToolBar()
{
}

void CVMainWindow::showImage(QString path)
{
	cv::Mat img = cv::imread(path.toStdString());
	currentMat = img;
	if (img.empty())
	{
		return;
	}
	push_back(img,path);
	QImage frame(
		img.data,
		img.cols,
		img.rows,
		img.step,
		QImage::Format_BGR888);
	QPixmap pixmap = QPixmap::fromImage(frame);
	imageSrcScene->clear();
	imageSrcScene->addPixmap(pixmap);
	imageSrcScene->update();
	imageSrcView->setSceneRect(pixmap.rect());
}

void CVMainWindow::morphology(const cv::Mat& src, cv::Mat& dst, const QString action)
{
}

void CVMainWindow::openImage()
{
	QFileDialog dialog(this);
	dialog.setWindowTitle("打开图片");
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setDirectory("d:/images");
	dialog.setNameFilter("Images (*.png *.bemp *.jpg)");
	QStringList filePahts;
	if (dialog.exec()) {
		filePahts = dialog.selectedFiles();
		showImage(filePahts.at(0));
	}
}

void CVMainWindow::zoomIn()
{
	this->imageSrcView->scale(1.2, 1.2);
}

void CVMainWindow::zoomOut()
{
	this->imageSrcView->scale(1 / 1.2, 1 / 1.2);
}

void CVMainWindow::prevImage()
{
}

void CVMainWindow::nextImage()
{
}

void CVMainWindow::saveAs()
{
}

void CVMainWindow::openCamera()
{
}

void CVMainWindow::stopCamera()
{
}

void CVMainWindow::releaseCamera()
{
}

void CVMainWindow::captureImage()
{
}

void CVMainWindow::updateToolBar(QString tips)
{
}

QImage fromMat(cv::Mat mat) {
	if (mat.empty()) {
		return QImage();
	}
	if (mat.type() == CV_8UC3) {
		return QImage((const unsigned char*)mat.data, mat.cols, mat.rows, QImage::Format_BGR888);
	}
	else if (mat.type() == CV_8UC1) {
		return QImage((const unsigned char*)mat.data, mat.cols, mat.rows,mat.cols*mat.channels(), QImage::Format_Grayscale8);
	}
	return QImage();
}
void CVMainWindow::addMat(cv::Mat mat, QString name)
{
	mats.push_back(mat);
	QPixmap pixmap = QPixmap::fromImage(fromMat(mat));
	QStandardItem* item = new QStandardItem();
	list_model->appendRow(item);
	QModelIndex index = list_model->indexFromItem(item);
	list_model->setData(index, pixmap.scaledToWidth(145), Qt::DecorationRole);
	list_model->setData(index, name, Qt::DisplayRole);
	image_list->scrollTo(index);

}

void CVMainWindow::showDstMat(cv::Mat img)
{
	if (img.empty())
	{
		return;
	}
	if (img.type() != CV_8UC1 && img.type() != CV_8UC3) {
		return;
	}
	QImage frame(
		img.data,
		img.cols,
		img.rows,
		img.step,
		(img.type() == CV_8UC3) ? QImage::Format_BGR888 : QImage::Format_Grayscale8);

	QPixmap pixmap = QPixmap::fromImage(frame);
	imageDstScene->clear();
	imageDstScene->addPixmap(pixmap);
	imageDstScene->update();
	imageDstView->setSceneRect(pixmap.rect());
}
