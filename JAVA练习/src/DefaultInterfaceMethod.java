import java.lang.reflect.Array;
import java.util.*;
import static java.util.Comparator.comparing;
/*
* @ JDK8 之后引入了接口默认方法 且支持接口private方法 不用加default
* @
* */
public class DefaultInterfaceMethod {
    public static void main(String[] args){
        /*Ball ball = new Ball();
        Ball ba = new Ball();
        System.out.println(ball.lessthan(ba));*/

        /*Comparator<String> bylength1 = (s1, s2) -> s1.length() - s2.length();
        Comparator<String> bylength2 = StringOrder::bylength;
        String[] str = {"one", "two", "three"};
        Arrays.sort(str, String::compareTo);
        //当使用上面的写法的时候 相当于是一种语法糖*/

        List<Customer> list = new ArrayList<>(); //使用of会出现错误 因为不可变特性 循环会改变对象
        list.add(new Customer("li", "zhaolong", 21));
        list.add(new Customer("zhang", "siyao", 22));
        list.add(new Customer("xiao", "dindin", 23));
        Comparator<Customer> bylastname = comparing(Customer::getFirstname);
        //comparing方法返回一个比较器
        list.sort(bylastname.thenComparing(Customer::getLastbname).thenComparing(Customer::getZipcode));

        //list.forEach(System.out::println);

        five_ class_five = new five_();
        class_five.show();
        class_five.draw();
    }
}

class StringOrder{
    public static int bylength(String s1, String s2){
        return s1.length() - s2.length();
    }
}

interface Comparable_<T>{
    public int comparato(T that);

    default boolean lessthan(T that){ //默认接口不能直接变更数据状态
        int a = 5;
        return comparato(that) < 0;
    }

    private void submethod1(){
        int a = 5;
        System.out.println(5);
    }
}

class Ball implements Comparable_<Ball>{
    private int radius;

    @Override
    public int comparato(Ball ball) {
        return this.radius - ball.radius;
    }
}


class Customer {
    private String firstname;
    private String lastbname;
    private Integer zipcode;

    public Customer(String first, String Second, Integer code){
        this.firstname = first;
        this.lastbname = Second;
        this.zipcode = code;
    }

    @Override
    public String toString() {
        return String.format("%s %s : %d",firstname, lastbname, zipcode);
    }

    public String getFirstname(){
        return firstname;
    }

    public String getLastbname(){
        return lastbname;
    }

    public Integer getZipcode(){
        return zipcode;
    }
}

interface one_{
    public void show();
    default void draw(){
        System.out.println("one_ show");
    }
}

interface two_{
    public void show();
    default void draw(){
        System.out.println("two_ show");
    }
}

interface four_{
    public void show();
    default void draw(){
        System.out.println("four show");
    }
}

class three implements one_, two_{
    public void show(){
        System.out.println("hello world");
    }
    public void draw(){
        one_.super.draw();
    }
}

//如果父类中的方法与接口中默认方法或者抽象方法相同的话优先使用父类
class five_ extends three implements four_{

}