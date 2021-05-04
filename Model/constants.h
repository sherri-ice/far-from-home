#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

#include <QString>

namespace constants {
const double kEpsilon = 0.0001;

const int kGameWidth = 960;
const int kGameHeight = 540;

const double kViewCircleDefault = 540;

const int kTimeBetweenTicks = 10;
const int kTimeScale = 100;

const double kResizerSpeed = 60.;
const double kResizerScale = 50.;

const int kMinTimeToGoHome = 1e3;
const int kMaxTimeToGoHome = 1e8;

const double kSemiMinorCoefficient = 0.8;

const double kCatRunCoefficient = 2;
const double kCatGroupSpeed = 10;

const double kCatGroupIncCoefficient = 1.1;

const QString kApplicationName = "Far from home";
}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
