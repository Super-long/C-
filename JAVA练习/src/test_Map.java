import javax.imageio.ImageTranscoder;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Array;
import java.util.*;

public class test_Map {
    public static void main(String[] args)
            throws IOException {
        Map<String, String> messages = new TreeMap<>((s1,s2) -> s1.compareTo(s2));
        messages.put("austin", "hello");
        messages.put("Moncia", "world");
        Scanner input = new Scanner(System.in);
        String str = messages.get(input.next());
        System.out.println(str);
        System.out.println(messages); //证明Map重载了Tostring()方法 有点意思
        Properties props = new Properties();/*
        props.setProperty("username", "justin");
        props.setProperty("password", "123456");
        System.out.println(props.getProperty("username"));
        System.out.println(props.getProperty("password"));*/

        //使用loadFromXML()方法可以加载 .xml文档
        props.load(new FileInputStream(args[0]));//throws IOException
        //这样可以加载 .properties 后缀文件中的内容
        System.out.println(props.getProperty("username"));

        show();

        //Map的keyset()方法返回一个set对象 values()方法返回一个Collection对象
        messages.keySet().forEach(key -> System.out.println(key));
        messages.values().forEach(value -> System.out.println(value));
        messages.forEach(
                (key, value) -> System.out.printf("key : %s . value : %s%n", key, value)
        );
        foreach(messages.entrySet()); //返回一个Set对象 其中元素是 Map.Entry<String, String>

        List<String> list = new LinkedList<>();
        for (int i = 0; i < 5; i++) {
            list.add("hello");
        }
        test(list);
    }

    static void show(){
        Properties T = System.getProperties();
        System.out.println(T.getProperty("java.version"));
        //java.class.path 可访问java包的路径
    }

    static void foreach(Iterable<Map.Entry<String ,String>> args){
        for (Map.Entry<String, String> entry : args){
            System.out.printf("%s %s%n",entry.getKey(), entry.getValue());
        }
    }

    static void test(List list){
        //类似与一个对象的视图
        List<String> unmodifiablename = Collections.unmodifiableList(list);
        System.out.println(unmodifiablename.get(0));
        list.add("asdasd");
        /*System.out.println(list.size());
        System.out.println(unmodifiablename.size());*/

        //test of List.of() 与 asList 创建不可变对象
        List<String> T = List.of("hello", "world");

        MyList TTT = new MyList("one", "two", "three", "four");
        for (String x : TTT){
            System.out.println(x);
        }
    }
}

//继承了Iterable后可以进行增强式的for循环
class MyList implements Iterable<String>{

    String[] arr = new String[10];

    int index = 0 ; //当前的指针

    MyList(String... number){
        for(String T : number){
            this.add(T);
        }
    }

    public void add(String o){
        arr[index++] = o;  // 1
    }

    public int size(){
        return index;
    }

    @Override
    public Iterator<String> iterator() {

        return new Iterator<String>() {

            int cursor  = 0;

            @Override
            public boolean hasNext() {
                return cursor<index;
            }

            @Override
            public String next() {
                return arr[cursor++];
            }

            @Override
            public void remove() {

            }
        };
    }
}
