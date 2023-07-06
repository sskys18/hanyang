package Week7.util;

import Week7.Person;

import java.util.Calendar;

public class AgeCalculator {
    public static int calAge(Person p) {
        Calendar current = Calendar.getInstance();
        int currentYear  = current.get(Calendar.YEAR);
        int currentMonth = current.get(Calendar.MONTH) + 1;
        int currentDay   = current.get(Calendar.DAY_OF_MONTH);
        int age = 0;
        if(p.getDied() == null) {
            age = currentYear - p.getBorn().getYear();
            if ((p.getBorn().getMonth() > currentMonth) || ((p.getBorn().getMonth() == currentMonth) && (p.getBorn().getDay() > currentDay)))
                age--;
        }
        else {
            age = p.getDied().getYear() - p.getBorn().getYear();
            if ((p.getBorn().getMonth() > p.getDied().getMonth()) || ((p.getBorn().getMonth() == p.getDied().getMonth()) && (p.getBorn().getDate() > p.getDied().getDate())))
                age--;
        }

        return age;
    }
    public static int isOlder(Person p1, Person p2){
        if(calAge(p1) > calAge(p2)) return 1;
        else if(calAge(p1) < calAge(p2)) return -1;
        else return 0;
    }
}
