#pragma once
#ifndef __VOIICE_ORDER_H__
#define __VOIICE_ORDER_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>


#include <QString>
#include <QDialog>
#include <QFile>
#include <QtWidgets>
#include <qaudiosource.h>
#include <qaudioformat.h>
#include <qmediadevices.h>
namespace aip {
	class Speech;
}
struct FeedBack {

};
class VoiceOrder : public QObject
{
	   Q_OBJECT
public:
	VoiceOrder(QObject *parent=nullptr);
	~VoiceOrder();
	void startRecord();
	void stopRecord();
	QString asr(aip::Speech* client=nullptr);//百度语言识别api
private:
	QString fileName;
	QFile pcmFile;
	QAudioFormat audioFormat;
	QAudioSource* audio=nullptr;
	aip::Speech* client;

};
#endif __VOIICE_ORDER_H__
