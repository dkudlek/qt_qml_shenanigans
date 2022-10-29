//
// Created by dkudlek on 2/20/22.
//

#include "element_backend_qt.h"

#include <memory>

QList<QObject *> ElementBackendQt::getElements() const {
    QList<QObject *> elements;
    for (auto &element: mElements) {
        elements.append(element.get());
    }
    return elements;
}

ElementBackendQt::ElementBackendQt() {
    mElements.push_back(std::make_unique<ElementQt>("No. 1", 10.0f));
    mElements.push_back(std::make_unique<ElementQt>("No. 2", 12.0f));
    mElements.push_back(std::make_unique<ElementQt>("No. 3", 13.0f));
    emit elementsChanged();
}

void ElementBackendQt::declareQml() {
    qmlRegisterType<ElementBackendQt>("com.goliath-sw.test", 1, 0, "ElementBackend");

}
