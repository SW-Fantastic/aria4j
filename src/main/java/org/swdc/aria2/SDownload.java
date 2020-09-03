package org.swdc.aria2;

import org.swdc.aria2.impl.NativeImpl;

public class SDownload {

    private String ariaDownloadId;

    private long length;
    private long completeLength;
    private double downloadSpeed;
    private double uploadSpeed;
    private String fileName;
    private String fileLocation;

    private AriaSession session;

    public SDownload(String downloadId) {
        this.ariaDownloadId = downloadId;
    }

    public void setSession(AriaSession session) {
        this.session = session;
    }

    public double getDownloadSpeed() {
        if (!session.isClosed()) {
            NativeImpl.refreshDownload(this,this.ariaDownloadId,session.getPointerAddress());
        }
        return downloadSpeed;
    }

    public long getLength() {
        if (length == 0 && !session.isClosed()) {
            NativeImpl.refreshDownload(this,this.ariaDownloadId,session.getPointerAddress());
        }
        return length;
    }

    public double getUploadSpeed() {
        if (!session.isClosed()) {
            NativeImpl.refreshDownload(this,this.ariaDownloadId,session.getPointerAddress());
        }
        return uploadSpeed;
    }

    public String getAriaDownloadId() {
        return ariaDownloadId;
    }

    public long getCompleteLength() {
        if (!session.isClosed()) {
            NativeImpl.refreshDownload(this,this.ariaDownloadId,session.getPointerAddress());
        }
        return completeLength;
    }

    public String getFileName() {
        if (fileName == null && !session.isClosed()){
            NativeImpl.refreshDownload(this,this.ariaDownloadId,session.getPointerAddress());
        }
        return fileName;
    }

    public String getFileLocation() {
        if (fileLocation == null && !session.isClosed()){
            NativeImpl.refreshDownload(this,this.ariaDownloadId,session.getPointerAddress());
        }
        return fileLocation;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public void setAriaDownloadId(String ariaDownloadId) {
        this.ariaDownloadId = ariaDownloadId;
    }

    public void setCompleteLength(long completeLength) {
        this.completeLength = completeLength;
    }

    public void setDownloadSpeed(double downloadSpeed) {
        this.downloadSpeed = downloadSpeed;
    }

    public void setFileLocation(String fileLocation) {
        this.fileLocation = fileLocation;
    }

    public void setLength(long length) {
        this.length = length;
    }

    public void setUploadSpeed(double uploadSpeed) {
        this.uploadSpeed = uploadSpeed;
    }

    public void pause() {
        NativeImpl.pauseDownload(session.getPointerAddress(),this.ariaDownloadId);
    }

    public void unPause(){
        NativeImpl.unPauseDownload(session.getPointerAddress(),this.ariaDownloadId);
    }

    public void stop() {
        NativeImpl.stopDownload(session.getPointerAddress(),this.ariaDownloadId);
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (!(obj instanceof SDownload)) {
            return false;
        }
        SDownload download = (SDownload) obj;
        return download.getAriaDownloadId() == this.getAriaDownloadId();
    }

    @Override
    public int hashCode() {
        return (this.getAriaDownloadId() + "").hashCode();
    }
}
