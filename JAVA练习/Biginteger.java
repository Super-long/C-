import java.util.*;
import java.math.*;

public class Biginteger{
    public static void main(String[] args) {
        Scanner imput = new Scanner(System.in);
        BigInteger a = imput.nextBigInteger();
        BigInteger b = imput.nextBigInteger();
        BigInteger c = a.divide(b);
        System.out.println(c);
    }
}