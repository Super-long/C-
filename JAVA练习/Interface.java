import java.util.*;
import static java.lang.System.out;

interface Swimmer{
    public abstract void swim();
}

interface Flyer{
    public abstract void fly();
}
//接口中的方法没有实现的时候一定是公开且抽象的
interface Diver extends Swimmer,Flyer{ //接口可以继承另一个接口 也可以多继承
    public abstract void diver();
}

class Human implements Swimmer{
    @Override public void swim(){
        out.println("I'm a human, I can swim.");
    }
}

class Seaplane implements Swimmer, Flyer{
    @Override public void swim(){
        out.println("I'm a Seaplane, I can swim.");
    }
    @Override public void fly(){
        out.println("I'm a Seaplanem I can fly.");
    }
}

class Fish implements Swimmer{
    @Override public void swim(){
        out.println("I'm a Fish, I can swim.");
    }
}

class FlyingFish extends Fish implements Flyer{
    @Override public void swim(){
        out.println("I'm a FlyingFish, I can swim.");
    }
    @Override public void fly(){
        out.println("I'm a FlyingFish, I can fly.");
    } //没有实现的时候相当于一个抽象基类 没有办法被实例化 
} 

class Shark extends Fish{
    public void swim(){
        out.println("I'm a Shark, I can swim.");
    }
}

interface Game{ //相当于一个枚举常数 但一定要使用=号
    public static final int one = 1;
    public static final int two = 2;
    public static final int three = 3;
}
enum Game_en{
    onw, two, three, four
} //枚举类继承自java.lang.Enum

//匿名内部类

public class Interface{
    public static void main(String[] args){
        Swimmer T = new Swimmer(){
            public void swim(){
                out.println("匿名内部类");
            }
        };
        //若接口只定义了一个抽象方法 可以使用Lambda表达式简化 JDK8以后支持
        Swimmer TT = () -> {out.println("lambda表达式");};
        TT.swim();
        T.swim();
        
        Fish one = new Shark();
        one.swim();
        Swimmer two = new Seaplane();
        two.swim();
        ((Seaplane)two).fly();
        FlyingFish three = new FlyingFish();
    }
}