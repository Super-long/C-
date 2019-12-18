import java.util.*;

public class test_compare {
    public static void main(String[] args){ //main函数中无法使用主类的嵌套类
        ArrayList<User> student = new ArrayList<User>();
        User user2 = new User(2,"zsy");
        User user1 = new User(1, "lzl");
        student.add(user2);
        student.add(user1);
        Collections.sort(student, COM);
        for(User T : student){
            System.out.println(T);
        }

        //test of lambda expression.
        Tst x = (String str) -> String.format("str %s", str); //语句比较长可以使用{}来划分一个区域
    }

    private static final Comparator<User> COM = new Comparator<User>() {
        @Override
        public int compare(User user, User t1) {
            //return user.compareTo(t1);
            if(user.getID() < t1.getID()) return -1;
            else if(user.getID() < t1.getID()) return 0;
            return 1;
        }
    };

    class test{
        int id;
        test(int id){
            this.id = id;
        }
    }

}

interface Tst{
    String Return_str(String str);
}

//implements Comparable<Object>
class User {
    int ID;
    String name;

    public int getID() {return this.ID;}
    public void getname(){
        System.out.println(name);
    }

    public User(int id, String para){
        this.ID = id;
        this.name = para;
    }

    @Override
    public String toString(){
        return String.format("ID : %d  Name : %s",ID, name);
    }

    /*@Override
    public int compareTo(Object para){
        if(this == para){
            return 0;
        }
        else if (para != null && para instanceof User){
            if(ID <= ((User) para).ID){
                return -1;
            }else return 1;
        }else return -1;
    }*/
}
