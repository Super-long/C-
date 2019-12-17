import java.util.*;



public class Arraylist{
    public static void main(String[] Args){
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int[] array = new int[100];
        for(int i=0;i<n;++i){
            array[i] = input.nextInt();
        }
        ArrayList<Integer> list = new ArrayList<>();//这里就相当与容器 可以学习一下
        for(int i=0;i<n;++i){
            if(!list.contains(array[i])) list.add(array[i]);
        }
        Collections.sort(list);   
        for(int temp : list){
            System.out.print(temp + " ");
        }
    }
}