import java.util.*;

public class number_of_letter{
    public static int countletters(String s){
        int count = 0;
        for(int i=0;i<s.length();++i){
            if((s.charAt(i))>='a' && s.charAt(i)<='z' || s.charAt(i)>='A' && s.charAt(i)<='Z') count++;
        }
        return count;
    }
    public static void main(String[] Args){
        Scanner input = new Scanner(System.in);
        String str = input.next();
        System.out.println("The number of letters inside the string is: "+countletters(str));
    }
}