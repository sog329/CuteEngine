//
// Created by Jack on 2015/11/13 0013.
//

#ifndef BASE_BALL_H
#define BASE_BALL_H

#include <string>

using std::string;

class Ball {
private:
    float *mPtAryModelVertex;
    float *mPtAryTextureVertex;
    int mVertexNum;
    float mStartX;
    float mStartY;
    float mOffsetX;
    float mOffsetY;

public:
    Ball();

    Ball(float r, int span, int startX, int offsetX, int startY, int offsetY);

    ~Ball();

    void resize(float r, int span, int startX, int offsetX, int startY, int offsetY);

    float *getPtAryModelVertex();

    float *getPtAryTextureVertex();

    int getVertexNum();

    int getStartX();

    int getOffsetX();

    int getStartY();

    int getOffsetY();

    static void getTileInfo(int tileLevel, int *ptRow, int *ptColumn);

    static string getTilePath(string url, int row, int column, int tileLevel);
};


#endif //BASE_BALL_H
