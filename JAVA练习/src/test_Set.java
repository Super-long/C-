import javax.swing.*;
import java.util.*;

public class test_Set{
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);

        System.out.println("please enter some words");
        Set<String> wrods = Return_Set(input.nextLine());//可接收一行数据
        System.out.println(wrods.size());
        for(String T : wrods){
            System.out.println(T);
        }
        Set<Student> se = new HashSet();
        Student a = new Student("li","233");
        Student b = new Student("li","233");
        System.out.println(a.hashCode()+ " " + b.hashCode()); //没重载的时候也不一样呀
        se.add(new Student("li","233"));
        se.add(new Student("zhang","9824"));
        se.add(new Student("zhang","9824"));
        System.out.println(se.size());

    }
    /*
    * @ 静态方法不能使用类的非静态变量。静态方法从参数列表得到数据，然后计算这些数据。
    * @ main函数是静态的 所以Return_Set 函数得是静态的才能被引用
    * */
    public static Set Return_Set(String args){
        String[] token = args.split(" ");
        return new HashSet(Arrays.asList(token)); //学一手
    }
}

class Student{
    private String name;
    private String number;
    Student(String name, String number){
        this.name = name;
        this.number = number;
    }
    Student(){}

    @Override
    public int hashCode(){ //因为Set使用hashcode和equal比较是否重复 所以两个方法一般同时操作
        int hash = 7;
        return hash = 47 * hash + Objects.hashCode(this.name);
    }

    @Override
    public boolean equals(Object obj){
        if(obj == null){
            return false;
        }
        if(getClass() != obj.getClass()){
            return false;
        }
        final Student other = (Student)obj;
        if(!name.equals(other.name)) return false;
        if(!number.equals(other.number)) return false;
        return true;
    }

    @Override
    public String toString(){
        return String.format("name = %s , number = %s", name, number);
    }
}
