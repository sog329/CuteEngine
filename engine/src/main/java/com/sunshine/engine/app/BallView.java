/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.app;

import android.content.Context;
import android.util.AttributeSet;

import com.sunshine.engine.base.CuteViewGL;
import com.sunshine.engine.base.Lib;
import com.sunshine.engine.util.pic.SdcardHelper;


/**
 * Created by Jack on 16/2/17.
 */
public class BallView extends CuteViewGL {
    public BallView(Context context) {
        super(context);
    }

    public BallView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public void setTileBallView(int tileLevel, String picId, String url, int fromX, int offsetX, int fromY, int offsetY, String folderPath, int maxNum) {
        Lib.setTileBallView(getViewId(), tileLevel, picId, url, fromX, offsetX, fromY, offsetY);
        SdcardHelper.addFolderName(picId, folderPath, maxNum);
    }
}
