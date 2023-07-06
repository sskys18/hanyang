package LotterySimulator;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        int input = -1;
        while(input != 0) {
            System.out.print("<< ");
            input = keyboard.nextInt();
            if(input == 0) break;
            LotteryGenerator lottoNum = new LotteryGenerator();
            lottoNum.setWinNum();
            for(int i=0; i<input;i++){
                lottoNum.setLottoNum();
            }

        }
        System.out.println(">> End of program");
        System.exit(0);
    }
}
