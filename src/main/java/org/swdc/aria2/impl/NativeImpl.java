package org.swdc.aria2.impl;

import org.swdc.aria2.*;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class NativeImpl {

    private static Map<Long,AriaSession> pointerSessionMap = new ConcurrentHashMap<>();

    public static AriaSession getSession(long pointer) {
        return pointerSessionMap.get(pointer);
    }

    public static void addSessionImpl(AriaSession session) {
        pointerSessionMap.put(session.getPointerAddress(),session);
    }

    public static void onEvent(long sessionPointer,int eventType,String downloadId) {
        AriaSession session = pointerSessionMap.get(sessionPointer);
        DEventType type = DEventType.getType(eventType);
        AriaEvent event = new AriaEvent(session,type,downloadId);
        for (AriaEventListener listener: session.getListeners()) {
            listener.handle(event);
        }
    }

    /**
     * 移除session，在移除之前需要关闭它。
     * @param session 被移除的session
     */
    public synchronized static void finalizeSession(long session) {
        pointerSessionMap.remove(session);
    }

    /**
     * 初始化session，native实现，返回session的指针地址，提供native使用。
     * @return session的native地址
     */
    public synchronized static native long createSessionImpl();

    /**
     * 关闭session
     * @param sessionPointer session的指针
     */
    public synchronized static native void closeSession(long sessionPointer);

    /**
     * 添加目标url
     * @param url
     * @param name
     * @param pointer
     * @return
     */
    public synchronized static native boolean addUrl(String url,String name,String folder,long pointer);

    /**
     * 执行下载。
     * 调用native的run不停的执行下载动作，并且进行事件轮询
     * @param sessionPointer session的指针
     * @return session的下载的状态
     */
    public static native int doDownload(long sessionPointer);

    /**
     * 暂停的下载
     * @param sessionPointer 指针
     * @return
     */
    public synchronized static native int pauseDownload(long sessionPointer, String a2gid);

    /**
     * 继续被暂停的下载
     * @param sessionPointer 指针
     * @return
     */
    public synchronized static native int unPauseDownload(long sessionPointer, String a2gid);

    /**
     * 结束下载
     * @param sessionPointer 指针
     * @return
     */
    public synchronized static native int stopDownload(long sessionPointer, String a2gid);

    /**
     * 获取进行中的下载
     * @param sessionPointer
     * @return
     */
    public synchronized static native List<SDownload> getActiveDownloads(long sessionPointer);

    /**
     * 刷新下载信息
     * @param sDownloadId
     */
    public synchronized static native void refreshDownload(SDownload download,String sDownloadId, long sessionPointer);

}
