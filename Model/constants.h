#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

#include <QString>

namespace constants {
const double kEpsilon = 0.0001;

const int kGameWidth = 1920;
const int kGameHeight = 1080;

const double kViewCircleDefault = 540;
const double kViewCircleMax = 2200;
const double kViewCircleMin = 500;

const int kTimeBetweenTicks = 100;
const int kTimeScale = 100;

const double kResizerSpeed = 25.;
const double kResizerScale = 50.;

const int kMinTimeToGoHome = 1e3;
const int kMaxTimeToGoHome = 1e8;

const double kSemiMinorCoefficient = 0.8;

const double kCatRunCoefficient = 2;
const double kCatGroupSpeed = 10;

const int kMinRunAwayDistance = 100;
const int kMaxRunAwayDistance = 500;

const double kCatGroupIncCoefficient = 1.1;

const QString kApplicationName = "Far from home";
}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
