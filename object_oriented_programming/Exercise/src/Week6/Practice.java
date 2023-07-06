package Week6;

import java.util.Scanner;
import java.util.StringTokenizer;


public class Practice {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        String string1 = keyboard.nextLine();
        String string2 = keyboard.nextLine();
        StringTokenizer stu1 = new StringTokenizer(string1, ". ");
        StringTokenizer stu2 = new StringTokenizer(string2);
        String name1 = stu1.nextToken();
        String year = stu1.nextToken();
        String month = stu1.nextToken();
        String day = stu1.nextToken();
        int year1 = Integer.parseInt(year);
        int month1 = Integer.parseInt(month);
        int day1 = Integer.parseInt(day);
        String name2 = stu2.nextToken();
        Student student1 = new Student(name1,year1,month1,day1);
        Student student2 = new Student(name2,year1);
        System.out.println(student1.getName() + " " + student1.getYear() + "/" + student1.getMonth() + "/" + student1.getDay() + " age :" + student1.calAge(student1.getYear(),student1.getMonth(),student1.getDay()));
        System.out.println(student2.getName() + " " + student2.getYear() + "/" + student2.getMonth() + "/" + student2.getDay() + " age :" + student1.calAge(student2.getYear(),student2.getMonth(),student2.getDay()));
        if(student2.isOlder(student1)){
            System.out.println(student2.getName() + " is older than " + student1.getName());
        }
        else{
            System.out.println(student1.getName() + " is older than " + student2.getName());
        }
    }
}
