package Week4;

import java.util.Scanner;

public class Practice2 {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        int intVal1, intVal2;
        intVal1 = keyboard.nextInt();
        intVal2 = keyboard.nextInt();
        int quo = intVal1/intVal2;
        int remainder = intVal1%intVal2;
        System.out.println("dividend = " + intVal1);
        System.out.println("divisor = " + intVal2);
        System.out.println("quotient = " + quo);
        System.out.println("remainder = " + remainder);

    }
}
