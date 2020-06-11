//
// Created by Jack on 15/11/25.
//

#ifndef ANDROIDDEMO_ENGINE_H
#define ANDROIDDEMO_ENGINE_H


#include "base/util/BmpHelper.h"

#include <string>
#include <deque>

using std::string;
using std::deque;

class Engine {
public:
// 渲染View的生命周期 ********************************************************************
    static void onCreate(int viewId);

    static void onResume(int viewId);

    static void onPause(int viewId);

    static void onDestroy(int viewId);

// openGL线程调用的渲染接口 ********************************************************************
    static void onSurfaceCreated(int viewId);

    static void onSurfaceChanged(int viewId, int w, int h);

    static void onDrawFrame(int viewId);

// 上层传递图片数据给引擎 ********************************************************************
    static void onItemGetBmp(int viewId, int layerId, string itemId, BmpHelper *ptBmpHelper);

#ifndef __ANDROID__
    static void onItemGetBmp(int viewId, int layerId, const char *itemId, void* ptSrc, int w, int h);
#endif

// 对外业务逻辑 ********************************************************************
    /**
     * 加载3D列表控件
     * @param viewId：渲染控件的Id
     */
    static int loadListView(int viewId);

    /**
     * 清空3D列表的数据
     * @param viewId：渲染控件的Id
     * @param layerId：控件中图层的Id
     */
    static void clearListViewData(int viewId, int layerId);

    /**
     * 在末尾插入一条3D列表的数据
     * @param viewId：渲染控件的Id
     * @param layerId：控件中图层的Id
     * @param dataId：此条数据的Id
     * @param picId：图片的id
     * @param picUrl：图片的url地址
     * @param textId：控件中图层的Id
     * @param text：显示内容
     */
    static void addListViewData(int viewId, int layerId, string dataId, string picId, string picUrl, string textId, string text);

    /**
     * 在获取数据结束时，调用次函数，告知引擎是否还有更多数据，即滑倒末尾时是否再自动加载更多数据。
     * @param viewId：渲染控件的Id
     * @param layerId：控件中图层的Id
     * @param hasMoreData：是否还有更多数据，
     */
    static void requestNextPageDataEnd(int viewId, int layerId, bool hasMoreData);

    /**
     * 设置列表是否为分页加载模式，如果是则调用次函数。
     * @param viewId：渲染控件的Id
     * @param layerId：控件中图层的Id
     * @param content：加载更多的显示文字“加载中”
     * @param heightK：加载更多的显示高度比例k，高度=列表宽度*k
     */
    static void setAddPageMode(int viewId, int layerId, string content, float heightK);

    /**
     * 设置列表中每个item的默认图片。
     * @param viewId：渲染控件的Id
     * @param layerId：控件中图层的Id
     * @param picUrl：默认图片的路径
     */
    static void setListViewDefaultPic(int viewId, int layerId, string picUrl);

    /**
     * 设置渲染控件为Vr模式
     * @param viewId：渲染控件的Id
     * @param url：需要显示的图片url
     */
    static void setVrView(int viewId, int tileLevel, string picId, string url);

    /**
     * 设置渲染控件为详情模式
     * @param viewId：渲染控件的Id
     * @param url：需要显示的图片url
     */
//    static void setBallView(int viewId, string url);

    /**
     * 设置渲染控件为详情模式
     * @param viewId：渲染控件的Id
     * @param url：需要显示的图片瓦片url队列
     * @param picId：图片Id，上层传入，方便获取图片时根据id从不同路径存取
     */
    static void setTileBallView(int viewId, int tileLevel, string picId, string url, int fromX, int offsetX, int fromY, int offsetY);

// 手势 ********************************************************************
    /**
     * 用于停止列表、模型滚动等操作
     * @param viewId：渲染控件的Id
     * @param isDown：是否是按下，否为手势结束
     */
    static void onDown(int viewId, bool isDown);

    /**
     * 点击操作，坐标以屏幕左上角为(0，0)
     * @param viewId：渲染控件的Id
     * @param x：点击的x坐标
     * @param y：点击的y坐标
     */
    static void onClick(int viewId, int x, int y);

    /**
     * 双点击操作
     * @param viewId：渲染控件的Id
     */
    static void onDoubleClick(int viewId);

    /**
     * 双指缩放
     * @param viewId：渲染控件的Id
     * @param scale：缩放系数，首次从1开始(当双指缩放开始时传入)
     */
    static void onZoom(int viewId, float scale);

