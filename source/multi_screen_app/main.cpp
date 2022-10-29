#include <iostream>
#include <string>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "argparse.hpp"

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("multi_screen_app");
    program.add_argument("--first-window-position").default_value(1).help(
            "Indicates the display where the app shows the window");
    program.add_argument("--first-window-size").default_value(std::string("windowed")).help("window size: windowed, fullscreen");
    program.add_argument("--second-window-position").default_value(2).help(
            "Indicates the display where the app shows the window");
    program.add_argument("--second-window-size").default_value(std::string("windowed")).help("window size: windowed, fullscreen");
    program.add_argument("--third-window-position").default_value(3).help(
            "Indicates the display where the app shows the window");
    program.add_argument("--third-window-size").default_value(std::string("windowed")).help("window size: windowed, fullscreen");
    program.add_argument("--help", "-h");

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }
    auto firstWindowPosition = program.get<int>("first-window-position");
    auto firstWindowSize = program.get<std::string>("first-window-size");
    auto secondWindowPosition = program.get<int>("second-window-position");
    auto secondWindowSize = program.get<std::string>("second-window-size");
    auto thirdWindowPosition = program.get<int>("third-window-position");
    auto thirdWindowSize = program.get<std::string>("third-window-size");



    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("appFirstWindowDisplayId", firstWindowPosition);
    engine.rootContext()->setContextProperty("appFirstWindowDisplaySize", QString::fromStdString(firstWindowSize));
    engine.rootContext()->setContextProperty("appSecondWindowDisplayId", secondWindowPosition);
    engine.rootContext()->setContextProperty("appSecondWindowDisplaySize", QString::fromStdString(secondWindowSize));
    engine.rootContext()->setContextProperty("appThirdWindowDisplayId", thirdWindowPosition);
    engine.rootContext()->setContextProperty("appThirdWindowDisplaySize", QString::fromStdString(thirdWindowSize));
    engine.load(QUrl(QStringLiteral("qrc:///res/qml/main.qml")));
    return app.exec();
}