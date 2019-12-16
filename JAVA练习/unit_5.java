import java.util.*; //utility 实用程序
import java.math.*;

class cloths{
    private int a =10;
    private final int b;
    private String text;
    //构造函数中一定要对final的值进行初始化
    public cloths(int a, String text){
        //this(a);
        this.text = text;
        this.b = 10;
    }

    public cloths(int a){ 
        this.a = a;
        this.b = 20;
    }

    public void show(){
        System.out.println("hello world " +  text);
    }

    public int sum(int... numbers){
        int sum = 0;
        for(int number : numbers)
            sum += number;
        return sum;
    }
}

class maze{
    int x[] = {1,-1,0,0};
    int y[] = {0,0,1,-1}; 
    static private int[][] map = {
                          {2,2,2,2,2,2,2},
                          {0,0,0,0,0,0,2},
                          {2,0,2,0,2,0,2},
                          {2,0,0,2,0,2,2},
                          {2,2,0,2,0,2,2},
                          {2,0,0,0,0,0,2},
                          {2,2,2,2,2,0,2}};
    int[][] vis = new int[10][10];
    boolean flag = false;
    void start(){
        for(int i=0;i<7;++i){
            Arrays.fill(vis[i], 0);
        }
        dfs(1, 0);
        if(flag) System.out.println("yes");
        else System.out.println("no");

        for(int i=0;i<7;++i){
            for(int j=0;j<7;++j){
                System.out.print(vis[i][j]);
            }
            System.out.println();
        }
    }
    void dfs(int lhs, int rhs){
        if(flag) return;
        if(lhs == 6 && rhs == 5){
            flag = true;
            return;
        }
        for(int i=0;i<4;++i){
            int xx = x[i] + lhs;
            int yy = y[i] + rhs;//类型安全 不能使用位运算符
            if(xx >=0 && xx < 7 && yy >= 0 && yy < 7 && vis[xx][yy]==0 && map[xx][yy]==0){
                vis[xx][yy] = 1;
                dfs(xx, yy);
                if(flag) return;
                vis[xx][yy] = 0;
            }
        }
    }
}

public class unit_5{

    static class helper{
        static final double PI = 3.14159265;
        void show(){
            System.out.println(PI + "is PI");
        } 
    }
    
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        cloths blue = new cloths(10, "blue");
        blue.show();
        System.out.print(blue.sum(1,2,3,4,5,6,7,8,9,10));
        helper Temp = new helper();
        Temp.show();
        int[] sorces = {1,2,3,4,5,6,7};
        int[] score2 = new int[10];
        Arrays.fill(score2, 0, 5, 60);
        for(int T : score2){
            System.out.print(T + " ");
        }
        //int a = scanner.nextInt();
        //int b = scanner.nextInt();
        BigDecimal aa = new BigDecimal(5.646461651651);
        BigDecimal bb = new BigDecimal(5.646461651651);
        if(aa.equals(bb)) System.out.println("same");
        else System.out.println("no same");
        //==判断两个对象是否是一个对象 equals判断两个对象的其中的值是否相同
        //if(a == b) System.out.println("same");
        //else System.out.println("no same");
        maze Tep = new maze();
        Tep.start();
    }
}