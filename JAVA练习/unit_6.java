import java.util.*;
import java.math.*;

abstract class SwordMan{ //现在这东西就变成了一个接口(抽象基类)
    private String name;
    private int level;
    private int blood;

    SwordMan(String name, int level, int blood){
        this.name = name;
        this.level = level;
        this.blood = blood;
        System.out.println("sucessful in base class");
    }

    SwordMan(){
    }

    protected abstract void fight();

    public int getblood(){
        return this.blood;
    }
    public void setblood(int blood){
        this.blood = blood;
    }
    public String getname(){
        return this.name;
    }
    public void setname(String name){
        this.name = name;
    }

}

class MagicSwordMan extends SwordMan{
    @Override public void fight(){ //对于父类中的函数限定符权限派生类只能扩大不能减小
        System.out.print("Magic Sword attack!");
    }

    public void cure(){
        System.out.print("Magic cure!");
    }

    public String toString(){
        return String.format("this is my information : %s %d%n", getname(), getblood());
    }
}

    final class NoMagicSwordMan extends SwordMan{
    NoMagicSwordMan(String name, int level, int blood){
        super(name, level, blood);
        //this() 与 super() 只能选一个执行 且必须要在构造函数的第一行执行 
    }

    @Override public void fight(){
        System.out.print("noMagic Sword attack!");
    }

    public void nocure(){
        System.out.print("no Magic cure!");
    }

    private String Name_;
}

//java中派生类只能继承一个基类

public class unit_6{
    static void drawfight(SwordMan x){
        x.getname();
        x.fight();
    }

    static public void main(String[] args){
        SwordMan msm = new MagicSwordMan();
        SwordMan msa = new NoMagicSwordMan("hello", 10, 20);
        drawfight(msm);
        drawfight(msa); //java我真是太喜欢了 太好用了.
        System.out.println(((MagicSwordMan)msm).toString());
        //NoMagicSwordMan TT = (NoMagicSwordMan)msm;//编译通过 执行出现问题 很正常
        //msm.getname(); //太有意思了 null都能打印 java大法好.
    }
}