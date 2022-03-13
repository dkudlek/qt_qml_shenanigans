#ifndef QT_QML_SHENANIGANS_PLACE_QT_H
#define QT_QML_SHENANIGANS_PLACE_QT_H

#include <memory>

#include <QObject>
#include <QtPositioning/qgeocoordinate.h>


class PlaceQt : public QObject {
  Q_OBJECT
  Q_PROPERTY(QGeoCoordinate placeCoordinate READ getCoordinate NOTIFY coordinateChanged)
  Q_PROPERTY(QString placeName READ getName NOTIFY nameChanged)
signals:

  void coordinateChanged();
  void nameChanged();

public:
  explicit PlaceQt(QString name="", QGeoCoordinate coordinate=QGeoCoordinate(0,0));


  //static void declareQml();
  [[nodiscard]] QString getName() const;
  [[nodiscard]] QGeoCoordinate getCoordinate() const;

private:
  QString mName;
  QGeoCoordinate mCoordinate;
};

#endif