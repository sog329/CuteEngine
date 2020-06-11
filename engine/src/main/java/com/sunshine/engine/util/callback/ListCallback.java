/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.callback;

/**
 * Created by Jack on 16/1/11.
 */
public interface ListCallback extends Callback {
    void onClick(int dataIndex, String dataId);

    void onLoadNextPageData(int viewId, int layerId);
}
