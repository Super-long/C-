import java.time.Period;
import java.util.*;
import java.util.function.Function;

public class MethodReference {
    public static void main(String[] args){
        List<String> name = List.of(args);
        //为什么要传构造函数　传一个类型不好吗
        List<person> per = methodReference.map(name, person::new);//Constructor Reference
        per.forEach(System.out::println);
        String str = "asdasd";
        See(str, str);
        Test two = new Test() {
            @Override
            public String apr(String str) {
                return str;
            }
        };
        methodReference.exchange(str, namse -> String.format("name : %s", namse));
        methodReference.exchange(str, two::apr);

    }

    static
    <T, R> void See(T one, R o){
        //R x = new R(); //为什么这样做是不可以的 知识储备还不够 (泛型没有C++的强大)
        System.out.println(one);
    }
}

interface Test{
    String apr(String str);
}

class person{
    String name;

    public person(String name){ //默认返回一个this
        this.name = name;
    }

    @Override
    public String toString(){
        return "Person : " + "name " + name;
    }
}


// Function中 P表示形参 R表示返回值
class methodReference{
    static <P, R> List<R> map(List<P> l, Function<P,R> mapper){//类似于一个函数对象
        List<R> mapped = new ArrayList<>();
        for (int i = 0; i < l.size(); i++) {
            mapped.add(mapper.apply(l.get(i)));//apply方法是便是lambda表达式的抽象
        }
        return mapped;
    }

    static <P, R> void exchange(P one, Function<P, R> two){
        System.out.println(two.apply(one));
    }
}
