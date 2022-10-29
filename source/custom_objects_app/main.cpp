#include <iostream>
#include <string>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "argparse.hpp"
#include "element_qt.h"
#include "element_backend_qt.h"

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("custom_objects_app");

    QApplication app(argc, argv);
    ElementQt::declareQml();
    ElementBackendQt::declareQml();
    ElementBackendQt backend;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backend", &backend);

    engine.load(QUrl(QStringLiteral("qrc:///res/qml/main.qml")));
    return app.exec();
}