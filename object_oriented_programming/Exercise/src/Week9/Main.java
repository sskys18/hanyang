package Week9;

import java.util.Date;

public class Main {
    public static void main(String[] args){
        Date date1 = new Date(1999,4,13);
        Date date2 = new Date(1975,9,17);
        Date date3 = new Date(2002,4,13);
        Date date4 = new Date(1970,9,17);
        Doctor d1 = new Doctor("d1", date2, null, "hospital1");
        Patient p1 = new Patient("p1", date1, null, "internal");
        Patient p2 = new Patient("p2", date3, null, "Dental");
        Physician d2 = new Physician("d2", date4, null, "hospital2");

        System.out.println(d1.toString());
        System.out.println(d2.toString());
        System.out.println(p1.toString());
        System.out.println(p2.toString());

        d1.examination(p1);
        d1.examination(p2);
        d2.examination(p1);
        d2.examination(p2);
    }
}
