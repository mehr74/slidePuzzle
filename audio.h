#ifndef AUDIO_H
#define AUDIO_H

class QSound;
class Audio
{
public:
    Audio();
    void playBackgroundMusic();

private:
    QSound *background;
    QSound *sound;
    bool isSoundPlaying;
    bool isBackgroundPlaying;
};

#endif
