package LotterySimulator;

import java.util.Random;

public class LotteryGenerator {
    private int[] winNum;
    private int[] lottoNum;
    public int[] setWinNum() {
        winNum = new int[7];
        Random rnd = new Random();
        for(int i = 0;i<7;i++) {
            winNum[i] = rnd.nextInt(10) + 1;
            for (int j = 0; j < i; j++) {
                if(winNum[j]==winNum[i]){
                    i--;
                    break;
                }
            }
        }
        System.out.print(">> Round Winning number : ");
        for(int i = 0;i<6;i++){
            System.out.print(winNum[i]+" ");
        }
        System.out.println("+ " + winNum[6]);
        return winNum;
    }

    public int[] setLottoNum(){
        lottoNum = new int[6];
        Random rnd = new Random();
        for(int i = 0;i<6;i++) {
            lottoNum[i] = rnd.nextInt(10) + 1;
            for (int j = 0; j < i; j++) {
                if(lottoNum[j]==lottoNum[i]){
                    i--;
                    break;
                }
            }
        }
        System.out.print(">> Lottery number : ");
        for(int i = 0;i<6;i++){
            System.out.print(lottoNum[i]+" ");
        }
        LotteryChecker lottoCheck = new LotteryChecker(winNum,lottoNum);
        lottoCheck.checkNum();
        return lottoNum;
    }

}
