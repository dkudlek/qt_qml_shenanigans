#include <iostream>
#include <string>
#include <memory>

#include <QDebug>

#include <QtXml/QtXml>
#include <QFile>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QGeoPath>

#include "point_of_interest_qt.h"
#include "app_backend_qt.h"
#include "point_of_interest_qt_model.h"

QDomDocument getContent(const QString& fileName){
    QDomDocument xmlBOM;
    // Load xml file as raw data
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Error while loading file
        std::cerr << "Error while loading file" << std::endl;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f);
    f.close();
    return xmlBOM;
}

QGeoPath process (const QDomDocument track){
    QDomElement root=track.documentElement();
    const auto trackElement = root.elementsByTagName("trk");
    const auto path = trackElement.at(0).firstChildElement("trkseg");
    QGeoPath geoPath;
    for(auto i = path.firstChild(); !i.isNull(); i = i.nextSibling()){
        const auto attr = i.attributes();
        geoPath.addCoordinate(
                    QGeoCoordinate(attr.namedItem("lat").nodeValue().toDouble(), attr.namedItem("lon").nodeValue().toDouble()));
    }
    return geoPath;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("track-viewer");
    QCoreApplication::setApplicationVersion("0.9");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", QCoreApplication::translate("main", "The file to open."));
    parser.addOptions({{{"t", "track"},
                        QCoreApplication::translate("main", "Copy all source files into <directory>."),
                        QCoreApplication::translate("main", "directory")},
                });

    parser.process(app);
    const QString targetFile = parser.value("track");
    auto path = process(getContent(targetFile));
    const auto poi = std::make_shared<PointOfInterestQt>("HIG", QGeoCoordinate(51.37613152240059, 10.146611476648038));
    QQmlApplicationEngine engine;
    PointOfInterestQt::declareQml();
    PointOfInterestQtModel::declareQml();
    AppBackendQt::declareQml();
    AppBackendQt appBackend(path, {poi});
    engine.rootContext()->setContextProperty("appBackend", &appBackend);

    engine.load(QUrl(QStringLiteral("qrc:///res/qml/main.qml")));

    return app.exec();
}
