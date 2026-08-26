#ifndef SCENARIOMANAGER_H
#define SCENARIOMANAGER_H

#include <QObject>

class ScenarioManager : public QObject {

    Q_OBJECT

    public :
        // Constructor
        explicit ScenarioManager( QObject *parent = nullptr );

    public slots : 
        void addLocation( const QString &name );
        void addRadar( const QString &name );
        void addDEW( const QString &name );
        void addTarget( const QString &name );

    signals :
        void locationAdded( const QString &name );
        void radarAdded( const QString &name );
        void dewAdded( const QString &name );
        void targetAdded( const QString &name );
};

#endif 