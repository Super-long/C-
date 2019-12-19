import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.UncheckedIOException;
import java.util.*;

public class unit_10_3 {
    public static void main(String[] args){
        FileUtil T = new FileUtil();
        try(T){// Try-With-Resources.
            T.open("input", fileInputStream ->{
                Scanner file = new Scanner(fileInputStream);
                while(file.hasNextLine()){
                    System.out.println(file.nextLine());
                }
            });
        }catch (Throwable ex){
            ex.printStackTrace();
        }
    }
}

interface handing_stream{
    void handing(FileInputStream para);
}

class FileUtil implements AutoCloseable{
    FileInputStream x;
    public void open(String str, handing_stream para)
            throws UncheckedIOException {
        try{
            x = new FileInputStream(str);
            para.handing(x);
        }catch (IOException ex){
            ex.printStackTrace();
            Throwable t = ex.fillInStackTrace();
            throw (UncheckedIOException)t;
        }
    }

    @Override
    public void close() throws Exception{
        x.close();
        System.out.println("Resource released.");
    }
}