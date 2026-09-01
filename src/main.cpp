#include <QApplication>
#include <QMainWindow>

#include "scenarioManager.h"

int main( int argc, char *argv[] ) {

    QApplication app( argc, argv );

    QMainWindow window;
    window.setWindowTitle( "Scenario Manager" );
    window.resize( 1000, 700 );

    ScenarioManager *manager = new ScenarioManager( &window );
    window.setCentralWidget( manager );

    // Show Window
    window.show();

    return app.exec();
}
