import java.util.*;

public class Max_in_array{
    public static Object max(Comparable[] a){
        Arrays.sort(a);
        return a[a.length-1];
    }
    public static void main(String[] args){
        String[] aArray = new String[5];
        Integer[] integersarray = new Integer[5];
        Scanner input = new Scanner(System.in);
        for(int i=0;i<aArray.length;i++){
            aArray[i] = input.next();
        }
        for(int i=0;i<integersarray.length;i++){
            integersarray[i] = input.nextInt();
        }
        System.out.println("Max string is " + (String)max(aArray));
        System.out.println("Max interger is " + (Integer)max(integersarray));
    }
}