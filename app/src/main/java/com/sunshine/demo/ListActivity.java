/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */

package com.sunshine.demo;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.os.Bundle;

import com.sunshine.engine.app.ListView;
import com.sunshine.engine.util.LogTool;
import com.sunshine.engine.util.callback.ListCallback;
import com.sunshine.engine.util.callback.LogCalllback;
import com.sunshine.engine.util.callback.TvCallback;
import com.sunshine.engine.util.pic.BmpHelper;
import com.sunshine.engine.util.pic.SdcardHelper;
import com.sunshine.engine.util.pic.UrlHelper;

import java.util.ArrayList;
import java.util.List;

public class ListActivity extends Activity {
    private ListView mView = null;
    private List<String> mLstUrl = new ArrayList<String>();

    @Override
    protected void onCreate(final Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.activity_listview);

        LogTool.addLogCallback(new LogCalllback() {
            @Override
            public void show(String str) {
                android.util.Log.d("____", str);
            }
        });

        mView = (ListView) findViewById(R.id.ugc_view);

        ListCallback callback = new ListCallback() {
            @Override
            public void onClick(int dataIndex, String dataId) {
                int n = 2;
                if (dataIndex % n == 0) {
                    Intent intent = new Intent(ListActivity.this, BoneAnim2DActivity.class);
                    startActivity(intent);
                } else if (dataIndex % n == 1) {
                    Intent intent = new Intent(ListActivity.this, BoneAnim3DActivity.class);
                    startActivity(intent);
                } else if (dataIndex % n == 2) {
                    String url = mLstUrl.get(dataIndex);
                    Intent intent = new Intent(ListActivity.this, VrActivity.class);
                    intent.putExtra(DetailActivity.URL, url);
                    startActivity(intent);
                } else {
                    String url = mLstUrl.get(dataIndex);
                    Intent intent = new Intent(ListActivity.this, DetailActivity.class);
                    intent.putExtra(DetailActivity.URL, url);
                    startActivity(intent);
                }
            }

            @Override
            public void onLoadNextPageData(final int viewId, final int layerId) {
                Thread t = new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            Thread.sleep(200);
                            for (int i = 0; i < 10; i++) {
                                addData();
                            }
                            if (mLstUrl.size() > 30) {
                                mView.onLoadNextPageData(false);
                            } else {
                                mView.onLoadNextPageData(true);
                            }
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                });
                t.start();
            }
        };
        mView.setDataCallback(callback);

        mView.addTvCallback(ListView.TV_NAME_ID, new TvCallback() {
            @Override
            public Bitmap buildBmp(String content, int w, int h) {
                Bitmap bmp = BmpHelper.getBitmapByText(w, h, content, (int) (h * .7), Color.rgb(255, 255, 255), Color.argb(170, 60, 60, 60), h / 4, h / 15, false);
                return bmp;
            }
        });

        mView.setAddPageMode("加载中", 1.0f / 8);
        mView.setDefaultPic(UrlHelper.buildAssetUrl("pic/listview_default_pic.jpg"));
        mView.clearListViewData();

        SdcardHelper.addFolderName("find", "tmpPic", 200);

        //        startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("baidupanougc://preview/?jobID=551a1c3e5a06ee251e3ca7ae&userID=80152228")));
    }

    @Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mView.onDestroy();
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        finish();
    }

    private void addData() {
        int index = mLstUrl.size();
        String picUrl = UrlHelper.buildAssetUrl("pic/p" + index % 12 + ".jpg");
        if (index == 0) {
            //            picUrl = "http://bos.nj.bpc.baidu.com/v1/quanjing-img/55684be0cba709e3763c9b7d_1447728032_scc23pb05t_1451981303.jpg";
        }
        mLstUrl.add(picUrl);
        LogTool.show("picUrl[" + index + "]=" + picUrl);
        long t = System.currentTimeMillis();
        mView.addListViewData("iv[" + index + "]", "find", picUrl, "Try[" + index + "]");
        LogTool.show("addData cost:" + (System.currentTimeMillis() - t) + "ms");
    }
}
