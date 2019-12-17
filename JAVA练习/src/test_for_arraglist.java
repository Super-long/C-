import java.util.*;
import java.lang.*;

public class test_for_arraglist{
    public static void main(String[] args){
        //不指定类型默认为Object对象
        ArrayList<String> array = new ArrayList<String>();
        array.add("hello");
        array.add("world");
        array.add(1, "xx");
        array.remove("xxx");
        ArrayList<String> two = new ArrayList<String>();
        two.addAll(array);
        System.out.println(two.size());

        for(String x : array){
            System.out.printf(x);
        }

        /*Object[] str =  array.toAarray();
        for(Object y : str){
            System.out.printf((String)y);
        }*/

        System.out.println(array.get(0));
        System.out.println("hello world");
        have_implement T = ()->{System.out.println("");};
        T.show();
    }

}

interface have_implement{
    abstract public void show();
}
