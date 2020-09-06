#include "HierarchyElement.h"
#include "iostream"
#include <qnamespace.h>

HierarchyElement::HierarchyElement(HierarchyElement* parent,bool togglable):parent(parent),
        modifying(false){

    treeItem = parent->addItem();
    parent->addChild(this);

    if(togglable){
        treeItem->setCheckState(modify,Qt::Unchecked);
    }

    connect(treeItem->treeWidget(),&QTreeWidget::currentItemChanged,this,&HierarchyElement::clicked);
    connect(treeItem->treeWidget(),&QTreeWidget::itemChanged,this,&HierarchyElement::toggled);

    setVisible(true,true);

}

HierarchyElement::HierarchyElement(QTreeWidget* master):modifying(false){

    treeItem = new QTreeWidgetItem(master);
    connect(master,&QTreeWidget::currentItemChanged,this,&HierarchyElement::clicked);
    connect(master,&QTreeWidget::itemChanged,this,&HierarchyElement::toggled);
    setVisible(true,true);
}

HierarchyElement::~HierarchyElement(){
    delete treeItem;
}

void HierarchyElement::addChild(HierarchyElement* child){
    children.push_back(child);
}

void HierarchyElement::changeStatus(bool active, bool recursively){

    this->active = active;

    if(active){widget.show();}
    else{widget.hide();}

    if(parent != nullptr && active){parent->changeStatus(true,true);};

    onActivation(active,recursively);
}

void HierarchyElement::simulateClicked(){

    treeItem->treeWidget()->setCurrentItem(treeItem);
}

void HierarchyElement::clicked(QTreeWidgetItem* item, QTreeWidgetItem* prev){

    if(item == treeItem){
        changeStatus(true);
    }else{
        changeStatus(false);
    }
}

void HierarchyElement::toggled(QTreeWidgetItem* item, int col){

    if(item == treeItem){
        if (col == visibleCol){
            setVisible(!visible,false);
            return;
        }else if(col == modify){
            setModifying(!modifying,false);
        }
    }
}

void HierarchyElement::setModifying(bool on, bool changeBox){

    if(changeBox){
        treeItem->setCheckState(modify,on ? Qt::Checked : Qt::Unchecked);
    }else{
        this->modifying = on;
    }
    if(on){
        //for(QTreeWidgetItem* item: treeItem->treeWidget()->children)
    }
    onModifyingChange(modifying);
    //std::cout << on << std::endl;
}

void HierarchyElement::setVisible(bool visible, bool changeBox){

    if(changeBox){treeItem->setCheckState(visibleCol,visible ? Qt::Checked : Qt::Unchecked);}
    this->visible = visible;
    for(HierarchyElement* child: children){
        child->setVisible(visible,true);
    }
    onVisible(visible);
}

void HierarchyElement::setColor(QColor& color){

    treeItem->setForeground(itemCol,color);
}

void HierarchyElement::setBold(bool bold){

    QFont font = treeItem->font(itemCol);
    font.setWeight(QFont::Bold);
    treeItem->setFont(itemCol,font);
}
