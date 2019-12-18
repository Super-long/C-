import java.util.*;
import static java.lang.System.out;
import static java.lang.System.in;

//DAO Data AccessObject 数据访问接口
/*
1）一个DAO接口
2）一个实现了DAO的具体实现类
3）一个DAO工厂类
4）数据传输对象（有时称为值对象）
*/
//业务对象应该只关注业务逻辑
/*
使用DAO设计模式来封装数据库持久层所有操作（CRUD） ，使低级的数据逻辑和高级的业务分离，达到解耦合的目的。
*/

//工厂类 可根据不同的类型返回一个接口类型的对象 根据多态调用其需要的版本
public class CashcardService{

    CashcardService(StorageMethod para){
        ArrayList<String> array = new ArrayList<String>();
        switch (para){
            case DATABASE:
                break;
            case FILE:
                break;
            case OTHERCOMPUTER:
                break;
            default:
                assert false : "undefined value."; //assert关键字 和C++差不多
        }
    }
}

class Cashcard{
    String number;
    int blance;
    int bonus;
    public String getNumber(){
        return number;
    }
}

enum StorageMethod{ //存储方法
    DATABASE, FILE, OTHERCOMPUTER
}

interface  Cashcara_Servive{
    abstract public void save(Cashcard para);
    abstract public Cashcard load(String number);
}

//实现我们可以采用不同的实现
class CashcardServic_ implements  Cashcara_Servive{
    @Override
    public void save(Cashcard para){

    }

    @Override
    public Cashcard load(String number){
        if(!number.matches("\\d*")){
            return null;
        }else{

        }
    }
}
