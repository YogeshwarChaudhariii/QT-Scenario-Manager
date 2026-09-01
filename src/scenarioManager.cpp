#include "scenarioManager.h"

#include <iostream>

#include <QInputDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>

ScenarioManager::
ScenarioManager(QWidget *parent)
    : QWidget(parent) {
    createTree();
    createPropertyPanel();
    createButtons();

    createLayout();

    setupConnections();
}

void ScenarioManager::createTree() {
    scenarioTree = new QTreeWidget( this );
    scenarioTree->setColumnCount( 1 );
    scenarioTree->setHeaderLabel( "Scenario" );

    // Root Node
    QTreeWidgetItem *scenarioItem = new QTreeWidgetItem( scenarioTree );
    scenarioItem->setText( 0, "Scenario" );

    // Locations
    locationsItem = new QTreeWidgetItem( scenarioItem );
    locationsItem->setText( 0, "Locations" );

    QTreeWidgetItem *balasoreItem = new QTreeWidgetItem(locationsItem);
    balasoreItem->setText(0, "Balasore");

    QTreeWidgetItem *hyderabadItem = new QTreeWidgetItem(locationsItem);
    hyderabadItem->setText(0, "Hyderabad");

    QTreeWidgetItem *kurnoolItem = new QTreeWidgetItem(locationsItem);
    kurnoolItem->setText(0, "Kurnool");

    // Radars
    radarsItem = new QTreeWidgetItem(scenarioItem);
    radarsItem->setText(0, "Radars");

    QTreeWidgetItem *radar1 = new QTreeWidgetItem(radarsItem);
    radar1->setText(0, "Radar-01");

    QTreeWidgetItem *radar2 = new QTreeWidgetItem(radarsItem);
    radar2->setText(0, "Radar-02");

    // DEW Systems
    dewItem = new QTreeWidgetItem(scenarioItem);
    dewItem->setText(0, "DEW Systems");

    QTreeWidgetItem *mark1 = new QTreeWidgetItem(dewItem);
    mark1->setText(0, "DEW-01");

    QTreeWidgetItem *mark2 = new QTreeWidgetItem(dewItem);
    mark2->setText(0, "DEW-02");

    // Targets
    targetItem = new QTreeWidgetItem(scenarioItem);
    targetItem->setText(0, "Targets");

    QTreeWidgetItem *wingLoong = new QTreeWidgetItem(targetItem);
    wingLoong->setText(0, "Wing Loong");

    QTreeWidgetItem *dji = new QTreeWidgetItem(targetItem);
    dji->setText(0, "DJI Mavic");

    scenarioTree->expandAll();
}

void ScenarioManager::createPropertyPanel() {
    propertyWidget = new QWidget(this);
    QFormLayout *propertyLayout = new QFormLayout( propertyWidget );

    nameValue = new QLabel("-", propertyWidget);
    typeValue = new QLabel("-", propertyWidget);

    propertyLayout->addRow("Name : ", nameValue);
    propertyLayout->addRow("Type : ", typeValue);
}

void ScenarioManager::createButtons() {
    buttonLayout = new QHBoxLayout();

    addLocationButton = new QPushButton( "Add Location", this );
    addRadarButton    = new QPushButton( "Add Radar", this );
    addDewButton      = new QPushButton( "Add Dew", this );
    addTargetButton   = new QPushButton( "Add Target", this );
    deleteButton      = new QPushButton( "Delete Selected", this );
    saveButton        = new QPushButton ( "Save Scenario", this );

    buttonLayout->addWidget(addLocationButton);
    buttonLayout->addWidget(addRadarButton);
    buttonLayout->addWidget(addDewButton);
    buttonLayout->addWidget(addTargetButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(saveButton);
}

void ScenarioManager::createLayout() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(scenarioTree);
    splitter->addWidget(propertyWidget);

    mainLayout->addWidget(splitter);
    mainLayout->addLayout(buttonLayout);
}

void ScenarioManager::setupConnections() {

    // Add Location Button
    connect(addLocationButton, &QPushButton::
        clicked, this, 
        [ this ]() {
        bool ok = false;
        QString name = QInputDialog::getText(
            this,
            "Add Location",
            "Location Name : ",
            QLineEdit::Normal,
            "",
            &ok
        );

        if (ok && !name.trimmed().isEmpty()) {
            addLocation(name.trimmed());
        }
    });

    // Add Radar 
    connect(addRadarButton, &QPushButton::
        clicked, this,
        [this]() {
            bool ok = false;

            // Show the pop up window asking for name
            QString name = QInputDialog::getText(
                this,
                "Add Radar",
                "Radar Name : ",
                QLineEdit::Normal,
                "",
                &ok
            );

            if ( ok && !name.trimmed().isEmpty() ) {
                addRadar( name.trimmed() );
            } 
    });

    // Add DEW
    connect( addDewButton, &QPushButton::
        clicked, this,
        [ this ]() {
            bool ok = false;
            QString name = QInputDialog::getText(
                this,
                "Add DEW",
                "DEW Name : ",
                QLineEdit::Normal,
                "",
                &ok
            );
            if ( ok && !name.trimmed().isEmpty() )
            {
                addDEW( name.trimmed() );
            }
                
    });

    // Add Target
    connect( addTargetButton, &QPushButton::
        clicked, this,
        [ this ]() {
        bool ok = false;
        QString name = QInputDialog::getText(
            this,
            "Add Target",
            "Target Name : ",
            QLineEdit::Normal,
            "",
            &ok
        );

        if ( ok && !name.trimmed().isEmpty() )
        {
            addTarget( name.trimmed() );
        }
    });

    // Tree Item Clicked -> Update Property Panel
    connect(scenarioTree, &QTreeWidget::
        itemClicked, this, 
        [this]( QTreeWidgetItem *item, int /*column*/ ) {

        if ( !item || !nameValue || !typeValue ) return;

        QString name = item->text(0);
        QString type = "Root";

        if ( item->parent() != nullptr ) {
            type = item->parent()->text(0);

            if (type == "Locations") {
                type = "Location";
            } else if (type == "Radars") {
                type = "Radar";
            } else if (type == "DEW Systems") {
                type = "DEW System";
            } else if (type == "Targets") {
                type = "Target";
            }
        }

        nameValue->setText(name);
        typeValue->setText(type);
    });

    // Delete Button Connection
    connect( deleteButton, &QPushButton::
        clicked, this,
        &ScenarioManager::deleteSelectedItem );

    // Save Button -> Triggered the save button
    connect( saveButton, &QPushButton::
        clicked, this,
        &ScenarioManager::saveScenarioToJson );
}

