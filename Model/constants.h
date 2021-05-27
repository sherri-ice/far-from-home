#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

#include <QString>

namespace constants {
const double kEpsilon = 0.0001;

const int kNumOfCats = 10;

const int kGameWidth = 1600;
const int kGameHeight = 900;

const double kViewCircleDefault = 540;
const double kViewCircleMax = 2200;
const double kViewCircleMin = 500;

const int kTimeBetweenTicks = 10;
const int kTimeScale = 100;

const double kResizerSpeed = 25.;
const double kResizerScale = 50.;

const double kSemiMinorCoefficient = 0.8;

const double kCatRunCoefficient = 2;

const int kMinRunAwayDistance = 100;
const int kMaxRunAwayDistance = 500;

const double kCatGroupIncCoefficient = 1.1;

const double kMediumHungerPercent = 0.4;
const double kSevereHungerPercent = 0.15;
const double kSpeedOfHunger = 0.03;

const double kWidthForFoodGeneration = 250;
const double kHeightForFoodGeneration = 500;


const QString kApplicationName = "Far from home";
}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
