import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;
import java.lang.*;

public class unit_8{
    public static void main(String args[]){
        DoSomething TT = new DoSomething();
        TT.Showall(); //
        assert false : "test of this"; //编译时加上 -ea 才会默认执行这个关键字 一般不执行
        //TestOfStackTrace();
        //test(5);
    }

    public static int test(int flag){
        try {
            if(flag == 1){
                //return 1;
                throw new FileNotFoundException("hello world");
            }
        } catch (Exception ex){
            System.out.println("sucessful.");
        } finally {
            System.out.println("processing finally module.");
        }
        return 5;
    }

    public static void TestOfStackTrace(){
        Scanner input = new Scanner(System.in);
        String str = input.nextLine();
        try{
            one T = new one();
            String file = T.Readline(str);
            System.out.println(file);
        }catch (FileNotFoundException ex){
            System.out.println("not find file name");
            ex.printStackTrace(); //强大的函数
        }
        System.out.println("str = " + str);
    }
}

class one{
    public static String Readline(String args)
            throws FileNotFoundException{
        //线程安全可以使用StringBuffer类 接口差不多 单线程StringBuilder没有同步上的消耗 更快
        //java打开一个文件是如此的方便
        StringBuilder T = new StringBuilder();
        //其实也可以在try中扔一个对象 也可以进行自动关闭资源 JDK9以后支持
        try(Scanner text = new Scanner(new FileInputStream(args))){ //这样可以自动尝试关闭资源而不用写finally
            while(text.hasNext()){
                T.append(text.nextLine()).append('\n');
            }
        }catch (FileNotFoundException ex){ //自动关闭资源的时候也可以catch一下 看看栈追踪信息
            ex.printStackTrace();
            throw ex; //也可以先做一些处理再抛出这个错误 异常再抛出
            //重抛异常的追踪堆栈起点 仍然是异常的发生根源
            //或者使用 ex.printStackTrace() 这样会将起点设置为重抛异常的地方
        }
        //text.close(); //重复关闭好像被优化掉了 有点秀
        return T.toString();
    }

    public static String readline(String args) {
        StringBuilder T = new StringBuilder();//非线程安全
        //线程安全可以使用StringBuffer类 接口差不多 单线程StringBuilder没有同步上的消耗 更快
        Scanner text = null;
        try{
            text = new Scanner(new FileInputStream(args));
            while(text.hasNext()){
                T.append(text.nextLine()).append('\n');
            }
        }catch (FileNotFoundException ex){
            ex.printStackTrace();
        }finally {
            text.close();
        }
        return T.toString();
    }
}

class Resourse implements AutoCloseable{
    void dosome(){
        System.out.println("do something.");
    }

    @Override
    public void close() throws Exception {
        System.out.println("资源已关闭");
    }
}

class DoSomething{
    public static void Showall(){
        try(Resourse res = new Resourse()){
            res.dosome();
        }catch (Exception ex){
            ex.printStackTrace();
        }
    }
}

/*class two extends one{
    public static String Readline(String args)
        throws FileNotFoundException { //不能抛出这个异常如果使用了catch会报错

    }
}*/

class NotchexkException extends RuntimeException{
    NotchexkException(String args){
        super(args);
    }
}

/*
* @ java的异常对象有一套继承体系
* @　一般来说继承于RuntimeException的错误我们认为是程序没有做好检查　修改程序就好
* @ 而在实现某些方法的时候 某些条件的成立会引发异常 且客户端有能力处理异常
*   或函数内部不清楚如何处理异常 这是可强制客户端接catch异常 不然无法过编译
* @ 非受检异常 认为客户调用方法的时机错了
* @ 受检异常   客户端有能力处理异常 强制客户端catch异常
* @ 当使用继承的时候 若父类抛出异常
*   -不声明throws任何异常
*   -throws父类方法中的某些异常
*   -throws父类方法中的声明异常的子类
*       不可以
*   -throws父类方法中没有的异常
*   -throws父类方法中异常的父类
* */
