package Week5;

import java.util.Scanner;

public class Practice1 {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        int input = keyboard.nextInt();
        for(int i = 1; i*input < 101; i++) {
            System.out.print(i*input+", ");
        }
    }
}
