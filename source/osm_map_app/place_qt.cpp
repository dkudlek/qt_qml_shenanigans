#include "place_qt.h"

PlaceQt::PlaceQt(QString name, QGeoCoordinate coordinate)
    : mName(name), mCoordinate(coordinate){};

QString PlaceQt::getName() const { return mName; }

QGeoCoordinate PlaceQt::getCoordinate() const { return mCoordinate; }