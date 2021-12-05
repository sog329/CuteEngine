/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.pic;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.text.TextPaint;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

/** Created by Jack on 15/11/12. */
public class BmpHelper {
  private static final String ELLIPSIS = "..";

  /**
   * 获取指定尺寸的图片，当需要存储产生缩略图的目标图片时，scale不再为1，为2、4、8..
   *
   * @param ct
   * @param id
   * @param url
   * @param w
   * @param h
   * @param scale
   * @return
   */
  public static Bitmap getBmpByUrl(Context ct, String id, String url, int w, int h, int scale) {
    Bitmap bmp = null;
    if (url != null && id != null && w != 0 && h != 0) {
      if (UrlHelper.isAssetUrl(url)) {
        url = UrlHelper.decodeAccetUrl(url);
        bmp = getBmpByAssets(ct, url, w, h);
      } else if (UrlHelper.isHttpUrl(url)) {
        bmp = SdcardHelper.getImageFromSd(id, url, w, h, scale);
        if (bmp == null) {
          bmp = downloadPic(url);
          if (bmp != null) {
            bmp = resizeBitmap(bmp, w * scale, h * scale); // 存原始尺寸的图片
            SdcardHelper.saveImageToSd(bmp, id, url, w, h, scale);
            if (scale != 1) {
              bmp.recycle();
              bmp = SdcardHelper.getImageFromSd(id, url, w, h, scale);
            }
          }
        }
      } else {
        bmp = getLocalBmp(url, w, h);
      }
    }
    return bmp;
  }

  public static Bitmap getBmpByAssets(Context ct, String str, int w, int h) {
    Bitmap bmp = null;
    if (ct != null) {
      AssetManager am = ct.getAssets();
      if (am != null) {
        InputStream is = null;
        try {
          is = am.open(str);
          if (w == 0 || h == 0) {
            is = am.open(str);
            bmp = BitmapFactory.decodeStream(is);
          } else {
            BitmapFactory.Options op = new BitmapFactory.Options();
            op.inJustDecodeBounds = true;
            BitmapFactory.decodeStream(is, null, op);
            is.close();
            int srcW = op.outWidth;
            int srcH = op.outHeight;
            if (srcW > 0 && srcH > 0) {
              is = am.open(str);
              float scale = 1f * srcW * srcH / w / h;
              if (scale > 1) {
                scale = (float) Math.sqrt(scale);
                op.inJustDecodeBounds = false;
                op.inSampleSize = (int) scale;
                bmp = BitmapFactory.decodeStream(is, null, op);
              } else {
                bmp = BitmapFactory.decodeStream(is);
              }
            }
          }
        } catch (Exception e) {
          e.printStackTrace();
          bmp = null;
        } catch (OutOfMemoryError e) {
          e.printStackTrace();
          bmp = null;
        } finally {
          try {
            if (is != null) {
              is.close();
            }
          } catch (Exception ex) {
            ex.printStackTrace();
          }
        }
      }
    }
    return bmp;
  }

  public static Bitmap resizeBitmap(Bitmap bmp, int width, int height) {
    Bitmap newBmp = null;
    try {
      if (bmp != null && !bmp.isRecycled()) {
        if (bmp.getWidth() > width || bmp.getHeight() > height) {
          Matrix matrix = new Matrix();
          matrix.postScale(((float) width) / bmp.getWidth(), ((float) height) / bmp.getHeight());
          newBmp = Bitmap.createBitmap(bmp, 0, 0, bmp.getWidth(), bmp.getHeight(), matrix, true);
          bmp.recycle();
        } else {
          newBmp = bmp;
        }
      }
    } catch (Exception e) {
      e.printStackTrace();
      if (newBmp != null) {
        if (!newBmp.isRecycled()) {
          newBmp.recycle();
          newBmp = null;
        }
      }
      newBmp = bmp;
    }
    return newBmp;
  }

