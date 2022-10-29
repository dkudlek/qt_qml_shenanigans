#include "places_qt.h"

#include <QQmlEngine>

PlacesQt::PlacesQt() {
  mPlaces.push_back(std::make_unique<PlaceQt>(
      "Heilbad Heiligenstadt",
      QGeoCoordinate(51.377381, 10.134458)));
  mPlaces.push_back(std::make_unique<PlaceQt>(
      "Regensburg",
      QGeoCoordinate(49.017222, 12.096944)));
  mPlaces.push_back(std::make_unique<PlaceQt>(
      "Ilmenau", QGeoCoordinate(50.687222, 10.914167)));
  mPlaces.push_back(std::make_unique<PlaceQt>(
      "Stuttgart", QGeoCoordinate(48.775556, 9.182778)));
  mPlaces.push_back(std::make_unique<PlaceQt>(
      "Kronach", QGeoCoordinate(50.241111, 11.328056)));
}

QList<QObject *> PlacesQt::getPlaces() const {
  QList<QObject *> returnList;
  for (auto &element : mPlaces) {
    returnList.push_back(element.get());
  }
  return returnList;
}

QGeoPath PlacesQt::getPath() const {
  QGeoPath returnPath;
  returnPath.addCoordinate(mPlaces[0]->getCoordinate());
  returnPath.addCoordinate(mPlaces[1]->getCoordinate());
  returnPath.addCoordinate(mPlaces[2]->getCoordinate());
  returnPath.addCoordinate(mPlaces[3]->getCoordinate());
  returnPath.addCoordinate(mPlaces[4]->getCoordinate());
  return returnPath;
}

void PlacesQt::declareQml() {
  qmlRegisterType<PlacesQt>("com.goliath-sw.test", 1, 0, "Places");
}