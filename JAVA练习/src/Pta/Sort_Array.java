package Pta;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Sort_Array {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        while (true){
            try {
                int a = input.nextInt();
                int b = input.nextInt();
                System.out.printf("Sum is %d%n", a+b);
            }catch (Exception ex){
                System.out.println("Incorrect input and re-enter two integers:");
                input.nextLine();
            }
        }
    }
}
