#include <qsound.h>
#include "audio.h"
Audio::Audio()
{
    background = new QSound(":/sounds/sounds/background.wav");
}

void Audio::playBackgroundMusic()
{
    background->play();
}


