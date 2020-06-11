//
// Created by Jack on 15/12/30.
//

#ifndef ANDROIDDEMO_ITEM_H
#define ANDROIDDEMO_ITEM_H

#include <deque>
#include "../picLoader/Pic.h"

using std::deque;
using std::string;

class Item {
public:
    Item();

    ~Item();

    deque<Pic *> mLstPic;

    static string getItemIvId(string itemName, int dataIndex);

    static string getItemIvId(string itemName);

    static string getItemIvId(string itemName, int dataIndex, string description);

    static string getItemTvId(string itemName, int dataIndex);

    static string getItemTvId(string itemName);

    static string getItemStageId(string itemName);

    static string buildDescription(string description, string key, string value);

private:
    static string getItemId(string itemType, string itemName, int dataIndex, string content);
};


#endif //ANDROIDDEMO_ITEM_H
