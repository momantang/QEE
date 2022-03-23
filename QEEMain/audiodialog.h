#ifndef AUDIODIALOG_H
#define AUDIODIALOG_H

#include <QDialog>
#include <QFile>
#include <QtWidgets>
#include <qaudiosource.h>
#include <qaudioformat.h>
#include <qmediadevices.h>
//#include "VoiceOrder.h"
#include "AudioRecord.h"
/*
namespace Ui {
class AudioDialog;
}
*/
class VoiceOrder;
class AudioDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AudioDialog(QWidget *parent = nullptr);
    ~AudioDialog();
 signals:
    void sig_cmd(QString cmd);
    void sig_updateStatus(QString status);
public slots:
    void stopRecording();
    void updateStatus(QString status);

    void handleStateChanged(QAudio::State state);
private:
    VoiceOrder* voiceOrder;
    QString tempFilePath="test.pcm";
    QFile dstFile;
    QAudioFormat audioFormat;
    QAudioSource* audio;

    QLabel* rsLabel;
    QLabel* statusLabel;
    QPushButton* startButton;//启动录音
    QPushButton* uploadButton;// 识别语言
   // Ui::AudioDialog *ui;
};

#endif // AUDIODIALOG_H