void ScenarioManager::
addLocation(const QString &name) {

    QTreeWidgetItem *newLocation = new QTreeWidgetItem( locationsItem );
    newLocation->setText( 0, name );

    locationsItem->setExpanded( true );
    
    std::cout << "Location Added : " << name.toStdString() << "\n";
    emit locationAdded(name);
}

void ScenarioManager::
addRadar( const QString &name ) {

    // Make a new branch and attach it to 'radarsItem'
    QTreeWidgetItem *newRadar = new QTreeWidgetItem( radarsItem );
    newRadar->setText( 0, name );

    // Expand the folder so the user immediately sees the new item
    radarsItem->setExpanded( true );
    std::cout << "Radar Added\n";
}

void ScenarioManager::
addDEW( const QString &name ) {

    QTreeWidgetItem *newDEW = new QTreeWidgetItem( dewItem );
    newDEW->setText( 0, name );

    dewItem->setExpanded( true );
    std::cout << "DEW Added\n";
}

void ScenarioManager::
addTarget( const QString &name ) {

    QTreeWidgetItem *newTarget = new QTreeWidgetItem( targetItem );
    newTarget->setText( 0, name );

    targetItem->setExpanded( true );
    std::cout << "Target Added\n";
}

void ScenarioManager::
godView() {
    // QImage balasoreImage;

}

void ScenarioManager::
deleteSelectedItem() {
    
    // Get the currently highlighted item
    QTreeWidgetItem *selectedItem = scenarioTree->currentItem();
    
    if ( selectedItem == nullptr ) {
        return;
    }

    if ( selectedItem->parent() == nullptr ||
         selectedItem == locationsItem ||
         selectedItem == radarsItem ||
         selectedItem == dewItem ||
         selectedItem == targetItem ) {

            QMessageBox::warning(
                this,
                "Cannot Delete",
                "Root scenario and category folders cannot be deleted."
            );

        std::cout << "Cannot delete root or category folders\n";
        return;
    }

    // Ask user for confirmation
    QString itemName = selectedItem->text( 0 );
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Deletion",
        "Are you sure you want to delete \"" + itemName + "\"?",
        QMessageBox::Yes | QMessageBox::No
    );

    // If the user clicked anything other than "Yes", stop here
    if ( reply != QMessageBox::Yes ) {
        return;
    }

    // Get parent folder
    QTreeWidgetItem *parent = selectedItem->parent();

    // Unhook child and delete its memory
    parent->removeChild( selectedItem );
    delete selectedItem;

    // Resets the property panel to blank
    nameValue->setText("_");
    typeValue->setText("_");
}

// Helper Function : collects all children under a folder into a QJsonArray
static QJsonArray extractItemsFromFolder( QTreeWidgetItem *folder ) {
    QJsonArray array;

    if ( !folder ) {
        return array;
    }

    // Loop through all folders under ths items
    for ( int i = 0; i < folder->childCount(); ++i ) {
        QTreeWidgetItem *child = folder->child( i );
        array.append( child->text( 0 ) ); // add item name to our list
    }
    return array;
}

void ScenarioManager::
saveScenarioToJson() {

    QJsonObject rootObject;

    rootObject[ "Locations" ] = 
        extractItemsFromFolder( locationsItem );

    rootObject[ "Radars" ] = 
        extractItemsFromFolder( radarsItem );
    
    rootObject[ "DEW Systems" ] = 
        extractItemsFromFolder( dewItem );

    rootObject[ "Targets" ] = 
        extractItemsFromFolder( targetItem );

    // Wrap into a QJsonDocument so it can format into text
    QJsonDocument doc( rootObject );

    // Ask user where to save file
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Save Scenario",
        "scenario.json",
        "JSON Files (*.json)"
    );

    // If user clicked cancel
    if ( filePath.isEmpty() ) {
        return;
    }

    if ( !filePath.endsWith(".json", Qt::CaseInsensitive )) {
        filePath += ".json";
    }

    // Open the file and write the text
    QFile file( filePath );

    if (!file.open( QIODevice::WriteOnly | QIODevice::Text )) {
        QMessageBox::critical(this, "Error", "Could not open file" + 
                        file.errorString());
        return;
    }

    file.write( doc.toJson( QJsonDocument::Indented ));
    file.close();

    QMessageBox::information( this, "Success", "Scenario save successfully...");
}

