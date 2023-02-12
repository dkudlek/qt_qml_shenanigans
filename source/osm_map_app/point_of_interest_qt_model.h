#ifndef QT_QML_SHENANIGANS_POINT_OF_INTEREST_QT_MODEL_H
#define QT_QML_SHENANIGANS_POINT_OF_INTEREST_QT_MODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>

#include "app_backend_qt.h"

class PointOfInterestQtModel: public QAbstractListModel{
    Q_OBJECT
    Q_PROPERTY(AppBackendQt* backend READ getBackend WRITE setBackend NOTIFY backendChanged)

signals:
    void backendChanged();
public:
    enum MyRoles {
        PointOfInterest = Qt::UserRole +1
    };

    PointOfInterestQtModel(){}
    ~PointOfInterestQtModel(){};

    int rowCount(const QModelIndex& parent = QModelIndex()) const override{
        if(parent.isValid()){
            return 0;
        }
        return static_cast<int>(mPois.size());
    }

    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override{
        if(!index.isValid() || index.row() >= mPois.size()){
            return QVariant();
        }
        switch(role){
        case PointOfInterest:
            return QVariant::fromValue(mPois.at(index.row()).get());
            break;
        }
        return QVariant();
    }
    QHash<int, QByteArray> roleNames() const override{
        QHash<int, QByteArray> names;
        names[PointOfInterest]= "poi";
        return names;
    }

    AppBackendQt* getBackend() const{
        return mBackend;
    }

    void setBackend(AppBackendQt* backend){
        mBackend = backend;
        emit backendChanged();
        if(mBackend){
            update();
        }
    }

    Q_INVOKABLE void update(){
        if(mBackend){
            const auto pois = mBackend->getPois();
            beginResetModel();
            mPois = pois;
            endResetModel();
        }
    }

    static void declareQml(){
        qmlRegisterType<PointOfInterestQtModel>("Tracker", 1, 0, "PointOfInterestModel");
    }
private:
    AppBackendQt* mBackend;
    std::vector<std::shared_ptr<PointOfInterestQt>> mPois;

};

#endif // QT_QML_SHENANIGANS_POINT_OF_INTEREST_QT_MODEL_H
