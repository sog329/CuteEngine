//
// Created by Jack on 15/11/22.
//

#include "LyBall.h"
#include "../../base/util/TouchHelper.h"
#include "../../base/util/MatrixHelper.h"
#include "../../base/platform/PlatformHelper.h"
#include "../../base/util/TimeHelper.h"
#include "../../base/util/SensorHelper.h"

LyBall::LyBall(int viewId, int threadNum, int startX, int offsetX, int startY, int offsetY) : ILayer(viewId, threadNum) {
    mIsTouchalbe = true;
    //    mIsUseSensor = true;
    show("LyBall(): %d, %d, %d, %d", startX, offsetX, startY, offsetY);
    setBallAngle(startX, offsetX, startY, offsetY);

    mTileLevel = 0;
    Item *ptLevel0 = new Item();
    PgBall::DrawInfo *ptDrawInfo = new PgBall::DrawInfo(getPtPicLoader(0), startX, offsetX, startY, offsetY);
    ptDrawInfo->setSize(4096, 2048);
    MatrixHelper::setRotateM(ptDrawInfo->getMatrixCurrentExtra(), 90, 1, 0, 0);
    ptLevel0->mLstPic.push_back(ptDrawInfo);
    mLstItem.push_back(ptLevel0);
}

LyBall::~LyBall() {
    show("~LyBall");
}

void LyBall::setTileLevel(int level) {
    bool change = mTileLevel != level;
    mTileLevel = level;
    if (change) {
        if (mLstItem.size() == 2) {
            delete mLstItem[1];
            mLstItem.pop_back();
        }
        if (mTileLevel > 1) {
            Item *ptTileItem = new Item();
            int row = 1;
            int column = 1;
            Ball::getTileInfo(mTileLevel, &row, &column);
            float len = 180 / row;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    float startX = len * j;
                    float offsetX = len;
                    float startY = 90 - len * i;
                    float offsetY = len;
                    PgBall::DrawInfo *ptDrawInfo = new PgBall::DrawInfo(getPtPicLoader(0), startX, offsetX, startY, offsetY);
                    ptDrawInfo->setSize(4096, 2048);
                    ptTileItem->mLstPic.push_back(ptDrawInfo);
                }
            }
            mLstItem.push_back(ptTileItem);
        }
        updateItem();
    }
}

bool LyBall::onDraw(long drawTime) {
    if (mZoomHelper.isZooming()) {
        mZoomHelper.run(drawTime);
        float zoom = mZoomHelper.getZoom();
        mPgBall.setNear(3 * (.8 + zoom * zoom / 5));
        resetMaxRotateOffset();
        judgeRotate();
    }
    int itemSize = (int) mLstItem.size();
    if (itemSize > 0) {
        PgBall::DrawInfo *ptPic0 = (PgBall::DrawInfo *) (mLstItem[0]->mLstPic[0]);
        ptPic0->initTexture(mViewId, getPtPicLoader(0));
        if (ptPic0->mIsTextureReady) {
            if (mIsUseSensor) {
                MatrixHelper::copyMatrix(ptPic0->getMatrixCurrent(), SensorHelper::getCurrentRotationMatrix44());
            }
            mPgBall.onDraw(ptPic0, drawTime);
        }
        if (itemSize == 2) {
            for (int i = 0; i < mLstItem[1]->mLstPic.size(); i++) {
                PgBall::DrawInfo *ptPic = (PgBall::DrawInfo *) mLstItem[1]->mLstPic[i];
                ptPic->initTexture(mViewId, getPtPicLoader(0));
                if (ptPic->mIsTextureReady) {
                    MatrixHelper::copyMatrix(ptPic->getMatrixCurrent(), ptPic0->getMatrixCurrent());
                    MatrixHelper::copyMatrix(ptPic->getMatrixCurrentExtra(), ptPic0->getMatrixCurrentExtra());
                    mPgBall.onDraw(ptPic, drawTime);
                }
            }
        }
    }
    return true;
}

