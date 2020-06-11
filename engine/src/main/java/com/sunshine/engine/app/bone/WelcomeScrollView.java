/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.app.bone;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.VelocityTracker;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.Scroller;

import com.sunshine.engine.util.callback.WelcomeOnScrollCallback;


public class WelcomeScrollView extends ViewGroup {
	private WelcomeOnScrollCallback mListener = null;
	private int childWidth = 0;//每个子页面的宽度
	public int getChildWidth(){
		return childWidth;
	}

	private int maxOffset = 0;//滑动到边界，最大移动距离
	private void setMaxOffset(){
		maxOffset = childWidth/6;
	}
	
	private Scroller mScroller = null;//计算滚动
	private VelocityTracker mVelocityTracker = null;//计算速度

	private static final int mDefaultScreen = 0;//默认的第一屏
	private int mCurScreen = mDefaultScreen;//当前屏下标

	private static final int SNAP_VELOCITY = 600; // 默认的滚动速度，之后用于和手指滑动产生的速度比较，获取屏幕滚动的速度
	private float mLastMotionX; // 手指移动的时候，或者手指离开屏幕的时候记录下的手指的横坐标

	public WelcomeScrollView(Context ct) {
		super(ct);
		init(ct);
	}

	public WelcomeScrollView(Context ct, AttributeSet attrs, int defStyle) {
		super(ct, attrs, defStyle);
		init(ct);
	}

	public WelcomeScrollView(Context ct, AttributeSet attrs) {
		this(ct, attrs, 0);
		init(ct);
	}
	
	private void init(Context ct){
		mScroller = new Scroller(ct);
	}

	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
		super.onMeasure(widthMeasureSpec, heightMeasureSpec);
		int wMode = MeasureSpec.getMode(widthMeasureSpec);
		int hMode = MeasureSpec.getMode(heightMeasureSpec);
		if((wMode==MeasureSpec.EXACTLY)&&(hMode==MeasureSpec.EXACTLY)){
			int w = MeasureSpec.getSize(widthMeasureSpec);
			final int count = getChildCount();
			for (int i = 0; i < count; i++) {
				getChildAt(i).measure(widthMeasureSpec, heightMeasureSpec);
			}
//			scrollTo(mCurScreen * w, 0);
			snap2DestScreen(mCurScreen);
		}
	}

	@Override
	protected void onLayout(boolean changed, int l, int t, int r, int b) {
		if (changed) {
			int left = 0;
			int childCount = getChildCount();
			childWidth = r - l;
			setMaxOffset();
			for (int i = 0; i < childCount; i++) {
				RelativeLayout v = (RelativeLayout) getChildAt(i);
				if (v.getVisibility() != View.GONE) {
					v.layout(left, 0, left + childWidth, v.getMeasuredHeight());
					left = left + childWidth;
				}
			}
			snap2DestScreen(mCurScreen);
		}
	}

	/**
	 * 让界面跟着手指移动到手指移动的地点
	 */
	private void snapToDestination() {
		int destScreen = (getScrollX() + childWidth / 2) / childWidth;
		snap2DestScreen(destScreen);
	}

	/**
	 * 滚动到指定screen
	 *
	 * @param destScreen
	 */
	public void snap2DestScreen(int destScreen) {
		destScreen = Math.max(0, Math.min(destScreen, getChildCount() - 1));// 获取要滚动到的目标screen
		if (getScrollX() != (getWidth() * destScreen)) {
			final int delta = destScreen * getWidth() - getScrollX(); // 获取屏幕移到目的view还需要移动多少距离
			mScroller.startScroll(getScrollX(), 0, delta, 0, Math.abs(delta) * 2);// 使用Scroller辅助滚动，让滚动变得更平滑
			mCurScreen = destScreen;
			invalidate();// 重绘界面
		}
	}

	@Override
	public void computeScroll() {
		if(mScroller.computeScrollOffset()){
			scrollTo(mScroller.getCurrX(), mScroller.getCurrY());
			invalidate();
		}
	}
	/**
	 * 在边界处滚动，不允许滚出指定距离
	 * @param d
	 */
	private int getOffset(int d){
		int D = Math.abs(d);
		if(D>=maxOffset){
			D = maxOffset;
			d = maxOffset*(d>0?1:-1);
		}
		return d;
	}
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (mVelocityTracker == null) {
			mVelocityTracker = VelocityTracker.obtain();
		}
		mVelocityTracker.addMovement(event);

		final int action = event.getAction();
		final float x = event.getX();

		switch (action) {
			case MotionEvent.ACTION_DOWN://终止滚动;获取最后一次事件的x值
				if(!mScroller.isFinished()){
					mScroller.abortAnimation();
				}
				mLastMotionX = x;
				break;
			case MotionEvent.ACTION_MOVE://1,获取最后一次事件的x值2,滚动到指定位置
				int deltaX = (int) (mLastMotionX - x );
				mLastMotionX = x;
				int toX = getScrollX() + deltaX;//x方向目标位置
				int totalLen = childWidth*(getChildCount()-1);
				if(toX>=0&&toX<totalLen){//在内容区域，跟随手指移动
					scrollBy(deltaX, 0);
				}else if(getScrollX()<=0&&toX<0){
					int l = 0*childWidth;
					int n = 1 + 3*Math.abs(getScrollX() - l)/maxOffset;
					toX = getScrollX() + deltaX/n;
					scrollTo(l + getOffset(toX - l), 0);
				}else if(toX>=0&&toX>totalLen){
					int n = 1 + 3*Math.abs(getScrollX() - totalLen)/maxOffset;
					toX = getScrollX() + deltaX/n;
					scrollTo(totalLen + getOffset(toX - totalLen), 0);
				}
				break;
			case MotionEvent.ACTION_UP://计算手指移动的速度，并判断滚动到哪个 screen
				mVelocityTracker.computeCurrentVelocity(1000);//设置属性为计算1秒运行多少个像素
				int velocityX = (int) mVelocityTracker.getXVelocity();
				if(velocityX > SNAP_VELOCITY && mCurScreen > 0){//速度>0，向右。把左边的划过来
					int target = mCurScreen - 1;
					snap2DestScreen(target);
				}else if(velocityX < -SNAP_VELOCITY && mCurScreen < (getChildCount() - 1)){//速度<0，向左。把右边的划过来
					int target = mCurScreen + 1;
					snap2DestScreen(target);
				}else{//速度小于换屏速度，回弹到当前屏
					snapToDestination();
				}
				if(mVelocityTracker != null){
					mVelocityTracker.recycle();
					mVelocityTracker = null;
				}
				break;
			case MotionEvent.ACTION_CANCEL:
				break;
			default:
				break;
		}
		return true;
	}

	public void setOnScrollListener(WelcomeOnScrollCallback listener) {
		mListener = listener;
	}
	@Override
	protected void onScrollChanged(int x, int y, int oldX, int oldY) {
		super.onScrollChanged(x, y, oldX, oldY);
		if (mListener != null) {
			float percent = 0;
			int len = getChildWidth() * (getChildCount() - 1);
			if (len > 0) {
				percent = Math.abs((float) x / len);
				if (percent > 1) {
					percent = 2 - percent;
				}
			}
			mListener.onChanged(percent);
		}
	}
}