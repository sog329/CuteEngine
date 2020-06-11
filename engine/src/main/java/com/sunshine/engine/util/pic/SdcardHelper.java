/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.pic;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;

import java.io.File;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by Jack on 16/1/4.
 */
public class SdcardHelper {
    private static Map<String, CacheInfo> mMapFolder = new HashMap<String, CacheInfo>();

    public static String getFolderPath(String folderName) {
        File file = Environment.getExternalStorageDirectory();
        String folderPath = file.getAbsolutePath() + File.separator + folderName;
        return folderPath;
    }

    public static void addFolderName(String id, String folderName, int maxNumber) {
        addFolderPath(id, getFolderPath(folderName), maxNumber);
    }

    public static void addFolderPath(String id, String folderPath, int maxNumber) {
        synchronized(mMapFolder) {
            if (checkFolder(folderPath)) {
                CacheInfo info = new CacheInfo();
                info.setFolderPath(folderPath);
                if (maxNumber < 1) {
                    maxNumber = 1;
                }
                info.setMaxNumber(maxNumber);
                mMapFolder.put(id, info);
            }
        }
        cleanFolder(id);
    }

    public static boolean hasSd() {
        return Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED);
    }

    public static String toHashCode(String imageUrl) {
        if (imageUrl == null) {
            return null;
        }
        int seed = 131;
        int hash = 0;
        int urlSize = imageUrl.length();
        for (int i = 0; i < urlSize; i++) {
            hash = (hash * seed) + imageUrl.charAt(i);
        }
        int result = hash & 0x7FFFFFFF;
        return String.valueOf(result);
    }

    /**
     * 路径名会跟scale相乘
     *
     * @param picId
     * @param picUrl
     * @param w
     * @param h
     * @param scale
     *
     * @return
     */
    private static String getImageCachePicUrl(String picId, String picUrl, int w, int h, int scale) {
        StringBuilder sb = new StringBuilder();
        String folderPath = null;
        synchronized(mMapFolder) {
            if (mMapFolder.get(picId) != null) {
                folderPath = mMapFolder.get(picId).getFolderPath();
            }
            if (!checkFolder(folderPath)) {
                folderPath = null;
            }
        }
        if (folderPath != null) {
            String hashUrl = toHashCode(picUrl);
            sb.append(folderPath);
            sb.append(File.separator);
            sb.append(hashUrl);
//            sb.append("_").append(w * scale).append("*").append(h * scale);
        }
        return sb.toString();
    }

    //    public static void removeImageFromSd(String picUrl) {
    //        if (mMapFolder != null) {
    //            if (picUrl != null && hasSd()) {
    //                String url = getImageCachePicUrl(picUrl);
    //                File file = new File(url);
    //                if (file.exists()) {
    //                    file.delete();
    //                    file = null;
    //                }
    //            }
    //        }
    //    }

    public static Bitmap getImageFromSd(String picId, String picUrl, int w, int h, int scale) {
        if (mMapFolder.get(picId) == null || picUrl == null || !hasSd()) {
            return null;
        } else {
            Bitmap bmp = null;
            try {
                String url = getImageCachePicUrl(picId, picUrl, w, h, scale);
                if (url != null && !url.isEmpty()) {
                    BitmapFactory.Options opts = null;
                    if (scale != 1) {
                        opts = new BitmapFactory.Options();
                        opts.inSampleSize = scale;
                    }
                    bmp = BitmapFactory.decodeFile(url, opts);
                }
            } catch (OutOfMemoryError e) {
                if (bmp != null) {
                    if (!bmp.isRecycled()) {
                        bmp.recycle();
                    }
                    bmp = null;
                }
            } catch (Exception e) {
                if (bmp != null) {
                    if (!bmp.isRecycled()) {
                        bmp.recycle();
                    }
                    bmp = null;
                }
            }
            return bmp;
        }
    }

    public static boolean saveImageToSd(Bitmap bmp, String picId, String picUrl, int w, int h, int scale) {
        boolean b = false;
        if (hasSd() && bmp != null) {
            String imagePath = getImageCachePicUrl(picId, picUrl, w, h, scale);
            if (imagePath != null) {
                String folderPath = null;
                synchronized(mMapFolder) {
                    if (mMapFolder.get(picId) != null) {
                        folderPath = mMapFolder.get(picId).getFolderPath();
                    }
                }
                if (folderPath != null) {
                    try {
                        File f = new File(imagePath);
                        boolean clean = true;
                        if (f.exists()) {
                            clean = f.delete();
                        }
                        if (clean) {
                            FileOutputStream out = null;
                            try {
                                if (f.createNewFile()) {
                                    out = new FileOutputStream(f);
                                    b = bmp.compress(Bitmap.CompressFormat.JPEG, 100, out);
                                    out.flush();
                                }
                            } catch (Exception e) {
                            } finally {
                                if (out != null) {
                                    try {
                                        out.close();
                                    } catch (Exception e) {
                                    } finally {
                                        out = null;
                                    }
                                }
                            }
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }
        return b;
    }

    private static boolean checkFolder(String folderPath) {
        boolean b = false;
        synchronized(mMapFolder) {
            try {
                if (folderPath != null && hasSd() && !folderPath.endsWith(File.separator)) {
                    File dir = new File(folderPath);
                    if (dir.exists()) {
                        b = true;
                    } else {
                        b = dir.mkdirs();
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return b;
    }

    private static void cleanFolder(String picId) {
        String folderPath = null;
        int max = 0;
        synchronized(mMapFolder) {
            if (mMapFolder.get(picId) != null) {
                folderPath = mMapFolder.get(picId).getFolderPath();
                max = mMapFolder.get(picId).getMaxNumber();
            }
        }
        if (folderPath != null) {
            File root = new File(folderPath);
            File[] files = root.listFiles();
            if (files != null && files.length > max) {
                final List<FileInfo> lst = new ArrayList<FileInfo>();
                for (File file : files) {
                    FileInfo info = new FileInfo();
                    info.setFilePath(file.getAbsolutePath());
                    info.setCreateTime(file.lastModified());
                    if (lst.size() == 0) {
                        lst.add(info);
                    } else {
                        int deleteNum = max / 2;
                        if (deleteNum < 1) {
                            deleteNum = 1;
                        }
                        // 如果比队列中最后的最新的还新
                        if (lst.get(lst.size() - 1).getCreateTime() <= info.getCreateTime()) {
                            // 如果队列已满，不用再插入次队列
                            if (lst.size() == deleteNum) {
                                continue;
                            } else {
                                lst.add(info);
                            }
                        } else {
                            for (int i = lst.size() - 1; i > -1; i--) {
                                if (lst.get(i).getCreateTime() > info.getCreateTime()) {
                                    lst.add(i, info);
                                    break;
                                }
                            }
                            if (lst.size() > deleteNum) {
                                lst.remove(lst.size() - 1);
                            }
                        }
                    }
                }
                if (lst.size() > 0) {
                    Runnable runnable = new Runnable() {
                        @Override
                        public void run() {
                            try {
                                for (int i = 0; i < lst.size(); i++) {
                                    File file = new File(lst.get(i).getFilePath());
                                    file.delete();
                                }
                            } catch (Exception e) {
                            }
                        }
                    };
                    new Thread(runnable).start();
                }
            }
        }
    }
}
