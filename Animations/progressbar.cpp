#include "progressbar.h"
#include <iostream>

using namespace pb;

ProgressBar::ProgressBar(float minValue, float maxValue) :
	minValue(minValue), maxValue(maxValue), active(minValue < maxValue) {}

ProgressBar::ProgressBar(float minValue, float maxValue, bool active) :
	minValue(minValue), maxValue(maxValue), active(active) {}

void ProgressBar::print()
{
    if (active) {
        progress = currentValue / (maxValue - minValue);
        std::cout << ansi::foreground_red << "[";
        int pos = int(barWidth * progress);
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos)
				std::cout << "=";
            else if (i == pos)
				std::cout << ">";
            else
				std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r" << ansi::reset << std::endl;
    }
}

void ProgressBar::update(float currentValue)
{
    active = true;
    if (currentValue == -1)
        active = false;
    this->currentValue = currentValue;
}

float ProgressBar::getProgress()
{
    return progress;
}

void ProgressBar::setActive(bool value)
{
    active = value;
}

bool ProgressBar::getActive()
{
    return active;
}
