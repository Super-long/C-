package Pta;

import java.math.*;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class search_score {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String result = input.next();
        String[] ob =  result.split("\\D", 0);
        Integer flag = 0;
        if(result.indexOf('/') != -1) flag = 0;
        else if(result.indexOf('*') != -1) flag = 1;
        else if(result.indexOf('+') != -1) flag = 2;
        else flag = 3;
        BigInteger one = new BigInteger(ob[0]);
        BigInteger two = new BigInteger(ob[1]);
        System.out.println(flag);
        one = one.subtract(two);
        System.out.println(one);
        switch (flag){
            case 1:
                System.out.println();
                break;
                case 2:
                System.out.println();
                break;
            case 0:
                one.divide(two);
                System.out.println(one);
                break;
        }

    }
}

//这个问题要搞清楚
abstract class four{
    abstract public void Show();
}

interface auto extends four{
    abstract public void show();
    @Override
    public void Show();
}

class three implements auto{
    @Override
    public void show(){
        System.out.println("ok");
    }

    @Override
    public void Show() {

    }
}

class one{
    private String a;
    one(String a){
        this.a = a;
    }
    one(){

    }
    public void show(){
        System.out.println("one");
    }
}

class two extends one{
    two(String str){
        super(str);
    }
    public void show(){
        System.out.println("two");
    }
}

class student implements Comparable<student>{
    private String name;
    private double score;

    public student(String str, double fl){
        this.name = str;
        this.score = fl;
    }

    @Override
    public int compareTo(student student) {
        if(score < student.score) return -1;
        else return 1;
    }
}
