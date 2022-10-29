#include <iostream>
#include <string>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "places_qt.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  QQmlApplicationEngine engine;
  PlacesQt places;
  PlacesQt::declareQml();
  engine.rootContext()->setContextProperty("appPlaces", &places);

  engine.load(QUrl(QStringLiteral("qrc:///res/qml/main.qml")));
  return app.exec();
}