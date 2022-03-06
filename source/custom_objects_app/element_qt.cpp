//
// Created by dkudlek on 2/20/22.
//

#include "element_qt.h"

ElementQt::ElementQt() {};

ElementQt::ElementQt(QString displayName, float velocity) {
    mDisplayName = displayName;
    mVelocity = velocity;

}

QString ElementQt::getDisplayName() const {
    return mDisplayName;
}

float ElementQt::getVelocity() const {
    return mVelocity;
}


