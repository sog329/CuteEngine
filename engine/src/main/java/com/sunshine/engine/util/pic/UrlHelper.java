/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.pic;

/**
 * Created by Jack on 16/1/4.
 */
public class UrlHelper {
    private static final String ASSET_URL = "asset:";
    private static final String HTTP_URL = "http";

    public static String buildAssetUrl(String url) {
        if (url != null && !isAssetUrl(url)) {
            url = ASSET_URL + url;
        }
        return url;
    }

    public static boolean isAssetUrl(String url) {
        boolean isAssetUrl = false;
        if (url != null) {
            isAssetUrl = url.startsWith(ASSET_URL);
        }
        return isAssetUrl;
    }

    public static String decodeAccetUrl(String url) {
        if (url != null) {
            url = url.replace(ASSET_URL, "");
        }
        return url;
    }

    public static boolean isHttpUrl(String url) {
        boolean isHttpUrl = false;
        if (url != null) {
            isHttpUrl = url.toLowerCase().startsWith(HTTP_URL);
        }
        return isHttpUrl;
    }

}
