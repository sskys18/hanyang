package Week5;

import java.util.Scanner;
import java.util.Random;

public class Practice2 {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        Random rnd = new Random();
        String word = keyboard.next();
        int wordNum = 0;
        switch(word) {
            case "rock" :
                wordNum = 0;
                break;
            case "paper" :
                wordNum = 1;
                break;
            case "scissors" :
                wordNum = 2;
                break;
        }
        int randomNum = rnd.nextInt(3);
        switch(randomNum) {
            case 0 :
                System.out.println("Computer's choice : rock");
                break;
            case 1 :
                System.out.println("Computer's choice : paper");
                break;
            case 2 :
                System.out.println("Computer's choice : scissors");
                break;
        }
        if(wordNum == randomNum) {
            System.out.println("You draw");
        }
        else if(wordNum > randomNum || (wordNum == 0 && randomNum == 2)) {
            System.out.println("You win");
        }
        else {
            System.out.println("You lose");
        }
    }
}
