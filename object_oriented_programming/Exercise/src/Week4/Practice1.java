package Week4;

import java.util.Scanner;

public class Practice1 {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        keyboard.useDelimiter(",");
        String word1, word2, word3;
        word1 = keyboard.next();
        word2 = keyboard.next();
        word3 = keyboard.next();
        System.out.println(word1);
        System.out.println(word2);
        System.out.println(word3);
    }
}
