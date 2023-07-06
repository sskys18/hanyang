package Week4;

import java.util.Scanner;

public class Practice3 {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        int input;
        input = keyboard.nextInt();
        double result = (double)input/100*4;
        System.out.println("(" + input + "/100) * 4 = " + (int)result);
    }
}
