import java.util.*;

public class Find_number{
    public static void main(String args[]){
        Scanner input = new Scanner(System.in);
        String[] name = new String[1000];
        String[] number = new String[1000];
        int j = 0;
        while(true){
            name[j] = input.next(); 
            if(name[j].equals("noname")) break;
            number[j++] = input.next();   
        }
        String temp = input.next();
        int len = name.length;
        int flag = 1;
        for(int i=0;i<len;++i){
            if(temp.equals(name[i])){
                System.out.println(number[i]);
                flag = 0;
                break;
            }
        }
        if(flag == 1) System.out.println("Not found!\n");
    }
}