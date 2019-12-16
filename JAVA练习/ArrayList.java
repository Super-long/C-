import java.util.*;
import static java.lang.System.out;
import static java.lang.System.in;

//java中所有的类追溯至最上层父类一定是java.lang.Object 

class Arraylist{
    private int num;
    private Object[] list;
    Arraylist(int capacity){
        list = new Object[capacity];
    }

    Arraylist(){
        this(16); //初始容量默认为16
    }

    public void add(Object o){
        if(num == list.length){
            list = Arrays.copyOf(list, num * 2); //这个Arrays类有点diao
        }
        list[num++] = o;
    }

    public int size(){
        return num;
    }
}

public class ArrayList{
    //许多方法传入对象 默认调用toString 比如说println 
    static public void main(String[] args){
        String str = new String("hello world");
        out.println(str.toString());
        if(str instanceof Object)//显然C++中不需要这个运算符
            out.println("yes");
    }
}

/*hashcode是一种编码方式，在Java中，
每个对象都会有一个hashcode，Java可以通过这个hashcode来识别一个对象。*/