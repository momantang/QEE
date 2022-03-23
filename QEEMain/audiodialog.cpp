#include "audiodialog.h"
//#include "VoiceOrder.h"
//#include "ui_audiodialog.h"

AudioDialog::AudioDialog(QWidget* parent) :
	QDialog(parent)
{
	statusLabel = new QLabel("当前状态");
	startButton = new QPushButton("start Butoon", this);
	uploadButton = new QPushButton("语言识别", this);
	QHBoxLayout* mainLayout = new QHBoxLayout;
	QVBoxLayout* buttonLayout = new QVBoxLayout;
	buttonLayout->addWidget(statusLabel);
	buttonLayout->addWidget(startButton);
	buttonLayout->addWidget(uploadButton);

	rsLabel = new QLabel("识别结果");
	mainLayout->addWidget(rsLabel);
	mainLayout->addLayout(buttonLayout);
	this->setLayout(mainLayout);
	this->resize(600, 400);

	//voiceOrder = new VoiceOrder;
	/*
	dstFile.setFileName("d:/dev/test.pcm");
	dstFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

	audioFormat.setSampleRate(16000);
	audioFormat.setChannelCount(1);
	audioFormat.setSampleFormat(QAudioFormat::Int16);
	audioFormat.setChannelConfig(QAudioFormat::ChannelConfigMono);
	QAudioDevice info = QMediaDevices::defaultAudioInput();
	for (auto format : info.supportedSampleFormats() ){
		qDebug() << "supported format: " << format;
	}
	if (!info.isFormatSupported(audioFormat))
	{
		qWarning() << "Defautl format not supported tring to use the nearest.";
		return;
	}
	else {
		qWarning() << " goog job it suppport..";
	}
	audio = new QAudioSource(audioFormat, this);
	connect(audio, &QAudioSource::stateChanged, this, &AudioDialog::handleStateChanged);
	*/
	connect(this, &AudioDialog::sig_updateStatus, this, &AudioDialog::updateStatus);
	
	connect(startButton, &QPushButton::clicked, this, [this]() {
		QTimer::singleShot(3000, this, SLOT(stopRecording()));
		emit sig_updateStatus("录音中（3秒）");
//		this->voiceOrder->startRecord();
		});
	connect(uploadButton, &QPushButton::clicked, this, [this]() {
		emit sig_updateStatus("识别中");
	//	QString rs= this->voiceOrder->asr();
	//	qDebug() << rs;
		});
	//connect(stopButton, &QPushButton::clicked, this, &AudioDialog::stopRecording);
}

AudioDialog::~AudioDialog()
{
	//   delete ui;
}
void AudioDialog::stopRecording()
{
	qDebug() << "stop recode";
	emit sig_updateStatus("录音结束");
	//this->voiceOrder->stopRecord();
}
void AudioDialog::updateStatus(QString status)
{
	this->statusLabel->setText(status);
}
void AudioDialog::handleStateChanged(QAudio::State state) {
	switch (state) {
	case QAudio::StoppedState:
		if (audio->error() != QAudio::NoError) {
			// Error handling
		}
		else {
			// Finished recording
		}
		break;

	case QAudio::ActiveState:
		// Started recording - read from IO device
		break;

	default:
		// ... other cases as appropriate
		break;
	}

}