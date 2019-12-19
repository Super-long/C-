import java.util.*;

public class unit_9 {
    public static void main(String[] args){
        Queue<String> que = new LinkedList<>();
        for (int i = 0; i < 5; i++) {
            que.offer((String)"asdass");
        }

        que.forEach(name -> System.out.println("hello : " + name));
        //forEach方法接收java.util.function.Consumer<T>接口的实例 其中只有一个accept(T t)的方法 Lambda表达式就很舒服
        //foreach(que);
        //foreach(que);

        List list = Arrays.asList(1,2,3,4);
        System.out.println(list.size());
    }

    static void foreach(Iterable que){
        for(Object T : que){
            System.out.println(T);
        }
    }

    /*static void foreach(Iterable para){ //是Collection的父接口 所以这一套容器均可这样遍历
        Iterator itr = para.iterator();
        while(itr.hasNext()){
            System.out.println(itr.next());
        }
    }*/

    static void foreach(Collection que){
        Iterator itr = que.iterator();
        while(itr.hasNext()){
            System.out.println(itr.next());
        }
    }
}
