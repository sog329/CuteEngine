//
// Created by Jack on 15/11/20.
//

#ifndef BASE_LYLISTVIEW_H
#define BASE_LYLISTVIEW_H


#include "ILayer.h"
#include "SpringHelper.h"

class ILyListView : public ILayer {
protected:
    float mItemHeightK;

    float mItemPaddingK;
    int mItemPadding;

    int mVisibleItemNum;
    int mPreloadItemNum;
    int mFirstItemDataIndex;

    int mItemHeight;
    int mItemContentWidth;
    int mItemContentHeight;
    int mItemCurrentY;
    int mScrollY;

    Pic *ptAddMore; // 更多按钮
    bool mHasMoreData;
    bool mIsGettingData;
    string mAddMoreContent;
    float mAddMoreK;
    int mAddMoreHeight;

    Pic *ptDefaultPic; // 默认图片
    string mDefaultPicUrl;

    int mMaxScrollY;

    SpringHelper mSpringHelper;

public:
    ILyListView(int viewId, int threadNum);

    virtual ~ILyListView();

    /**
     * 初始化列表尺寸
     * itemWidthK/itemHeightK：列表宽高占父View的比例
     * paddingK：内边距比例，以最短边为准
     * preloadItemNum：预加载数量
     */
    void initItemSize(float itemHeightK, float paddingK, int visibleItemNum, int preloadItemNum);

    virtual void onSizeChange(int w, int h);

    virtual void updateItem();

    bool setItemPosition(int itemIndex);

    bool onDraw();

    // 更新最大的Scroll值
    void updateMaxScrollY();

    bool judgeTouchEvent();

    virtual string getDataId(int index) = 0;

    void onPause(bool inGLThread);

    void setAddPageMode(string content, float heightK);

    void requestNextPageDataEnd(bool hasMoreData);

    static void *onLoadNextPageData(void *obj);

    struct NextPageInfo {
    public:
        int viewId;
        int layerId;
    };

    void setDefaultPicUrl(string picUrl);

private:

    void scrollBy(int distance);

    int getFirstVisibleItemDataIndex(int scrollY);

    virtual Item *getItemObject() = 0;
};


#endif //BASE_LYLISTVIEW_H
