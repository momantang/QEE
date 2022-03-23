#include "AudioRecord.h"
void AudioRecord::openMicrophone(std::string deviceName)
{
	inputFormat = av_find_input_format("DSHOW");
	avformat_open_input(&fmt_ctx, deviceName.c_str(), inputFormat, nullptr);
}
void AudioRecord::recordFile(std::string fileName)
{
}
AudioRecord::AudioRecord()
{
	avdevice_register_all();
}

AudioRecord::~AudioRecord()
{
}
