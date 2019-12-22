import java.util.*;
import java.util.stream.Collectors;

/*
 * ? extends A:可以存放A及其子类
 * ? super A:可以存放A及其父类
* */

public class stream {
    public static void main(String[] args){

        List<String> l = List.of("one", "two", "three");
        String[] words = new String[]{"one", "two", "three"};
        List<String> ll = Arrays.stream(words)
                .map(word -> word.split(""))
                .flatMap(Arrays::stream)
                //.distinct()
                .collect(Collectors.toList());
        ll.forEach(System.out::println);


        Flatmap fm = new Flatmap("weizhong", "123456", "6");
        //fm.show();

        List<employee> employees = List.of(
                new employee("li",5,Gender.MALE),
                new employee("zhao", 5,Gender.FENALE),
                new employee("long", 15, Gender.FENALE)
        );
        int sum = employees.stream()
                .filter(employee -> employee.getGender() == Gender.FENALE)
                .mapToInt(employee::getAge)
                .sum();

        int sum2 = employees.stream()
                .filter(employee -> employee.getGender() == Gender.FENALE)
                .mapToInt(employee::getAge)
                .reduce((total, age) -> total + age)
                .getAsInt();

        double average = employees.stream()
                .filter(employee -> employee.getGender() == Gender.FENALE)
                .mapToInt(employee::getAge)
                .average()
                .getAsDouble();

        int max = employees.stream()
                .filter(employee -> employee.getGender() == Gender.FENALE)
                .mapToInt(employee::getAge)
                .max()
                .getAsInt();

        List<employee> em = employees.stream()
                .filter(employee -> employee.getGender() == Gender.FENALE)
                .collect(Collectors.toList());

        /*List<employee> am = employees.stream()
                .collect(filetering());*/ //没找到这个方法

        List.of(sum, average, max).forEach(System.out::println);

        //不清楚为什么sum返回一个0 而average返回一个OptionalDouble
    }
}

enum Gender{FENALE, MALE}

class employee{
    private String name;
    private Integer age;
    private Gender gender;

    public employee(String name, Integer age, Gender gender){
        this.age = age;
        this.name = name;
        this.gender = gender;
    }

    public String getName(){
        return name;
    }

    public Integer getAge(){
        return age;
    }

    public Gender getGender(){
        return gender;
    }

    @Override
    public String toString() {
        return String.format("name : %s , age : %d", name, age);
    }
}

class Flatmap{
    private String school;
    private String gender;
    private String number;

    public Flatmap(String school, String gender, String number){
        this.gender = gender;
        this.number = number;
        this.school = school;
    }

    public Optional<String> getschool(){
        return Optional.ofNullable(school);
    }

    public Optional<String> getnumber(){
        return Optional.ofNullable(number);
    }

    public Optional<String> getgender(){
        return Optional.ofNullable(gender);
    }

    @Override
    public String toString() {
        return String.format("gender : %s, school : %s , number %s",gender, school, number);
    }

    /*public String show(){
        return this.getnumber()
                .flatMap(Flatmap::getgender)
                .flatMap(Flatmap::getschool)
                .orElse("no");
    }*/
}