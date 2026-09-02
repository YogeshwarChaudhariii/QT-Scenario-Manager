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

#include <QPixmap>

class ScenarioManager : 
public QWidget {

    Q_OBJECT

    public :
        // Constructor
        explicit ScenarioManager( QWidget *parent = nullptr );

    public slots : 
        void addLocation( const QString &name, const QString &imagePath = "" );
        void addRadar( const QString &name );
        void addDEW( const QString &name );
        void addTarget( const QString &name );

        void deleteSelectedItem();
        void saveScenarioToJson();
        void importImageForSelected();

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

        void displayImage( const QString &imagePath );

    private :       // UI objects as member
        QTreeWidget *scenarioTree = nullptr;
        QTreeWidgetItem *locationsItem = nullptr;
        QTreeWidgetItem *radarsItem = nullptr;
        QTreeWidgetItem *dewItem = nullptr;
        QTreeWidgetItem *targetItem = nullptr;
        
        QWidget *propertyWidget = nullptr;
        QLabel *nameValue = nullptr;
        QLabel *typeValue = nullptr;
        QLabel *imageValue = nullptr;

        QPushButton *addLocationButton = nullptr;
        QPushButton *addRadarButton = nullptr;
        QPushButton *addDewButton = nullptr;
        QPushButton *addTargetButton = nullptr;
        QPushButton *deleteButton = nullptr;
        QPushButton *saveButton = nullptr;
        QPushButton *importImageButton = nullptr;
        
        QHBoxLayout *buttonLayout = nullptr;
        QSplitter *splitter = nullptr;

};

#endif      // SCENARIOMANAGER_H