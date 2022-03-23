#pragma once
#ifdef __cplusplus
#define __STDC_CONSTANT_MACROS
#ifdef _STDINT_H
#undef _STDINT_H
#endif
extern "C" {
#include <libavutil/log.h>
#include<libavdevice/avdevice.h>
#include <libavformat/avformat.h>

}
#endif
#include<string>
class AudioRecord
{
public:
	static AudioRecord& getInstance() {
		static AudioRecord instance;
		return instance;
	}
	AudioRecord(const AudioRecord&) = delete;
	AudioRecord(AudioRecord&) = delete;
	AudioRecord& operator=(const AudioRecord&) = delete;
	AudioRecord& operator=(AudioRecord&) = delete;

	void openMicrophone(std::string deviceName);//打开麦克风
	void recordFile(std::string fileName);
	void setISRecord(bool isr) { this->isRecord = isr; }
	bool getIsRecord() { return this->isRecord; }
private:
	AudioRecord();
	~AudioRecord();
	std::string deviceName;
	AVFormatContext* fmt_ctx = nullptr;
	AVInputFormat* inputFormat = nullptr;
	bool isRecord = false;
	AVPacket pkt;
};

