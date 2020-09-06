#include "Dock.h"

Dock::Dock(QWidget* child, QString name, QWidget* parent): QDockWidget(parent){

    setWidget(child);
    child->show();
    setWindowTitle(name);

    setFeatures(features() & ~QDockWidget::DockWidgetClosable);
    setFeatures(features() & ~QDockWidget::DockWidgetFloatable);
}
