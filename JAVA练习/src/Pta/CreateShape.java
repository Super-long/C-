import java.util.*;
import java.math.*;
import java.text.*;

public class CreateShape {
    public static void main(String[] args) {
        DecimalFormat d = new DecimalFormat("#.####");
        Scanner input = new Scanner(System.in);
        double a = input.nextDouble();
        IShape r = new RHexagon (a);
        System.out.println(d.format(r.getArea()));
        System.out.println(d.format(r.getPerimeter()));
        input.close();
    }
}

interface IShape {
    double getArea();

    double getPerimeter();
}

class RHexagon implements IShape{
    private double len ;
    RHexagon(double x){
        this.len = x;
    }

    @Override
    public double getArea(){
        return 1.5*Math.sqrt(3)*len*len;
    }
    @Override
    public double getPerimeter(){
        return 6*len;
    }
}