import java.util.*;
import static java.lang.System.out;

public class ClientQueue{
    public static void main(String[] args){
        Client para1 = new Client("127.0.0.1", "lzl");
        Client para2 = new Client("192.168.0.1", "zsy");

        Clientqueue que = new Clientqueue(); //接口中只有一个函数的可以使用Lambda
        que.addclientListener(new Clientlisten(){
            @Override
            public void clientaddlisten(clientevent para){
                out.println("on-line");
            }
            @Override
            public void clientremvelisten(clientevent para){
                out.println("no on-line");
            }
        });
        que.Add(para1);
        que.Add(para2);
        que.Remove(para1);
        que.Remove(para2);
    }
}

class Client{
    public final String IP;
    public final String name;
    public Client(String IP, String name){
        this.IP = IP;
        this.name = name;
    }
}

class clientevent{
    private Client Cli_;
    clientevent(Client client){
        this.Cli_ = client;
    }
    public String getname(){
        return Cli_.name;
    }
    public String getIP(){
        return Cli_.IP;
    }
}

interface Clientlisten{
    void clientaddlisten(clientevent para);
    void clientremvelisten(clientevent para);
}

class Clientqueue{
    private ArrayList clients = new ArrayList(); //线程不安全
    private ArrayList listeners = new ArrayList();

    public void addclientListener(Clientlisten lis){
        listeners.add(lis); //一般扔进去一个匿名对象
    }

    public void Add(Client client){
        clients.add(client);
        clientevent event = new clientevent(client);
        for(int i = 0; i < listeners.size(); ++i){
            Clientlisten Temp = (Clientlisten) listeners.get(i);
            Temp.clientaddlisten(event);
        }
    }
    public void Remove(Client client){
        clients.remove(client);
        clientevent event = new clientevent(client);
        for(int i = 0; i < listeners.size(); ++i){
            Clientlisten Temp = (Clientlisten) listeners.get(i);
            Temp.clientremvelisten(event);
        }
    }
}
