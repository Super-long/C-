import java.util.*;

public class implementList{
    public static void main(String args[]){
        ArrayList<String> list = new ArrayList<String>();
        LinkedList<String> list2 = new LinkedList<String>();
        list.add("hello");
        list2.add("hello");
        String str = "hello";
        StringBuilder strbud = new StringBuilder();
        strbud.append(str);
        System.out.println(strbud.appendCodePoint(97));
        System.out.println(Character.toChars(96));
        System.out.println(strbud.toString());

        //test of list
        //A simple list.
        SimpleList Slist = new SimpleList();
        String one = "one";
        Slist.add(one);
        String list3 = (String)Slist.get(0);
        System.out.println(list3);
    }
}

class SimpleList{
    private class node{
        node(Object a){
            this.value = a;
            next = null;
        }
        Object value;
        node next;
    }
    private node first;
    public void add(Object elem){
        node T = new node(elem);
        if(first == null){
            first = T;
        }else {
            append(T);
        }
    }

    private void append(node para){
        node last = first;
        while(last.next != null){
            last = last.next;
        }
        last = para;
    }

    public Object findElemof(int index){
        int count = 0;
        node last = first;
        while(++count < index){ //遇到这种条件判断<优于!= 不容易犯错误
            last = last.next;
        }
        return last.value;
    }

    private int size(){
        node last = first;
        int count = 0;
        while(last != null){
            last = last.next;
            count += 1;
        }
        return count;
    }

    void checksize(int len){
        if(len < 0 || len > size()){
            throw new IndexOutOfBoundsException(
                        String.format("index %d, size %d", len, size())
            );
        }
    }

    public Object get(int index){
       checksize(index);
       return findElemof(index);
    }
}