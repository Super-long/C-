import java.util.*;

public class test_Queue{

    public static void main(String[] args){
        Queue que = new LinkedList();
        Deque<String> dque = new ArrayDeque<String>();
        dque.offerLast(new String("hello"));
        dque.offerFirst(new String("world"));
        //dque.pop();
        ArrayList<Integer> alt = new ArrayList<>(); //JDK7以后可以这样写
        System.out.println(dque.element());
        //dque.push(new String("okoko")); //equal of offerFirst
        for(String T : dque){
            System.out.println(T);
        }
        comparameter<String> x = new comparameter<String>() {
            @Override
            public int compare(String para1, String para2) {
                /*if(para1 < para2)
                    return -1;
                else if(para1 == para2)
                    return 0;
                else return 1;*/
                return para1.compareTo(para2);
            }
        };
        String one = "Asd";
        String two = "dasd";
        System.out.println("comparae : " + x.compare(one, two));
        //offerRequests(que);
        //handing(que);
    }

    static void offerRequests(Queue que){
        for (int i = 0; i < 5; i++) {
            Request Temp = new Request(){
                    public void execute(){
                        System.out.println("hello world");
                    }
            };
            que.offer(Temp);
        }
    }

    static void handing(Queue que){
        while (!que.isEmpty()){
            Request T = (Request)que.poll();
            T.execute();
        }
        /*while (que.peek() != null){
            Request T = (Request) que.poll();
            T.execute();
        }*/
    }
}

interface comparameter<e>{
    int compare(e para1, e para2);
}

class comparastring implements comparameter<String>{
    @Override
    public int compare(String para1, String para2){
        return para1.compareTo(para2);
    }
}

interface Request{
    void execute();
}