    /**
     * 手指在屏幕上滑动
     * @param viewId：渲染控件的Id
     * @param disX：距离上次的X轴滑动距离
     * @param disY：距离上次的Y轴滑动距离
     */
    static void onScroll(int viewId, int disX, int disY);

    /**
     * 手指在屏幕上Fling
     * @param viewId：渲染控件的Id
     * @param speedX：手指抬起时的X轴速度
     * @param speedY：手指抬起时的Y轴速度
     */
    static void onFling(int viewId, float speedX, float speedY);

// 传感器 ********************************************************************
    /**
     * 传入传感器数据
     * @param xyzw：世界坐标系的四元数
     */
    static void saveRotateVector(float x, float y, float z, float w);

// 骨骼动画 ********************************************************************

    /**
     * 根据动画脚本，添加舞台容器
     * @param id：骨骼动画的Id
     */
    static void buildStage(string id);

    /**
     * 根据动画脚本，设置舞台画布尺寸
     * @param id：骨骼动画的Id
     * @param w：容器宽
     * @param h：画布高
     */
    static void setStageSize(string id, int w, int h);

    /**
     * 根据动画脚本，添加角色
     * @param id：骨骼动画的Id
     */
    static void buildActor(string id);

    /**
     * 根据动画脚本，添加角色的骨骼
     * @param id：骨骼动画的Id
     */
    static void buildBone(string id);

    /**
     * 根据动画脚本，设置骨骼的蒙皮信息
     * @param id：骨骼动画的Id
     * @param left/top/w/h：此骨骼对应的图片区域
     * @param totalW、totalH：整图的宽高
     */
    static void setBonePicInfo(string id, int left, int top, int w, int h, int totalW, int totalH);

    /**
     * 根据动画脚本，添加骨骼的动画
     * @param id：骨骼动画的Id
     */
    static void buildBoneAnim(string id);

    /**
     * 根据动画脚本，设置当前动画的时间片段
     * @param id：骨骼动画的Id
     * @param startPercent/endPercent：起止时间片段，[0，1]
     * @param isShow：此时间片段中是否可视
     */
    static void setBoneAnimRunPercent(string id, float startPercent, float endPercent, bool isShow);

    /**
     * 根据动画脚本，设置当前动画的速率
     * @param id：骨骼动画的Id
     * @param interpolator：枚举，减速-1，正常0，加速1
     */
    static void setBoneAnimInterpolator(string id, int interpolator);

    /**
     * 根据动画脚本，设置当前动画的位移信息
     * @param id：骨骼动画的Id
     * @param fromScaleX/Y：起始X/Y轴的缩放系数
     * @param toScaleX/Y：终止X/Y轴的缩放系数
     * @param fromCenterX/Y：起始的中心点X/Y坐标
     * @param toCenterX/Y：终止的中心点X/Y坐标
     */
    static void setBoneAnimRect(
            string id,
            float fromScaleX, float fromScaleY, float toScaleX, float toScaleY,
            int fromCenterX, int fromCenterY, int toCenterX, int toCenterY
    );

    /**
     * 根据动画脚本，设置当前动画的透明度
     * @param id：骨骼动画的Id
     * @param from/to：起始/终止的透明度[0，255]
     */
    static void setBoneAnimAlpha(string id, int from, int to);

    /**
     * 根据动画脚本，设置当前动画的透明度
     * @param id：骨骼动画的Id
     * @param from/to：起始/终止的旋转角度
     * @param rotateX/Y：旋转圆心坐标
     */
    static void setBoneAnimRotate(string id, float from, float to, int rotateX, int rotateY);

    /**
     * 设置渲染控件为骨骼动画模式
     * @param viewId：渲染控件的Id
     * @param id：骨骼动画的Id
     * @param xmlUrl：骨骼动画的xml路径
     * @param picUrl：骨骼动画的pic路径
     */
    static void setBoneAnimView(int viewId, string id, string xmlUrl, string picUrl);

    /**
     * 画布尺寸改变
     * @param id：骨骼动画的Id
     * @param w/h：容器宽高
     * @param left/top：目前传入0，为后继支持画布的padding设计
     */
    static void onViewSizeChange(string id, int w, int h, int left, int top);

    /**
     * 停止并释放动画
     * @param id：骨骼动画的Id
     */
    static void stop(string id);

    /**
     * 设置动画的运行百分比
     * @param id：骨骼动画的Id
     * @param percent：[0，1]
     */
    static void setPercent(string id, float percent);
};


#endif //ANDROIDDEMO_ENGINE_H