  public static Bitmap getLocalBmp(String path, int w, int h) {
    Bitmap bmp = null;
    if (path != null && w > 0 && h > 0) {
      BitmapFactory.Options op = new BitmapFactory.Options();
      op.inJustDecodeBounds = true;
      try {
        BitmapFactory.decodeFile(path, op);
        int srcW = op.outWidth;
        int srcH = op.outHeight;
        if (srcW > 0 && srcH > 0) {
          int scale = srcW * srcH / w / h;
          if (scale > 1) {
            scale = (int) Math.sqrt(scale);
            op.inJustDecodeBounds = false;
            op.inSampleSize = scale;
            bmp = BitmapFactory.decodeFile(path, op);
          } else {
            bmp = BitmapFactory.decodeFile(path);
          }
        }
      } catch (Exception e) {
        e.printStackTrace();
        bmp = null;
      } catch (OutOfMemoryError e) {
        e.printStackTrace();
        bmp = null;
      }
    }
    return bmp;
  }

  public static Bitmap downloadPic(String imageUrl) {
    return downloadPic(imageUrl, 5000, 10000);
  }

  private static Bitmap downloadPic(String imageUrl, int connectTimeout, int readTimeout) {
    URL url = null;
    HttpURLConnection conn = null;
    InputStream is = null;
    Bitmap bitmap = null;
    try {
      if (imageUrl != null) {
        url = new URL(imageUrl);
        conn = (HttpURLConnection) url.openConnection();
        conn.setConnectTimeout(connectTimeout);
        conn.setReadTimeout(readTimeout);
        conn.setDoInput(true);
        conn.connect();
        is = conn.getInputStream();
        bitmap = BitmapFactory.decodeStream(is);
      }
    } catch (FileNotFoundException e) {
      e.printStackTrace();
    } catch (IOException e) {
      e.printStackTrace();
    } catch (OutOfMemoryError e) {
      e.printStackTrace();
    } catch (Exception e) {
      e.printStackTrace();
    } finally {
      if (conn != null) {
        conn.disconnect();
        conn = null;
      }
      if (is != null) {
        try {
          is.close();
        } catch (IOException e) {
          e.printStackTrace();
        } finally {
          is = null;
        }
      }
    }
    // todo 因内网链接失效，暂用序号图表示全景瓦片图，等找到链接后更新恢复
    if (null == bitmap && null != imageUrl && imageUrl.contains("pos=")) {
      int n = imageUrl.indexOf("pos=") + 4;
      bitmap =
          getBitmapByText(
              200, 200, imageUrl.substring(n, n + 3), 50, Color.BLACK, Color.WHITE, 0, 0, true);
    }
    // end
    return bitmap;
  }

  public static Bitmap getBitmapByText(
      int width,
      int height,
      String content,
      float textSize,
      int textColor,
      int bgColor,
      int leftPadding,
      int topPadding,
      boolean isCenter) {
    Bitmap bmp = null;
    if (width <= 0 || height <= 0) {
    } else {
      if (content == null) {
        content = "";
      }
      TextPaint tp = new TextPaint();
      tp.setTextSize(textSize);
      bmp = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
      Canvas memCanvas = new Canvas(bmp);
      memCanvas.drawColor(bgColor);
      Paint paint = new Paint();
      paint.setAntiAlias(true);
      content = getMaxCharacterOfSingleLine(content, textSize, width - leftPadding * 2);
      paint.setTextSize(textSize);
      paint.setColor(textColor);
      int left = leftPadding;
      if (isCenter) {
        int length = (int) tp.measureText(content);
        left = (width - length) / 2;
      }
      memCanvas.drawText(content, left, textSize + topPadding, paint);
    }
    return bmp;
  }

  public static String getMaxCharacterOfSingleLine(String str, float textSize, int length) {
    if (str == null) {
      return "";
    } else {
      TextPaint tp = new TextPaint();
      tp.setTextSize(textSize);
      if (tp.measureText(str) <= length) {
        return str;
      } else {
        int num = 1;
        for (; num <= str.length(); num++) {
          String sub = str.substring(0, num);
          if (tp.measureText(sub + ELLIPSIS) >= length) {
            num--;
            break;
          }
        }
        num = Math.min(num, str.length());
        return str.substring(0, num) + ELLIPSIS;
      }
    }
  }
}
