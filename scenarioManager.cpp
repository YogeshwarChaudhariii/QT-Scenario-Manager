#include "scenarioManager.h"

#include <iostream>
#include <QString>



ScenarioManager::ScenarioManager( QObject *parent )
                : QObject( parent ) {}



void ScenarioManager::addLocation( const QString &name ) {
    // QString name = "Pune";

    std::cout << "Location Added : "
              << name.toStdString() 
              <<"\n";

    emit locationAdded( name );
}

void ScenarioManager::addRadar() {
    std::cout << "Radar Added\n";
}

void ScenarioManager::addDEW() {
    std::cout << "DEW Added\n";
}

void ScenarioManager::addTarget() {
    std::cout << "Target Added\n";
}