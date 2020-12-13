#pragma once

#include <QObject>
#include <QTreeWidgetItem>

class HierarchyElement: public QObject{

Q_OBJECT

    void clicked(QTreeWidgetItem* item, QTreeWidgetItem* prev);
    void toggled(QTreeWidgetItem* item, int col);
    void changeStatus(bool active, bool recursively = false);

    enum columns{itemCol, modify ,visibleCol};

    std::vector<HierarchyElement*> children{};

    bool visible;

public:
    HierarchyElement(QTreeWidget* master);
    HierarchyElement(HierarchyElement* parent,bool togglable=false);
    ~HierarchyElement();
    
    void simulateClicked();
    void setModifying(bool on, bool changeBox);
    QTreeWidgetItem* addItem(){return new QTreeWidgetItem(treeItem);};
    void addChild(HierarchyElement* child);
    QWidget* getWidget(){return &widget;}
    HierarchyElement* getParent(){return parent;}
    QTreeWidgetItem* getTreeItem(){return treeItem;}

protected:
    QTreeWidgetItem* treeItem = new QTreeWidgetItem();
    HierarchyElement* parent = nullptr;
    QWidget widget;

    bool modifying;
    bool active;

    void setVisible(bool visible, bool changeBox);
    void setBold(bool bold);
    void setColor(QColor& color);
    virtual void onActivation(bool active, bool recursively = false){};
    virtual void onVisible(bool visible){};
    virtual void onModifyingChange(bool modifying){};
};
