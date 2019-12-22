import java.util.*;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Collectors;


public class FunctionalANdStream {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        //Optional<String> str = getNickname(input.next());
        //System.out.println(str.orElse("error operations.."));
        String nickname = "error operations.";

        List<String> list = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            list.add("one");
        }
        //filter -> 过滤器
        Optional<String> first = list.stream().filter( a -> a.equals("one")).findFirst();
        if(first.isPresent()){
            nickname = first.get();
        }
        //System.out.println(nickname);

        /*Test_Functional_API x = new Test_Functional_API();
        x.con(name -> System.out.printf("name"));
        x.pre(name -> {
            if(name == "hello") return true;
            return false;
        });
        x.upp(String::new);*/

        List<Temp> T = List.of(
                new Temp("one", 1),
                new Temp("two", 2),
                new Temp("three", 3)
        );

        List<String> list2 = new ArrayList<>();
        for(Temp x : T){
            if(x.getAge() >= 2){
                list2.add(x.getone().toUpperCase());
            }
        }

        String s = T.stream()
                .filter(name -> name.getAge() >= 2)
                .map(Temp::getone)
                .map(String::toUpperCase) //像是管道一样 很有意思
                .reduce((total, obj) -> total + obj) //用在数字效果更好
                .get();
        System.out.println(s);
                //.collect(Collectors.toList())
                //.forEach(System.out::println);
        //可以打印一下看看 确实是后续操作要求时才会动手处理下一笔数据 这样就有了很多的优化空间
        //对于有条件的读取文件来说有很大的用处 就不需要一次全读完 而是有需要的时候读取 条件达成则关闭
    }

    static Optional<String> getNickname(String key){
        Map<String, String> nickname = Map.of(
                "lizhaolong", "jiaolong",
                "hello", "world",
                "world", "hello");
        String name = nickname.get(key);
        return name == null ? Optional.empty() : Optional.of(name);
    }

}

class Test_Functional_API{
    void upp(Supplier para){
        System.out.println(para.get());
    }

    void pre(Predicate para){
        String str = "sda";
        if(para.test(str)) System.out.println("ok");
        else System.out.printf("okok");
    }

    <T, R>
    R fun(List<T> list , Function<T, R> para){
        String st = "asd";//如何保证传入的是一个T类型
        return para.apply(list.get(0));
    }

    void con(Consumer para){
        para.accept("asd");
    }
}

class Temp{
    private String one;
    private Integer age;

    Temp(String T, Integer age){
        this.one = T;
        this.age = age;
    }

    public String getone(){
        System.out.println("name");
        return one;
    }

    public Integer getAge(){
        System.out.println("age");
        return age;
    }

    @Override
    public String toString() {
        return String.format("name : , age : %d", one, age);
    }
}