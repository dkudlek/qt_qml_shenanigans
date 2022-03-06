//
// Created by dkudlek on 2/20/22.
//

#ifndef QT_QML_SHENANIGANS_ELEMENT_BACKEND_QT_H
#define QT_QML_SHENANIGANS_ELEMENT_BACKEND_QT_H

#include <memory>
#include <vector>

#include <QObject>
#include <QQmlEngine>
#include <QList>

#include "element_qt.h"

class ElementBackendQt : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<QObject *> elements READ getElements NOTIFY elementsChanged)
signals:

    void elementsChanged();

public:
    ElementBackendQt();

    ~ElementBackendQt() {};

    static void declareQml();

    QList<QObject *> getElements() const;

private:
    std::vector<std::unique_ptr<ElementQt>> mElements;
};


#endif //QT_QML_SHENANIGANS_ELEMENT_BACKEND_QT_H
