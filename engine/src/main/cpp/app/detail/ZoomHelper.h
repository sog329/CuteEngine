//
// Created by Jack on 15/12/21.
//

#ifndef ANDROIDDEMO_ZOOMHELPER_H
#define ANDROIDDEMO_ZOOMHELPER_H


class ZoomHelper {
private:
    float mZoom; // 1,2,3

    float mZoomFrom;
    float mZoomChange;
    long mStartTime;

    float mBaseZoom;

    static const long DURATION = 300;
    static const long NONE = -1;
    static const long NOW = -2;
public:
    ZoomHelper();

    void moveNextLevel();

    void run(long drawTime);

    bool isZooming();

    void changeZoom(float zoom);

    float getZoom();
};


#endif //ANDROIDDEMO_ZOOMHELPER_H
