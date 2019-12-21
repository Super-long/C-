import java.util.*;

public class unit_12 {
    public static void main(String[] args){
        String[] arr = {"asd","aaa","ommom"};
        Arrays.sort(arr, (name1, name2) -> name1.length() - name2.length());
        //Arrays.sort(arr, String::compareTo);
        List<String> list = new ArrayList<>();
        for(String T : arr)list.add(T);
        list.sort(String::compareTo);//这么写就跟函数指针一样
        //list.forEach((name) -> System.out.println(name));

        //of方法为了生成一个不可变的对象(仅长度) 如果元素是个类的话显然可以变
        List<String> names = List.of("one","two","three", "one");

        Set se = new HashSet();
        names.forEach( name -> se.add(name));
        se.forEach(System.out::println);

        new HashSet<>(names).forEach(System.out::println);
        System.out.println("-----------");
        new ArrayDeque<>(names).forEach(System.out::println);

        /*hello TT = new hello();
        TT.r1.run();
        TT.r2.run();

        hello2 TTT = new hello2();
        TTT.r1.run();
        TTT.r2.run();*/

        Runnable run = new Runnable() {
            @Override
            public void run() {
                StringBuilder T = new StringBuilder();
                T.append("asdasd");
                for(String name : list){
                    name = "sd ";
                    System.out.println(name);
                }
            }
        };
        int i = 1;

        Runnable Run = () -> {//JDK8以后可以在匿名类内部基于使用非final的局部变量 但需要等效于final
            //i++; Lambda表达式禁止修改捕获的变量 是为了进一步支持并行程序的设计
            for(String T : list){
                System.out.println(T);
            }
            list.add("asd");
        };
        //Run.run();
        //System.out.println("-----------");
        //Run.run();
    }
}

class hello{
    /*
    * @执行显示不是"Hello world"的原因是因为 this和toString的实例其实是匿名对象
    * */
    Runnable r1 = new Runnable() {
        @Override
        public void run() {
            System.out.println(this);
        }
    };

    Runnable r2 = new Runnable() {
        @Override
        public void run() {
            System.out.println(toString());
        }
    };

    @Override
    public String toString(){
        return "hello world";
    }
}

class hello2{
    //也就是说Lambda其实和匿名对象不是一个东西
    Runnable r1 = () -> System.out.println(this);
    Runnable r2 = () -> System.out.println(toString());

    @Override
    public String toString(){
        return "Hello world";
    }
}

@FunctionalInterface //声明本接口为函数接口 不是的话则会报错
interface Fun<P, R>{
    P apply(R name1, R name2);
}