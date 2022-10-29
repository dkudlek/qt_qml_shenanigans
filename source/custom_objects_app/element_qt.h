//
// Created by dkudlek on 2/20/22.
//

#ifndef QT_QML_SHENANIGANS_ELEMENT_QT_H
#define QT_QML_SHENANIGANS_ELEMENT_QT_H

#include <QObject>
#include <QQmlEngine>
#include <QString>

class ElementQt : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString displayName READ getDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(float velocity READ getVelocity NOTIFY velocityChanged)

signals:

    void displayNameChanged();

    void velocityChanged();

public:
    ElementQt();
    ElementQt(QString displayName, float velocity);

    static void declareQml() {
        qmlRegisterType<ElementQt>("com.goliath-sw.test", 1, 0, "Element");
    }

    QString getDisplayName() const;

    float getVelocity() const;

private:
    QString mDisplayName = "DefaultItem";
    float mVelocity = 0.0f;
};


#endif //QT_QML_SHENANIGANS_ELEMENT_QT_H
