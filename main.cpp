#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>
#include <QObject>
#include <QTreeWidget>
#include <QInputDialog>
#include <QLineEdit>

#include "scenarioManager.h"

int main( int argc, char* argv[] ) {
    QApplication app( argc, argv );

    ScenarioManager manager;

    QMainWindow window;

    // 1
    window.setWindowTitle( "Scenario Manager ");
    window.resize( 1000, 700 );

    // 2
    QWidget *centralWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QTreeWidget *scenarioTree = new QTreeWidget();

    scenarioTree->setColumnCount( 1 );
    scenarioTree->setHeaderLabel( "Scenario" );

    // QTreeWidgetItem *scenarioItem = new QTreeWidgetItem( scenarioTree );

    // Tree Parent ( Root )
    QTreeWidgetItem *scenarioItem = new QTreeWidgetItem( scenarioTree );
    scenarioItem->setText( 0, "Scenario" );

    // Tree Locations Node
    QTreeWidgetItem *locationsItem = new QTreeWidgetItem( scenarioItem );
    locationsItem->setText( 0, "Locations" );

    // Tree Balasore Node
    QTreeWidgetItem *balasoreItem = new QTreeWidgetItem( locationsItem );
    balasoreItem->setText( 0, "Balasore" );

    // Tree Kurnool Node
    QTreeWidgetItem *kurnoolItem = new QTreeWidgetItem( locationsItem );
    kurnoolItem->setText( 0, "Kurnool" );
    
    // Tree Radar ( Parent ) Node
    QTreeWidgetItem *radarsItem = new QTreeWidgetItem( scenarioItem );
    radarsItem->setText( 0, "Radars" );

    // Tree Radar ( Child )Node
    QTreeWidgetItem *radar1 = new QTreeWidgetItem( radarsItem );
    radar1->setText( 0, "Radar-01" );

    // Tree Radar ( Child )Node
    QTreeWidgetItem *radar2 = new QTreeWidgetItem( radarsItem );
    radar2->setText( 0, "Radar-02" );

    // Tree DEW ( Parent ) Node
    QTreeWidgetItem *dewItem = new QTreeWidgetItem( scenarioItem );
    dewItem->setText( 0, "DEW Systems" );

    // Tree DEW ( Child )Node
    QTreeWidgetItem *mark1 = new QTreeWidgetItem( dewItem );
    mark1->setText( 0, "DEW-01" );

    // Tree DEW ( Child )Node
    QTreeWidgetItem *mark2 = new QTreeWidgetItem( dewItem );
    mark2->setText( 0, "DEW-02" );

    // Tree Target ( Parent ) Node
    QTreeWidgetItem *targetItem = new QTreeWidgetItem( scenarioItem );
    targetItem->setText( 0, "Targets" );

    // Tree Target ( Child ) Node
    QTreeWidgetItem *wingLoong = new QTreeWidgetItem( targetItem );
    wingLoong->setText( 0, "Wing Loong" );

    // Tree Target ( Child ) Node
    QTreeWidgetItem *dji = new QTreeWidgetItem( targetItem );
    dji->setText( 0, "DJI Mavic" );

    // Tree layout
    // layout->addLayout( scenarioTree );
    layout->addWidget( scenarioTree );

    // 3
    QPushButton *addLocationButton = new QPushButton( "Add Location" );
    QPushButton *addRadarButton = new QPushButton( "Add Radar" );
    QPushButton *addDewButton = new QPushButton( "Add Dew" );
    QPushButton *addTargetButton = new QPushButton( "Add Target" );

    // 4
    buttonLayout->addWidget( addLocationButton );
    buttonLayout->addWidget( addRadarButton );
    buttonLayout->addWidget( addDewButton );
    buttonLayout->addWidget( addTargetButton );

    // 5
    layout->addLayout( buttonLayout );

    // 6
    centralWidget -> setLayout( layout );

    // 7
    window.setCentralWidget( centralWidget );

    // 10             // Sender
    // QObject::connect( addLocationButton,

    //                   // Signal
    //                   &QPushButton::clicked,

    //                   // Receiver
    //                   &manager,

    //                   // Slot
    //                   &ScenarioManager::addLocation
    // );

    QObject::connect( addRadarButton,
                      &QPushButton::clicked,
                      &manager,
                      &ScenarioManager::addRadar
    );

    QObject::connect( addDewButton, 
                      &QPushButton::clicked,
                      &manager,
                      &ScenarioManager::addDEW
    );

    QObject::connect( addTargetButton,
                      &QPushButton::clicked,
                      &manager,
                      &ScenarioManager::addTarget
    );

    // Add Location
    QObject::connect(
    addLocationButton,
    &QPushButton::clicked,
    [&]()
    {
        bool ok = false;

        QString name =
            QInputDialog::getText(
                &window,
                "Add Location",
                "Location Name : ",
                QLineEdit::Normal,
                "",
                &ok
            );

        if (ok && !name.isEmpty())
        {
            manager.addLocation(name);
        }
    }
);

    // Add Location
    QObject::connect( &manager,
                      &ScenarioManager::locationAdded,

                      // & : capture everything by reference ( now variable)
                      // name : receive signal data
                      [&]( const QString &name )
                      {
                        QTreeWidgetItem *newLocation = 
                        new QTreeWidgetItem( locationsItem );
                        
                        newLocation->setText( 0, name );
                      }
    );

    
    // 8
    window.show();

    // 9
    return app.exec();

}
