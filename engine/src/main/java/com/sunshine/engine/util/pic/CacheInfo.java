/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.pic;

/**
 * Created by Jack on 16/2/15.
 */
public class CacheInfo {
    private String mFolderPath = null;
    private int mMaxNumber = 150;

    public String getFolderPath() {
        return mFolderPath;
    }

    public void setFolderPath(String folderPath) {
        mFolderPath = folderPath;
    }

    public int getMaxNumber() {
        return mMaxNumber;
    }

    public void setMaxNumber(int maxNumber) {
        mMaxNumber = maxNumber;
    }
}
