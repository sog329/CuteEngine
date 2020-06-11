//
//  IosInterface.h
//  HiGL
//
//  Created by Jack on 15/12/2.
//  Copyright © 2015年 Jack. All rights reserved.
//

#ifndef __ANDROID__


#ifndef IosInterface_h
#define IosInterface_h

class IosInterface {
public:
    IosInterface();
    virtual ~IosInterface();
    // 线程中调用，当获取到位图buffer后，调用Engine::onItemGetBmp(..)
    virtual void requestBmp(
            int viewId, // 渲染控件的Id
            int layerId, // 渲染控件的内部layerId
            const char *itemId, // 渲染控件内部layer中item的Id
            const char *url, // 请求图片的url地址
            int w, // 建议图片的尺寸w
            int h // 建议图片的尺寸h
    ) = 0;

    // ios目前可以先不实现，Android端支持脏渲染，ios端正在调此机制
    virtual void requestRender(
            int viewId // 渲染控件的Id
    ) = 0;
    
    // 读取下一页数据
    virtual void onLoadNextPageData(
            int viewId, // 渲染控件的Id
            int layerId // 渲染控件的图层Id
    ) = 0;
    
    // 列表被click后调用
    virtual void onClick(
            int viewId, // 渲染控件的Id
            int dataIndex, // 被点击的数据索引
            const char *dataId // 被点击的数据id
    ) = 0;

};


#endif /* IosInterface_h */

#endif
