//
// Created by Jack on 15/12/24.
//

#include "LyVrBall.h"
#include "../../base/util/MatrixHelper.h"
#include "../../base/util/SensorHelper.h"
#include <math.h>

LyVrBall::LyVrBall(int viewId, int threadNum) : ILayer(viewId, threadNum) {
//    mIsTouchalbe = true;
    mIsUseSensor = true;
    show("LyVrBall()");

    mTileLevel = 0;
    Item *ptLevel0 = new Item();
    PgBall::DrawInfo *ptDrawInfo = new PgBall::DrawInfo(getPtPicLoader(0), 0, 360, 90, 180);
    ptDrawInfo->setSize(2048, 1024);
    MatrixHelper::setRotateM(ptDrawInfo->getMatrixCurrentExtra(), 90, 1, 0, 0);
    ptLevel0->mLstPic.push_back(ptDrawInfo);
    mLstItem.push_back(ptLevel0);
}

LyVrBall::~LyVrBall() {
    show("~LyVrBall");
}

void LyVrBall::setTileLevel(int level) {
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

bool LyVrBall::onDraw(long drawTime) {
    int itemSize = (int) mLstItem.size();
    if (itemSize > 0) {
        PgBall::DrawInfo *ptPic0 = (PgBall::DrawInfo *) (mLstItem[0]->mLstPic[0]);
        ptPic0->initTexture(mViewId, getPtPicLoader(0));
        if (ptPic0->mIsTextureReady) {
            if (mIsUseSensor) {
                MatrixHelper::copyMatrix(ptPic0->getMatrixCurrent(), SensorHelper::getCurrentRotationMatrix44());
//                float ary[3];
//                float mt[16];
//                MatrixHelper::copyMatrix(mt, SensorHelper::getCurrentRotationMatrix44());
//                MatrixHelper::multiplyMM(mt, ptPic0->getMatrixCurrent());
//                MatrixHelper::getRotationEuler(mt, ary);
//                show("%f, %f, %f", ary[0], ary[1], ary[2]);
            }
            
            ptPic0->prepareDraw(true, mWidth, mHeight);
            mPgBall.onDraw(ptPic0, drawTime);
            ptPic0->prepareDraw(false, mWidth, mHeight);
            mPgBall.onDraw(ptPic0, drawTime);
        }
        if (itemSize == 2) {
            for (int i = 0; i < mLstItem[1]->mLstPic.size(); i++) {
                PgBall::DrawInfo *ptPic = (PgBall::DrawInfo *) mLstItem[1]->mLstPic[i];
                ptPic->initTexture(mViewId, getPtPicLoader(0));
                if (ptPic->mIsTextureReady) {
                    MatrixHelper::copyMatrix(ptPic->getMatrixCurrent(), ptPic0->getMatrixCurrent());
                    MatrixHelper::copyMatrix(ptPic->getMatrixCurrentExtra(), ptPic0->getMatrixCurrentExtra());
                    ptPic->prepareDraw(true, mWidth, mHeight);
                    mPgBall.onDraw(ptPic, drawTime);
                    ptPic->prepareDraw(false, mWidth, mHeight);
                    mPgBall.onDraw(ptPic, drawTime);
                }
            }
        }
    }
    return true;
}

void LyVrBall::onSizeChange(int w, int h) {
    ILayer::onSizeChange(w, h);
    mPgBall.onSizeChange(w, h / 2);
}

void LyVrBall::initProgram() {
    mPgBall.init();
}

void LyVrBall::updateItem() {
    if (mLstData.size() == 1) {
        Pic *ptPic = mLstItem[0]->mLstPic[0];
        string url = ((Data *) mLstData[0])->picUrl;
        string picId = ((Data *) mLstData[0])->picId;
        if (mTileLevel == 0) {
            ptPic->setUrl(Item::getItemIvId(picId), url);
        } else {
            int row = 1;
            int column = 1;
            Ball::getTileInfo(mTileLevel, &row, &column);
            string tileUrl = Ball::getTilePath(url, 0, 0, 1);
            ptPic->setUrl(Item::getItemIvId(picId), tileUrl);
            if (mLstItem.size() == 2) {
//                mMapUrl.clear();
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < column; j++) {
                        tileUrl = Ball::getTilePath(url, i, j, mTileLevel);
//                        mMapUrl.insert(std::pair<int, string>(column * i + j, tileUrl));
                        int index = j + i * column;
                        Pic *ptPic = mLstItem[1]->mLstPic[j + i * column];
                        ptPic->setUrl(Item::getItemIvId(picId, index), tileUrl);
                    }
                }
            }
        }
        PgBall::DrawInfo *ptDrawInfo = (PgBall::DrawInfo *) (mLstItem[0]->mLstPic[0]);
        MatrixHelper::setRotateM(ptDrawInfo->getMatrixCurrentExtra(), 90, 1, 0, 0);
    }
}


//void LyVrBall::updateTile(float rtX, float rtY) {
//    if (mTileLevel > 0 && mLstItem.size() == 2 && mLstData.size() > 0) {
//        float fovX = mPgBall.getFovDegreeX() / 2 * mPgBall.getCameraK();
//        float fovY = mPgBall.getFovDegreeY() / 2 * mPgBall.getCameraK();
//        float fromX = rtX - fovX - 90;
//        if (fromX > 360) {
//            fromX -= 360;
//        } else if (fromX < 0) {
//            fromX += 360;
//        }
//        float toX = rtX + fovX - 90;
//        if (toX > 360) {
//            toX -= 360;
//        } else if (toX < 0) {
//            toX += 360;
//        }
//        float fromY = rtY - fovY + 90;
//        float toY = rtY + fovY + 90;
//        int row = 1;
//        int column = 1;
//        Ball::getTileInfo(mTileLevel, &row, &column);
//        int offsetX = 360 / column;
//        int offsetY = 180 / row;
//        int fromColumn = (int) (fromX / offsetX);
//        int toColumn = (int) (toX / offsetX);
//        int fromRow = (int) (fromY / offsetY);
//        int toRow = (int) (toY / offsetY);
//        if (fromColumn > toColumn) {
//            toColumn += column;
//        }
//        if (fromRow > toRow) {
//            toRow += row;
//        }
//        for (int i = fromRow; i <= toRow; i++) {
//            for (int j = fromColumn; j <= toColumn; j++) {
//                if (i > row) {
//                    i -= row;
//                }
//                if (j > column) {
//                    j -= column;
//                }
//                int key = column * i + j;
//                std::map<int, string>::iterator it;
//                it = mMapUrl.find(key);
//                if (it != mMapUrl.end()) {
//                    string tileUrl = it->second;
//                    Pic *ptPic = mLstItem[1]->mLstPic[j + i * column];
//                    ptPic->setUrl(getPtPicLoader(0), getItemIvId(((Data *) mLstData[0])->picId, i, tileUrl), tileUrl);
//                    mMapUrl.erase(it);
//                }
//            }
//        }
//    }
//}