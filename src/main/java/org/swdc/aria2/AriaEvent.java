package org.swdc.aria2;

import java.util.List;

public class AriaEvent {

    private DEventType state;

    private AriaSession session;

    private SDownload download;

    public AriaEvent(AriaSession session, DEventType state,String downloadId) {
        this.session = session;
        this.state = state;
        synchronized (AriaSession.class) {
            List<SDownload> downloads = session.getDownloads();
            for (int idx = 0; idx < downloads.size(); idx++) {
                if (downloads.get(idx).getAriaDownloadId().equals(downloadId)) {
                    download = downloads.get(idx);
                    break;
                }
            }
        }
    }

    public SDownload getDownload() {
        return download;
    }

    public AriaEvent(DEventType state) {
        this.state = state;
    }

    public AriaSession getSession() {
        return session;
    }

    public DEventType getState() {
        return state;
    }

    public void setSession(AriaSession session) {
        this.session = session;
    }

    public void setState(DEventType state) {
        this.state = state;
    }
}