void LyBall::onSizeChange(int w, int h) {
    ILayer::onSizeChange(w, h);
    mPgBall.onSizeChange(w, h);
    resetMaxRotateOffset();
}

void LyBall::initProgram() {
    mPgBall.init();
}

void LyBall::updateItem() {
    if (mLstData.size() == 1) {
        Pic *ptPic = mLstItem[0]->mLstPic[0];
        string url = ((Data *) mLstData[0])->picUrl;
        string picId = ((Data *) mLstData[0])->picId;
        if (mTileLevel == 0) {
            ptPic->setUrl(Item::getItemIvId(picId), url);
        } else {
            string tileUrl = Ball::getTilePath(url, 0, 0, 1);
            ptPic->setUrl(Item::getItemIvId(picId), tileUrl);
            if (mLstItem.size() == 2) {
                mMapUrl.clear();
                int row = 1;
                int column = 1;
                Ball::getTileInfo(mTileLevel, &row, &column);
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < column; j++) {
                        tileUrl = Ball::getTilePath(url, i, j, mTileLevel);
                        mMapUrl.insert(std::pair<int, string>(column * i + j, tileUrl));
                    }
                }
                judgeRotate();
            }
        }
        PgBall::DrawInfo *ptDrawInfo = (PgBall::DrawInfo *) (mLstItem[0]->mLstPic[0]);
        if (mIsUseSensor) {
            MatrixHelper::setRotateM(ptDrawInfo->getMatrixCurrentExtra(), 90, 1, 0, 0);
        } else {
            MatrixHelper::setRotateM(ptDrawInfo->getMatrixCurrent(), mRotateCenterX, 1, 0, 0);
            MatrixHelper::setRotateM(ptDrawInfo->getMatrixCurrentExtra(), mRotateCenterY, 0, 1, 0);
        }
    }
}

bool LyBall::judgeTouchEvent() {
    if (!mZoomHelper.isZooming()) {
        TouchHelper::Result *ptResult = TouchHelper::getPtResult(mViewId);
        if (ptResult != NULL) {
            int disX = ptResult->disX;
            int disY = ptResult->disY;
            int isDoubleClick = ptResult->isDoubleClick;
            if (isDoubleClick) {
                mZoomHelper.moveNextLevel();
            } else {
                float scale = ptResult->scale;
                if (scale > 0) {
                    mZoomHelper.changeZoom(scale);
                } else {
                    if (scale == 0) {
                        mZoomHelper.changeZoom(scale);
                    }
                    if ((disX != 0 || disY != 0) && mWidth * mHeight != 0) {
                        float degreeY = mPgBall.getFovDegreeX() * disX / mWidth * mPgBall.getCameraK();
                        float degreeX = mPgBall.getFovDegreeY() * disY / mHeight * mPgBall.getCameraK();

                        mRotateOffsetX += degreeX;
                        mRotateOffsetY += degreeY;

                        judgeRotate();
                    }
                }
            }
        }
    }
    return true;
}


void LyBall::setBallAngle(int startX, int offsetX, int startY, int offsetY) {
    mStartX = startX;
    mOffsetX = offsetX;
    mStartY = startY;
    mOffsetY = offsetY;

    mRotateCenterY = 90 + offsetX / 2;
    mRotateCenterX = -(startY - offsetY / 2);

    mRotateOffsetX = 0;
    mRotateOffsetY = 0;
    resetMaxRotateOffset();
}

void LyBall::resetMaxRotateOffset() {
    show("LyBall::resetMaxRotateOffset");
    float fovX = mPgBall.getCameraK() * mPgBall.getFovDegreeX();
    float fovY = mPgBall.getCameraK() * mPgBall.getFovDegreeY();
    if (fovY > mOffsetY) {
        mMaxRotateOffsetX = 0;
    } else {
        mMaxRotateOffsetX = (mOffsetY - fovY) / 2;
    }
    if (mOffsetX < 360) {
        if (fovX > mOffsetX) {
            mMaxRotateOffsetY = 0;
        } else {
            mMaxRotateOffsetY = (mOffsetX - fovX) / 2;
        }
    } else {
        mMaxRotateOffsetY = 180;
    }
}

