#ifndef QT_QML_SHENANIGANS_PLACES_QT_H
#define QT_QML_SHENANIGANS_PLACES_QT_H

#include <memory>

#include <QObject>
#include <QtPositioning/qgeopath.h>

#include "place_qt.h"

class PlacesQt : public QObject {
  Q_OBJECT
  Q_PROPERTY(QList<QObject *> places READ getPlaces NOTIFY placesChanged)
  Q_PROPERTY(QGeoPath path READ getPath NOTIFY pathChanged)
signals:

  void placesChanged();
  void pathChanged();

public:
  PlacesQt();


  static void declareQml();

  [[nodiscard]] QList<QObject *> getPlaces() const;
  QGeoPath getPath() const;

private:
  std::vector<std::unique_ptr<PlaceQt>> mPlaces;
};

#endif