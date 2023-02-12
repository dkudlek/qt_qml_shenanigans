#ifndef QT_QML_SHENANIGANS_APP_BACKEND_H
#define QT_QML_SHENANIGANS_APP_BACKEND_H

#include <memory>
#include <atomic>
#include <shared_mutex>
#include <mutex>
#include <thread>

#include <QObject>
#include <QDebug>
#include <QQmlEngine>
#include <QGeoPath>
#include <QGeoCoordinate>
#include <vector>

#include "point_of_interest_qt.h"

class AppBackendQt: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoPath path READ getPath NOTIFY pathChanged)
    Q_PROPERTY(QGeoCoordinate coordinate READ getCoordinate NOTIFY coordinateChanged)
    Q_PROPERTY(int updateInterval READ getSleepTime NOTIFY sleepTimeChanged)

signals:
    void pathChanged();
    void coordinateChanged();
    void sleepTimeChanged();

public:
    AppBackendQt(QGeoPath path= QGeoPath(), std::vector<std::shared_ptr<PointOfInterestQt>> pois= {}): mPath(path), mPois(pois) {

        if(mPath.isValid()){
            mRunner = std::thread(std::bind(&AppBackendQt::run, this));
        }

    }
    virtual ~AppBackendQt() {
        mIsAlive.store(false);
        if(mRunner.joinable()){
            mRunner.join();
        }

    }

    Q_INVOKABLE void faster(){
        {
            const auto lock = std::unique_lock<std::shared_mutex>(mDataMutex);
            mSleepTime = std::max(20, mSleepTime / 2);

        }
        emit sleepTimeChanged();

    }

    Q_INVOKABLE void slower(){
        {
            const auto lock = std::unique_lock<std::shared_mutex>(mDataMutex);
            mSleepTime = std::min(1000, mSleepTime * 2);

        }
        emit sleepTimeChanged();
    }

    static void declareQml(){
        qmlRegisterType<AppBackendQt>("Tracker", 1, 0, "AppBackend");
    }

    Q_INVOKABLE void update(){
        emit pathChanged();
    }

    QGeoCoordinate getCoordinate() const{
        const auto lock = std::unique_lock<std::shared_mutex>(mDataMutex);
        return mCoordinate;
    }

    QGeoPath getPath() const{
        return mPath;
    }

    std::vector<std::shared_ptr<PointOfInterestQt>> getPois() const{
        return mPois;
    }

    int getSleepTime() const {
        const auto lock = std::unique_lock<std::shared_mutex>(mDataMutex);
        return mSleepTime;
    }

private:
    mutable std::shared_mutex mDataMutex;
    std::atomic<bool> mIsAlive;
    std::thread mRunner;
    QGeoPath mPath;
    QGeoCoordinate mCoordinate;
    std::vector<std::shared_ptr<PointOfInterestQt>> mPois;
    int mSleepTime = 1000; // ms

    void run(){
        mIsAlive.store(true);
        auto idx = 0;
        const auto path = mPath.path();
        while(mIsAlive.load()){
            {
                const auto lock = std::unique_lock<std::shared_mutex>(mDataMutex);
                mCoordinate = path[idx];
                idx = (idx + 1) % path.size();

            }
            emit coordinateChanged();
            std::this_thread::sleep_for(std::chrono::milliseconds(getSleepTime()));
        }
    }
};


#endif // QT_QML_SHENANIGANS_APP_BACKEND_H
