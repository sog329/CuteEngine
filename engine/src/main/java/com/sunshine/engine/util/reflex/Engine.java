/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.reflex;

import android.content.Context;
import android.graphics.Bitmap;
import android.opengl.GLSurfaceView;
import android.view.View;

import com.sunshine.engine.app.bone.BoneView;
import com.sunshine.engine.base.CuteViewGL;
import com.sunshine.engine.base.Lib;
import com.sunshine.engine.util.LogTool;
import com.sunshine.engine.util.XmlHelper;
import com.sunshine.engine.util.callback.Callback;
import com.sunshine.engine.util.callback.ListCallback;
import com.sunshine.engine.util.callback.TvCallback;
import com.sunshine.engine.util.pic.BmpHelper;
import com.sunshine.engine.util.pic.PicDescTool;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by Jack on 2015/11/17 0017.
 */
public class Engine {

    private static Context mContext = null;

    private static Map<Integer, CuteViewGL> mMap = new HashMap<Integer, CuteViewGL>();

    public static void onCreate(View view) {
        if (view != null) {
            if (mContext == null) {
                mContext = view.getContext().getApplicationContext();
            }
            if (view instanceof CuteViewGL) {
                synchronized(mMap) {
                    mMap.put(((CuteViewGL) view).getViewId(), (CuteViewGL) view);
                }
            }
        }
    }

    public static void onDestroy(GLSurfaceView view) {
        if (view != null) {
            synchronized(mMap) {
                mMap.remove(view);
            }
        }
    }

    public static void onClick(int viewId, int dataIndex, String dataId) {
        Callback cb = null;
        synchronized(mMap) {
            GLSurfaceView view = mMap.get(viewId);
            if (view != null) {
                cb = ((CuteViewGL) view).getDataCallback();
            }
        }
        if (cb != null) {
            if (cb instanceof ListCallback) {
                ListCallback listCallback = (ListCallback) cb;
                listCallback.onClick(dataIndex, dataId);
            }
        }
    }

    public static void onLoadNextPageData(int viewId, int layerId) {
        Callback cb = null;
        synchronized(mMap) {
            GLSurfaceView view = mMap.get(viewId);
            if (view != null) {
                cb = ((CuteViewGL) view).getDataCallback();
            }
        }
        if (cb != null) {
            if (cb instanceof ListCallback) {
                ListCallback listCallback = (ListCallback) cb;
                listCallback.onLoadNextPageData(viewId, layerId);
            }
        }
    }

    public static void requestRender(int viewId) {
        synchronized(mMap) {
            CuteViewGL view = mMap.get(viewId);
            if (view != null && view.isResume()) {
                view.requestRender();
            }
        }
    }

    public static void requestBmp(final int viewId, final int layerId, final String itemId, String url, int suggestWidth, int suggestHeight) {
        try {
            android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
            Bitmap bmp = null;
            final long t = System.currentTimeMillis();
            if (url != null && itemId != null) {
                if (itemId.startsWith("tv")) {
                    String[] aryId = itemId.split("_");
                    if (aryId.length >= 3) {
                        String tvId = aryId[1];
                        TvCallback callback = null;
                        synchronized(mMap) {
                            CuteViewGL view = mMap.get(viewId);
                            if (view != null) {
                                callback = view.getTvCallback(tvId);
                            }
                        }
                        if (callback != null) {
                            bmp = callback.buildBmp(url, suggestWidth, suggestHeight);
                        }
                    }
                } else if (itemId.startsWith("stage")) {
                    String[] aryUrl = url.split(";");
                    if (aryUrl.length == 3) {
                        final BoneView.Callback callback = new BoneView.Callback() {
                            @Override
                            public void onGetBmp(String id, Bitmap bmp) {
                                LogTool.show("BmpHelper.getBmpByAssets cost " + (System.currentTimeMillis() - t) + " ms");
                                LogTool.show("bmp.width=" + bmp.getWidth() + ", bmp.height=" + bmp.getHeight());
                                if (bmp != null) {
                                    Lib.onGetBmp(viewId, layerId, itemId, bmp);
                                    bmp.recycle();
                                }
                            }
                        };
                        new XmlHelper().parse(aryUrl[0], aryUrl[1], aryUrl[2], callback);
                    }
                } else {
                    String[] aryId = itemId.split("_");
                    if (aryId.length >= 3) {
                        String id = aryId[1];
                        JSONObject obj = PicDescTool.getJsonObj(aryId[2]);
                        int scale = PicDescTool.getScale(obj);
                        bmp = BmpHelper.getBmpByUrl(mContext, id, url, suggestWidth, suggestHeight, scale);
                    }
                }
                if (bmp != null) {
                    LogTool.show("Engine.requestBmp: " + itemId + " [" + suggestWidth + "," + suggestHeight + "][" + bmp.getWidth() + "," + bmp.getHeight() + "] " + (System.currentTimeMillis() - t) + "ms");
                    Lib.onGetBmp(viewId, layerId, itemId, bmp);
                    bmp.recycle();
                } else {
                    LogTool.show("~Engine.requestBmp - " + itemId);
                }
            }
        } catch (Exception e) {
            LogTool.show("Engine: " + e.toString());
        }
    }

    public static Context getContext() {
        return mContext;
    }
}
