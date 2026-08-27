#pragma once

#include <QMainWindow>
#include "core/scenarioManager.h"

class QTreeWidget;
class QTreeWidgetItem;
class QLabel;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onAddLocationClicked();
    void onLocationAdded(const QString &name);
    void onTreeItemClicked(QTreeWidgetItem *item, int column);

private:
    void setupUi();
    void setupConnections();
    void populateInitialTree();

    // Domain / Logic
    ScenarioManager m_manager;

    // UI Widgets
    QTreeWidget *m_scenarioTree{nullptr};
    QTreeWidgetItem *m_locationsItem{nullptr};
    QTreeWidgetItem *m_radarsItem{nullptr};
    QTreeWidgetItem *m_dewItem{nullptr};
    QTreeWidgetItem *m_targetsItem{nullptr};

    QLabel *m_nameValue{nullptr};
    QLabel *m_typeValue{nullptr};

    QPushButton *m_addLocationButton{nullptr};
    QPushButton *m_addRadarButton{nullptr};
    QPushButton *m_addDewButton{nullptr};
    QPushButton *m_addTargetButton{nullptr};
};