import java.util.ArrayList;
import java.util.List;

public class test_StackTrace {
    public static void main(String [] args)
    {
        test_StackTrace t3 = new test_StackTrace();
        t3.a();
        List a = new ArrayList();

    }
    Throwable th =  new Throwable();;

    public test_StackTrace() {
        System.out.println("in constructor");
    }

    public void a()
    {
        c();
    }

    public void b()
    {
        System.out.println("in b");
        th.fillInStackTrace();
        th.printStackTrace(System.out);
        System.out.println("in b");
    }

    public void c()
    {
        b();
        th.fillInStackTrace();
        System.out.println("in c");
        th.printStackTrace(System.out);
        System.out.println("in c");
    }

}
/*
* @ 可以看出确实是fillInStackTrace这个函数确实是清空信息后然后在展示新的信息 及其强大
* */
