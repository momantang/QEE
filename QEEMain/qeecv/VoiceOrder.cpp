#include "VoiceOrder.h"
#include "speech.h"
/// <summary>
/// 
/// 修改jsoncpp使得返回是utf8 而不是uicode格式
/// </summary>
/// <param name="root"></param>
/// <returns></returns>
///
std::string JsonToString(const Json::Value& root)
{
	static Json::Value def = []() {
		Json::Value def;
		Json::StreamWriterBuilder::setDefaults(&def);
		def["emitUTF8"] = true;
		return def;
	}();

	std::ostringstream stream;
	Json::StreamWriterBuilder stream_builder;
	stream_builder.settings_ = def;//Config emitUTF8
	std::unique_ptr<Json::StreamWriter> writer(stream_builder.newStreamWriter());
	writer->write(root, &stream);
	return stream.str();
}
QString getDateTimeStr() {
	QDateTime dt = QDateTime::currentDateTime();
	return dt.toString("yyyyMMddhhmmss");
}
VoiceOrder::VoiceOrder(QObject *parent)
	: QObject(parent)
{
	 client = new aip::Speech("25768436", "LTHyjCutNFzyp25ppz1CfqNV", "rt5V3OHKF28G4bOgnmIlrtGKRwG9Kge3");

	client->setDebug(false);
	/*

	pcmFile.setFileName("d:/dev/"+getDateTimeStr() + ".pcm");
	pcmFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

	audioFormat.setSampleRate(16000);
	audioFormat.setChannelCount(1);
	audioFormat.setSampleFormat(QAudioFormat::Int16);
	audioFormat.setChannelConfig(QAudioFormat::ChannelConfigMono);
	QAudioDevice info = QMediaDevices::defaultAudioInput();
	for (auto format : info.supportedSampleFormats()) {
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
		*/
}

VoiceOrder::~VoiceOrder()
{
}

void VoiceOrder::startRecord()
{
	fileName = "d:/dev/tmp/" + getDateTimeStr() + ".pcm";
	pcmFile.setFileName(fileName);
	pcmFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

	audioFormat.setSampleRate(16000);
	audioFormat.setChannelCount(1);
	audioFormat.setSampleFormat(QAudioFormat::Int16);
	audioFormat.setChannelConfig(QAudioFormat::ChannelConfigMono);
	QAudioDevice info = QMediaDevices::defaultAudioInput();
	for (auto format : info.supportedSampleFormats()) {
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
	audio->start(&pcmFile);

}

void VoiceOrder::stopRecord()
{
	audio->stop();
	pcmFile.close();
	delete audio;
}

QString VoiceOrder::asr(aip::Speech* client)
{
	if (nullptr != client) {
		this->client = client;
	}
	std::map<std::string, std::string> options;
	//options.emplace(std::pair<std::string,std::string>("dev_pid","1637"));
	std::string file_content;
	aip::get_file_content(fileName.toStdString().c_str(), &file_content);

	Json::Value result = this->client->recognize(file_content, "pcm", 16000, options);
	//common::tool::StringTool::UnicodeToUtf8();
	;
	std::cout << "out" << std::endl << JsonToString(result) << std::endl;
	std::cout << "out" << std::endl << JsonToString(result) << std::endl;
	return QString::fromStdString(JsonToString(result));
}
