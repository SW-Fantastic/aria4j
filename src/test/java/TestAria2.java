import org.swdc.aria2.AriaSession;
import org.swdc.aria2.SDownload;
import org.swdc.platform.NativeLoader;

import java.io.File;
import java.util.List;

public class TestAria2 {

    public static void main(String[] args) throws Exception {
        NativeLoader loader = new NativeLoader(new File("shared"));
        loader.load("aria2");

        AriaSession session = new AriaSession();
        Thread thread = new Thread(() -> {
            try {
                Thread.sleep(800);
                session.addDownloadUrl("http://music.163.com/song/media/outer/url?id=33255251.mp3","music-sec.mp3",new File("./files"));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            while (!session.isClosed()) {
                List<SDownload> downloads = session.getDownloads();
                for (int idx = 0; idx < downloads.size();idx ++) {
                    try {
                        SDownload download = downloads.get(idx);
                        System.out.println("file: " + download.getFileName() + "  =>  " +(download.getCompleteLength() / (double)download.getLength()) * 100);
                    } catch (Exception e) {
                    }
                }
            }
        });
        thread.start();
        session.addDownloadUrl("http://music.163.com/song/media/outer/url?id=731379.mp3","music.mp3",new File("./files"));
        session.download();
        session.close();
    }

}
