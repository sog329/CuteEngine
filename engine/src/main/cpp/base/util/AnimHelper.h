//
// Created by Jack on 15/11/23.
//

#ifndef BASE_ANIMHELPER_H
#define BASE_ANIMHELPER_H

namespace CuteEngine {
    class AnimHelper {
    private:
        int mDuration;
        long mStartTime;

        float mAlphaFrom;
        float mAlphaChange;
        float mAlpha;

        float mScaleFrom;
        float mScaleChange;
        float mScale;

//    float mValueFrom;
//    float mValueChange;
//    float mValue;
    public:
        void setAlphaAnim(float from, float to, int dutation);

        void setScaleAnim(float from, float to, int dutation);

//    void setValueAnim(float from, float to, int dutation);

        bool run(long drawTime);

        float getAlpha();

        float getScale();

//    float getValue();

        AnimHelper();

        void clear();
    };
}

#endif //BASE_ANIMHELPER_H