void LyBall::judgeRotate() {
    if (mLstItem.size() > 0) {
        deque<Pic *> lstPic = mLstItem[0]->mLstPic;
        if (lstPic.size() > 0) {
            PgBall::DrawInfo *ptPic = (PgBall::DrawInfo *) lstPic[0];
            if (abs(mRotateOffsetX) > mMaxRotateOffsetX) {
                if (mRotateOffsetX > 0) {
                    mRotateOffsetX = mMaxRotateOffsetX;
                } else {
                    mRotateOffsetX = -mMaxRotateOffsetX;
                }
            }
            if (mOffsetX < 360) {
                if (abs(mRotateOffsetY) > mMaxRotateOffsetY) {
                    if (mRotateOffsetY > 0) {
                        mRotateOffsetY = mMaxRotateOffsetY;
                    } else {
                        mRotateOffsetY = -mMaxRotateOffsetY;
                    }
                }
            } else {
                if (mRotateOffsetY > mMaxRotateOffsetY) {
                    mRotateOffsetY -= 360;
                } else if (mRotateOffsetY < -mMaxRotateOffsetY) {
                    mRotateOffsetY += 360;
                }
            }
            float rtY = mRotateCenterX + mRotateOffsetX;
            float rtX = mRotateCenterY + mRotateOffsetY;
            MatrixHelper::setRotateM(ptPic->getMatrixCurrent(), rtY, 1, 0, 0);
            MatrixHelper::setRotateM(ptPic->getMatrixCurrentExtra(), rtX, 0, 1, 0);
            updateTile(rtX, rtY);
        }
    }
}

void LyBall::updateTile(float rtX, float rtY) {
    if (mTileLevel > 0 && mLstItem.size() == 2 && mLstData.size() > 0) {
        float fovX = mPgBall.getFovDegreeX() / 2 * mPgBall.getCameraK();
        float fovY = mPgBall.getFovDegreeY() / 2 * mPgBall.getCameraK();
        float fromX = rtX - fovX - 90;
        if (fromX > 360) {
            fromX -= 360;
        } else if (fromX < 0) {
            fromX += 360;
        }
        float toX = rtX + fovX - 90;
        if (toX > 360) {
            toX -= 360;
        } else if (toX < 0) {
            toX += 360;
        }
        float fromY = rtY - fovY + 90;
        float toY = rtY + fovY + 90;
        int row = 1;
        int column = 1;
        Ball::getTileInfo(mTileLevel, &row, &column);
        int offsetX = 360 / column;
        int offsetY = 180 / row;
        int fromColumn = (int) (fromX / offsetX);
        int toColumn = (int) (toX / offsetX);
        int fromRow = (int) (fromY / offsetY);
        int toRow = (int) (toY / offsetY);
        if (fromColumn > toColumn) {
            toColumn += column;
        }
        if (fromRow > toRow) {
            toRow += row;
        }
        for (int i = fromRow; i <= toRow; i++) {
            for (int j = fromColumn; j <= toColumn; j++) {
                if (i > row) {
                    i -= row;
                }
                if (j > column) {
                    j -= column;
                }
                int key = column * i + j;
                std::map<int, string>::iterator it;
                it = mMapUrl.find(key);
                if (it != mMapUrl.end()) {
                    string tileUrl = it->second;
                    int index = j + i * column;
                    Pic *ptPic = mLstItem[1]->mLstPic[index];
                    ptPic->setUrl(Item::getItemIvId(((Data *) mLstData[0])->picId, index), tileUrl);
                    mMapUrl.erase(it);
                }
            }
        }
    }
}


