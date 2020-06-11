//
// Created by Jack on 2015/11/15 0015.
//

#ifndef BASE_APPHELPER_H
#define BASE_APPHELPER_H


#include "../base/util/BmpHelper.h"
#include "../base/view/View.h"

class AppHelper {
public:
    static int loadListView(int viewId);

    static void clearListViewData(int viewId, int layerId);

    static void addListViewData(int viewId, int layerId, string dataId, string picId, string picUrl, string textId, string text);

    static void requestNextPageDataEnd(int viewId, int layerId, bool hasMoreData);

    static void setAddPageMode(int viewId, int layerId, string content, float heightK);

    static void setListViewDefaultPic(int viewId, int layerId, string picUrl);

//    static void setBallView(int viewId, string url);

    static void setTileBallView(int viewId, int tileLevel, string picId, string url, int fromX, int offsetX, int fromY, int offsetY);

    static void setVrView(int viewId, int tileLevel, string picId, string url);

    static void setBoneAnimView(int viewId, string id, string xmlUrl, string picUrl);
};


#endif //BASE_APPHELPER_H
