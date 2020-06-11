//
// Created by Jack on 15/12/30.
//

#include "Item.h"

Item::Item() {

}

Item::~Item() {
    for (int j = 0; j < mLstPic.size(); j++) {
        delete mLstPic[j];
    }
    mLstPic.clear();
}


string Item::getItemIvId(string itemName, int dataIndex) {
    return getItemId("iv", itemName, dataIndex, string());
}

string Item::getItemTvId(string itemName, int dataIndex) {
    return getItemId("tv", itemName, dataIndex, string());
}

string Item::getItemIvId(string itemName, int dataIndex, string description){
    return getItemId("iv", itemName, dataIndex, description);
}
string Item::getItemIvId(string itemName) {
    return getItemId("iv", itemName, -1, string());
}

string Item::getItemTvId(string itemName) {
    return getItemId("tv", itemName, -1, string());
}

string Item::getItemStageId(string itemName) {
    return getItemId("stage", itemName, -1, string());
}

string Item::getItemId(string itemType, string itemName, int dataIndex, string description) {
    char ptChar[128];
    if (dataIndex == -1) {
        sprintf(ptChar, "%s_%s_{%s}", itemType.c_str(), itemName.c_str(), description.c_str());
    } else {
        sprintf(ptChar, "%s[%d]_%s_{%s}", itemType.c_str(), dataIndex, itemName.c_str(), description.c_str());
    }
    return string(ptChar);
}