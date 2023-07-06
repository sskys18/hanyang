package Week8;

import Week7.*;
import Week7.util.AgeCalculator;

import java.util.Date;
import java.util.Random;

public class Practice2 {
    public static void main(String[] args){
        Person[] personArray = new Person[10];
        for(int i=0;i<10;i++){
            Random rnd = new Random();
            int bornYear = (int) (Math.random() * (2022 - 1930 + 1)) + 1930;
            int bornMonth = rnd.nextInt(12) + 1;
            int bornDay = 0;
            switch (bornMonth) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    bornDay = rnd.nextInt(31) + 1;
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    bornDay = rnd.nextInt(30) + 1;
                    break;
                case 2:
                    bornDay = rnd.nextInt(28) + 1;
                    break;
            }
            Date born = new Date(bornYear,bornMonth,bornDay);
            personArray[i] = new Person("person" + i, born, null);
        }
        for(int i=0;i<9;i++){
            for(int j=i+1;j<10;j++){
                if(AgeCalculator.isOlder(personArray[i],personArray[j]) == 1) {
                    Person tmp = personArray[i];
                    personArray[i] = personArray[j];
                    personArray[j] = tmp;
                }
            }
        }
        for(int i=0;i<10;i++){
            System.out.println(personArray[i].getName() + "'s age: " + AgeCalculator.calAge(personArray[i]));
        }
    }
}
