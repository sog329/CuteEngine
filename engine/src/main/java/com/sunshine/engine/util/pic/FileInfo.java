/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.pic;

/**
 * Created by Jack on 16/2/15.
 */
public class FileInfo {
    private String mFilePath = null;
    private long mCreateTime = 0;

    public String getFilePath() {
        return mFilePath;
    }

    public void setFilePath(String filePath) {
        mFilePath = filePath;
    }

    public long getCreateTime() {
        return mCreateTime;
    }

    public void setCreateTime(long createTime) {
        mCreateTime = createTime;
    }
}
