package Week6;

import java.util.Calendar;
import java.util.Random;
import java.text.SimpleDateFormat;
import java.text.ParseException;

public class Student {
    private String name;
    private int year;
    private int month;
    private int day;

    public Student(String name, int year, int month, int day)
    {
        if(checkDate(month,day,year)) {
            this.name = name;
            this.year = year;
            this.month = month;
            this.day = day;
        }
        else
        {
            System.out.println("invalid input");
            System.exit(0);
        }
    }
    public Student(String name, int year)
    {
        do{
            Random rnd = new Random();
            month = rnd.nextInt(12) + 1;
            day = rnd.nextInt(31) + 1;
        }while(!checkDate(month,day,year));
        this.name = name;
        this.year = year;
        this.month = month;
        this.day = day;

    }
    public String getName()
    {
        return name;
    }
    public int getYear()
    {
        return year;
    }
    public int getMonth()
    {
        return month;
    }
    public int getDay()
    {
        return day;
    }
    private boolean checkDate(int monthInt, int dayInt, int yearInt)
    {
        String month = Integer.toString(monthInt);
        String day = Integer.toString(dayInt);
        String year = Integer.toString(yearInt);
        if((yearInt<1000) || (yearInt>=9999)){
            return false;
        }
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        dateFormat.setLenient(false);
        try{
            dateFormat.parse(year+"-"+month+"-"+day);
            return true;
        } catch (ParseException ex) {
            return false;
        }
    }
    public int calAge(int year, int month, int day)
    {
        Calendar current = Calendar.getInstance();
        int currentYear  = current.get(Calendar.YEAR);
        int currentMonth = current.get(Calendar.MONTH) + 1;
        int currentDay   = current.get(Calendar.DAY_OF_MONTH);
        int age = currentYear - year;
        if ((month > currentMonth) || ((month == currentMonth) && (day > currentDay)))
            age--;
        return age;
    }
    public boolean isOlder(Student stu)
    {
        return((month < stu.month) || ((month == stu.month) && (day < stu.day)));
    }
}
