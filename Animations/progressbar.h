#ifndef PROGRESSBAR_H_SENTRY
#define PROGRESSBAR_H_SENTRY

#include "colors.h"
#include "constants.h"

namespace pb
{
	class ProgressBar;
}

class pb::ProgressBar {
	
    float progress = 0.0;
    int barWidth = constants::WIDTH - 6;
    float minValue = 0;
    float maxValue = 1;
    float currentValue = 0;
    bool active = false;

public:

    ProgressBar(float minValue, float maxValue);
    ProgressBar(float minValue, float maxValue, bool active);
    void print();
    void update(float currentValue);
    float getProgress();
    void setActive(bool value);
    bool getActive();
};

#endif
