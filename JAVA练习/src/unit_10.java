import java.io.*;
import java.lang.reflect.Member;
import java.util.*;

public class unit_10 {
    public static void main(String[] args) throws IOException{
        /*IO.dump(
                new FileInputStream(args[0]),
                new FileOutputStream(args[1])
        );
        Scanner in = new Scanner(System.in);
        System.out.println(); //操作的数据会自动转换成bytes数组的数据*/
        member[] arr = {
                    new member("001", "input", 25),
                    new member("002", "input", 25),
                    new member("003", "input", 25)
        };

        //这两个算是输入输出流中的了
        FileReader T = new FileReader(args[0]);
        FileWriter TT = new FileWriter(args[1]);
        //Read(T, TT);
        //arr[0].save();
        //arr[1].Data_save();
        //System.out.println(arr[0].load("input"));

        FileInputStream R = new FileInputStream(args[0]);
        FileOutputStream RR = new FileOutputStream(args[1]);
        Exchange_encode Ee = new Exchange_encode();
        Ee.dump(R, RR, "GB2312");
    }

    public static void Read(Reader src, Writer ou) throws IOException{ //可以读取字符串
        try(Reader input = src ; Writer output = ou){
            char[] data = new char[1024]; //算是字符处理类
            int length = 0;
            while((length = input.read(data)) != -1){
                System.out.println(data);
            }
        }
    }
}

class IO{
    public static void dump(InputStream input, OutputStream ouput)
            throws IOException {//dest 目的
        try(InputStream src = input; OutputStream dest = ouput){ //自动关闭资源
            byte[] data = new byte[1024];
            int length = 0;
            while((length = src.read(data)) != -1){
                ouput.write(data, 0 , length); //会覆盖前面的数据
            }
        }
    }
}

/**
 *  为了能够使用这些串流处理装饰器
 *  @ ObjectInputStream ObjectOutputStream 改变发出时机 减少读写磁盘数量
 *  @ DataOutputStream DataOutputStream 可操作对象 文件小 读取次数多
 *  @ BufferedInputStream BufferOutputStream 可操作对象 文件大(写入一整个对象) 读取次数小
 *  这些串流处理器的参数为 InputStream OutputStream
 *  InputStream OuputStream 实际上处理的是字节数据 但我们实际需要的是字符数据
 */
//

class member implements Serializable{
    private String Number;
    private transient String name; //如果加上transient(短暂的) 则object不读取此成员+
    private int age;

    public member(String a, String b, int c){
        this.Number = a;
        this.name = b;
        this.age = c;
    }

    @Override
    public String toString(){
        return String.format("name : %s , number : %s , age : %d", name, Number, age);
    }

    public void save() throws IOException{
        try(ObjectOutputStream ouput = new ObjectOutputStream(new FileOutputStream(name))){
            System.out.println(name + " 开始写入");
            ouput.writeObject(this); //写入一个对象
        }
    }

    public static member load(String number)
        throws IOException, ClassNotFoundException{
        member obj;
        try(ObjectInputStream input = new ObjectInputStream((new FileInputStream(number)))){
            obj = (member)input.readObject();
        }
        return obj;
    }

    public void Data_save() throws IOException{
        try(DataOutputStream output = new DataOutputStream(new FileOutputStream(name))){
            System.out.println(name + "Data 开始写入");
            output.writeUTF(name); //
            output.writeUTF(Number);
            output.writeInt(age);
        }
    }
}

class Exchange_encode{
    public static void dump(Reader src, Writer dest) throws IOException{
        try(src; dest){
            char[] data = new char[1024];
            int length = 0; //
            while ((length = src.read(data)) != -1){
                System.out.println(length);
                dest.write(data, 0, length);
            }
        }
    }

    public static void dump(InputStream input, OutputStream ouput, String encode)
            throws IOException{
        dump(
                new InputStreamReader(input, encode),
                new OutputStreamWriter(ouput, encode)
        );
    }

    public static void dump(InputStream input, OutputStream ouput)
            throws IOException{
        dump(input, ouput, System.getProperty("file.encoding"));
    }
}

