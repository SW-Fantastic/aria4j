package org.swdc.aria2;

import org.swdc.aria2.impl.NativeImpl;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class AriaSession implements AutoCloseable {

    private long pointerAddress = -1;

    private List<SDownload> downloads;

    private boolean closed = false;

    private List<AriaEventListener> listeners = new ArrayList<>();

    public AriaSession() {
        pointerAddress = NativeImpl.createSessionImpl();
        NativeImpl.addSessionImpl(this);
        this.addListener(e -> {
            if (e.getState() == DEventType.COMPLETE) {
                e.getDownload().stop();
                downloads.remove(e.getDownload());
            }
        });
    }

    public boolean addDownloadUrl(String url,String fileName, File folder) {
        if (this.closed) {
            throw new RuntimeException("session has closed");
        }
        return NativeImpl.addUrl(url,fileName,folder.getAbsolutePath(),pointerAddress);
    }

    public void download() {
        if (this.closed) {
            throw new RuntimeException("session has closed");
        }
        NativeImpl.doDownload(this.pointerAddress);
    }

    public List<AriaEventListener> getListeners() {
        if (this.closed) {
            throw new RuntimeException("session has closed");
        }
        return listeners;
    }

    public List<SDownload> getDownloads() {
        if (this.closed) {
            throw new RuntimeException("session has closed");
        }
        if (this.downloads == null || this.downloads.isEmpty()) {
            this.downloads = NativeImpl.getActiveDownloads(this.pointerAddress);
            for (SDownload item: downloads) {
                item.setSession(this);
            }
            return downloads;
        }
        List<SDownload> downloads = NativeImpl.getActiveDownloads(this.pointerAddress);
        for (int idx = 0; idx < downloads.size();idx++) {
            if (!this.downloads.contains(downloads.get(idx))) {
                SDownload item = downloads.get(idx);
                item.setSession(this);
                this.downloads.add(item);
            }
        }
        return this.downloads;
    }

    public void addListener(AriaEventListener listener) {
        if (this.closed) {
            throw new RuntimeException("session has closed");
        }
        this.listeners.add(listener);
    }

    public long getPointerAddress() {
        if (this.closed) {
            throw new RuntimeException("session has closed");
        }
        return pointerAddress;
    }

    @Override
    public void close() {
        if (this.closed) {
            throw new RuntimeException("session has closed");
        }
        closed = true;
        NativeImpl.closeSession(pointerAddress);
        NativeImpl.finalizeSession(this.pointerAddress);
    }

    public synchronized boolean isClosed() {
        return closed;
    }

}
