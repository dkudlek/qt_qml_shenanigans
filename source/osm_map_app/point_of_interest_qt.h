#ifndef QT_QML_SHENANIGANS_POINT_OF_INTEREST_QT_H
#define QT_QML_SHENANIGANS_POINT_OF_INTEREST_QT_H

#include <memory>

#include <QObject>
#include <QQmlEngine>
#include <QGeoCoordinate>


class PointOfInterestQt : public QObject {
  Q_OBJECT
  Q_PROPERTY(QGeoCoordinate coordinate READ getCoordinate NOTIFY coordinateChanged)
  Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
signals:

  void coordinateChanged();
  void nameChanged();

public:
  PointOfInterestQt(QString name="", QGeoCoordinate coordinate=QGeoCoordinate())
      : mName(name), mCoordinate(coordinate){};
  ~PointOfInterestQt() = default;
  static void declareQml(){
      qmlRegisterType<PointOfInterestQt>("Tracker", 1, 0, "PointOfInterest");
  }

  QString getName() const { return mName; }
  QGeoCoordinate getCoordinate() const { return mCoordinate; }

private:
  QString mName;
  QGeoCoordinate mCoordinate;
};

#endif // QT_QML_SHENANIGANS_POINT_OF_INTEREST_QT_H
