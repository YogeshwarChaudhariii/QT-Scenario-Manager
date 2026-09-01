#ifndef SCENARIOMANAGER_H
#define SCENARIOMANAGER_H

#include <QObject>
#include <QString> 

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

#include <QLabel>
#include <QSplitter>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ScenarioManager : 
public QWidget {

    Q_OBJECT

    public :
        // Constructor
        explicit ScenarioManager( QWidget *parent = nullptr );

    public slots : 
        void addLocation( const QString &name );
        void addRadar( const QString &name );
        void addDEW( const QString &name );
        void addTarget( const QString &name );

        void deleteSelectedItem();
        void saveScenarioToJson();

    signals :
        void locationAdded( const QString &name );
        // void radarAdded( const QString &name );
        // void dewAdded( const QString &name );
        // void targetAdded( const QString &name );

    private :
        void createTree();
        void createPropertyPanel();
        void createButtons();
        void createLayout();
        void setupConnections();

    private :       // UI objects as member
        QTreeWidget *scenarioTree = nullptr;
        QTreeWidgetItem *locationsItem = nullptr;
        QTreeWidgetItem *radarsItem = nullptr;
        QTreeWidgetItem *dewItem = nullptr;
        QTreeWidgetItem *targetItem = nullptr;
        
        QWidget *propertyWidget = nullptr;
        QLabel *nameValue = nullptr;
        QLabel *typeValue = nullptr;

        QPushButton *addLocationButton = nullptr;
        QPushButton *addRadarButton = nullptr;
        QPushButton *addDewButton = nullptr;
        QPushButton *addTargetButton = nullptr;
        QPushButton *deleteButton = nullptr;
        QPushButton *saveButton = nullptr;
        
        QHBoxLayout *buttonLayout = nullptr;
        QSplitter *splitter = nullptr;

};

#endif      // SCENARIOMANAGER_H