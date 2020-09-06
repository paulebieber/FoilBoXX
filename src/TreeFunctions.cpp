
#include "TreeFunctions.h"

void setBold(QTreeWidgetItem* item, bool bold){

    QFont font = item->font(0);
    font.setWeight(QFont::Bold);
    item->setFont(0,font);
}
