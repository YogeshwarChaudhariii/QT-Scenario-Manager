#include "MainWindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSplitter>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QInputDialog>
#include <QLineEdit>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUi();
    populateInitialTree();
    setupConnections();
}

void MainWindow::setupUi() {
    setWindowTitle("Scenario Manager");
    resize(1000, 700);

    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(centralWidget);

    // 1. Left side: Scenario Tree
    m_scenarioTree = new QTreeWidget(this);
    m_scenarioTree->setColumnCount(1);
    m_scenarioTree->setHeaderLabel("Scenario");

    // 2. Right side: Property Panel
    auto *propertyWidget = new QWidget(this);
    auto *propertyLayout = new QFormLayout(propertyWidget);

    m_nameValue = new QLabel("_", propertyWidget);
    m_typeValue = new QLabel("_", propertyWidget);

    propertyLayout->addRow("Name : ", m_nameValue);
    propertyLayout->addRow("Type : ", m_typeValue);
    propertyWidget->setLayout(propertyLayout);

    // 3. Central Splitter
    auto *splitter = new QSplitter(this);
    splitter->addWidget(m_scenarioTree);
    splitter->addWidget(propertyWidget);
    mainLayout->addWidget(splitter);

    // 4. Bottom Buttons
    auto *buttonLayout = new QHBoxLayout();
    m_addLocationButton = new QPushButton("Add Location", this);
    m_addRadarButton = new QPushButton("Add Radar", this);
    m_addDewButton = new QPushButton("Add Dew", this);
    m_addTargetButton = new QPushButton("Add Target", this);

    buttonLayout->addWidget(m_addLocationButton);
    buttonLayout->addWidget(m_addRadarButton);
    buttonLayout->addWidget(m_addDewButton);
    buttonLayout->addWidget(m_addTargetButton);

    mainLayout->addLayout(buttonLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::populateInitialTree() {
    // Root Node
    auto *scenarioItem = new QTreeWidgetItem(m_scenarioTree);
    scenarioItem->setText(0, "Scenario");

    // Locations
    m_locationsItem = new QTreeWidgetItem(scenarioItem);
    m_locationsItem->setText(0, "Locations");

    auto *balasoreItem = new QTreeWidgetItem(m_locationsItem);
    balasoreItem->setText(0, "Balasore");

    auto *kurnoolItem = new QTreeWidgetItem(m_locationsItem);
    kurnoolItem->setText(0, "Kurnool");

    // Radars
    m_radarsItem = new QTreeWidgetItem(scenarioItem);
    m_radarsItem->setText(0, "Radars");

    auto *radar1 = new QTreeWidgetItem(m_radarsItem);
    radar1->setText(0, "Radar-01");

    auto *radar2 = new QTreeWidgetItem(m_radarsItem);
    radar2->setText(0, "Radar-02");

    // DEW Systems
    m_dewItem = new QTreeWidgetItem(scenarioItem);
    m_dewItem->setText(0, "DEW Systems");

    auto *mark1 = new QTreeWidgetItem(m_dewItem);
    mark1->setText(0, "DEW-01");

    auto *mark2 = new QTreeWidgetItem(m_dewItem);
    mark2->setText(0, "DEW-02");

    // Targets
    m_targetsItem = new QTreeWidgetItem(scenarioItem);
    m_targetsItem->setText(0, "Targets");

    auto *wingLoong = new QTreeWidgetItem(m_targetsItem);
    wingLoong->setText(0, "Wing Loong");

    auto *dji = new QTreeWidgetItem(m_targetsItem);
    dji->setText(0, "DJI Mavic");

    scenarioItem->setExpanded(true);
}

void MainWindow::setupConnections() {
    // Button clicks -> ScenarioManager actions
    connect(m_addLocationButton, &QPushButton::clicked, this, &MainWindow::onAddLocationClicked);
    connect(m_addRadarButton, &QPushButton::clicked, &m_manager, &ScenarioManager::addRadar);
    connect(m_addDewButton, &QPushButton::clicked, &m_manager, &ScenarioManager::addDEW);
    connect(m_addTargetButton, &QPushButton::clicked, &m_manager, &ScenarioManager::addTarget);

    // ScenarioManager signals -> UI updates
    connect(&m_manager, &ScenarioManager::locationAdded, this, &MainWindow::onLocationAdded);

    // Tree item selection -> Property panel updates & logging
    connect(m_scenarioTree, &QTreeWidget::itemClicked, this, &MainWindow::onTreeItemClicked);
}

void MainWindow::onAddLocationClicked() {
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
        m_manager.addLocation(name.trimmed());
    }
}

void MainWindow::onLocationAdded(const QString &name) {
    auto *newLocation = new QTreeWidgetItem(m_locationsItem);
    newLocation->setText(0, name);
    m_locationsItem->setExpanded(true);
}

void MainWindow::onTreeItemClicked(QTreeWidgetItem *item, int column) {
    Q_UNUSED(column);
    if (!item) return;

    QString name = item->text(0);
    QString type = "Unknown";

    std::cout << "Clicked : " << name.toStdString() << "\n";

    if (item->parent() != nullptr) {
        std::cout << "Parent : " << item->parent()->text(0).toStdString() << "\n";
        type = item->parent()->text(0);

        if (type == "Locations") {
            type = "Location";
        }
    }

    m_nameValue->setText(name);
    m_typeValue->setText(type);
}