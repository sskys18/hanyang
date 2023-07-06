package Week7;

import java.util.Date;
import Week7.util.*;

public class Main {
    public static void main(String[] args) {
        Date date1 = new Date(1999,4,13);
        Date date2 = new Date(1975,9,17);
        Date date3 = new Date(2002,4,13);


        Person p1 = new Person("p1", date1, date3);
        System.out.println(p1.toString());
        Person p2 = new Person("p2", date2, null);
        System.out.println(p2.toString());

        System.out.println(p1.getName()+"'s age is "+AgeCalculator.calAge(p1));
        System.out.println(p2.getName()+"'s age is "+AgeCalculator.calAge(p2));
        if(AgeCalculator.isOlder(p1,p2) == 1) System.out.println(p1.getName()+" is older than "+p2.getName());
        else if(AgeCalculator.isOlder(p1,p2) == -1) System.out.println(p2.getName()+" is older than "+p1.getName());
        else System.out.println(p1.getName()+" and "+p2.getName()+" has same age ");
    }
}
