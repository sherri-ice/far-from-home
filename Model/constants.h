#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

#include <QString>

namespace constants {
const double kEpsilon = 0.0001;

const int kGameWidth = 1920;
const int kGameHeight = 1080;

const double kViewCircleDefault = 540;
const double kViewCircleMax = 4200;
const double kViewCircleMin = 250;

const int kTimeBetweenTicks = 100;
const int kTimeScale = 100;

const double kResizerSpeed = 60.;
const double kResizerScale = 50.;

const double kSemiMinorCoefficient = 0.8;

const QString kApplicationName = "Far from home";
}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
