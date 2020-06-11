/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;

import com.sunshine.engine.app.bone.BoneView;
import com.sunshine.engine.base.Lib;
import com.sunshine.engine.util.pic.BmpHelper;
import com.sunshine.engine.util.reflex.Engine;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.io.IOException;
import java.io.InputStream;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

/**
 * Created by Jack on 15/12/7.
 */
public class XmlHelper {
    class BoneXmlHandler extends DefaultHandler {
        private StringBuilder bd = new StringBuilder();
        private int mPicWidth = 0;
        private int mPicHeight = 0;
        private String mId = null;

        public BoneXmlHandler(String id, int w, int h) {
            mId = id;
            mPicWidth = w;
            mPicHeight = h;
        }

        @Override
        public void startDocument() throws SAXException {
            super.startDocument();
            bd.setLength(0);
            Lib.buildStage(mId);
        }

        @Override
        public void startElement(String uri, String localName, String qName, Attributes atr) throws SAXException {
            super.startElement(uri, localName, qName, atr);
            String tag = localName.length() != 0 ? localName : qName;
            if (tag.equals("actor")) {
                Lib.buildActor(mId);
            } else if (tag.equals("bone")) {
                Lib.buildBone(mId);
            } else if (tag.equals("ba")) {
                Lib.buildBoneAnim(mId);
            }
            bd.setLength(0);
        }

        @Override
        public void characters(char[] ch, int start, int length) throws SAXException {
            super.characters(ch, start, length);
            bd.append(ch, start, length);
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException {
            super.endElement(uri, localName, qName);
            String tag = localName.length() != 0 ? localName : qName;
            if (tag.equals("width_height")) {
                String[] ary = getAry(bd.toString());
                Lib.setStageSize(mId, Integer.parseInt(ary[0]), Integer.parseInt(ary[1]));
            } else if (tag.equals("rect_ltwhxy")) {
                String[] ary = getAry(bd.toString());
                Lib.setBonePicInfo(mId, Integer.parseInt(ary[0]), Integer.parseInt(ary[1]), Integer.parseInt(ary[2]), Integer.parseInt(ary[3]), mPicWidth, mPicHeight);
            } else if (tag.equals("alpha")) {
                String[] ary = getAry(bd.toString());
                Lib.setBoneAnimAlpha(mId, Integer.parseInt(ary[0]), Integer.parseInt(ary[1]));
            } else if (tag.equals("rate")) {
                int interpolator = -1;
                if (bd.toString().equals("accelerate")) {
                    interpolator = 1;
                }
                Lib.setBoneAnimInterpolator(mId, interpolator);
            } else if (tag.equals("start_end")) {
                String[] ary = getAry(bd.toString());
                Lib.setBoneAnimRunPercent(mId, Float.parseFloat(ary[0]), Float.parseFloat(ary[1]), true);
            } else if (tag.equals("start_end_invisible")) {
                String[] ary = getAry(bd.toString());
                Lib.setBoneAnimRunPercent(mId, Float.parseFloat(ary[0]), Float.parseFloat(ary[1]), false);
            } else if (tag.equals("rect_smft")) {
                String[] ary = getAry(bd.toString());
                Lib.setBoneAnimRect(mId, Float.parseFloat(ary[0]), Float.parseFloat(ary[1]), Float.parseFloat(ary[2]), Float.parseFloat(ary[3]), Integer.parseInt(ary[4]), Integer.parseInt(ary[5]), Integer.parseInt(ary[6]), Integer.parseInt(ary[7]));
            } else if (tag.equals("rect_rotate")) {
                String[] ary = getAry(bd.toString());
                Lib.setBoneAnimRotate(mId, Float.parseFloat(ary[0]), Float.parseFloat(ary[1]), Integer.parseInt(ary[2]), Integer.parseInt(ary[3]));
            }
        }
    }

    ;

    public boolean parse(final String id, final String xmlUrl, final String picUrl, BoneView.Callback callback) {
        boolean success = false;
        if (xmlUrl != null) {
            InputStream is = null;
            Bitmap bmp = null;
            try {
                Context context = Engine.getContext();
                if (context != null) {
//                    String picUrl = getPicUrl(xmlUrl, "pic");
                    bmp = BmpHelper.getBmpByAssets(context, picUrl, 0, 0);
                    if (bmp != null) {
                        AssetManager assetManager = context.getAssets();
                        is = assetManager.open(xmlUrl);
                        SAXParserFactory sf = SAXParserFactory.newInstance();
                        SAXParser sp = sf.newSAXParser();
                        BoneXmlHandler handler = new BoneXmlHandler(id, bmp.getWidth(), bmp.getHeight());
                        sp.parse(is, handler);
                        success = true;
                    }
                }
            } catch (Exception e) {
                LogTool.show(e.toString());
            } finally {
                if (is != null) {
                    try {
                        is.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                if (success) {
                    if (callback != null) {
                        callback.onGetBmp(id, bmp);
                    }
                } else {
                    if (bmp != null) {
                        bmp.recycle();
                    }
                }
            }
        }
        return success;
    }

    private static String[] getAry(String str) {
        if (str == null) {
            return null;
        } else {
            return str.split(",");
        }
    }

    private static String getPicUrl(String url, String picName) {
        if (url == null) {
            return null;
        } else {
            return url.replace("config.xml", "") + picName;
        }
    }
}
