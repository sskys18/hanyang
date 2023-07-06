package LotterySimulator;

public class LotteryChecker {
    private int[] winNum;
    private int[] lottoNum;

    public LotteryChecker(int[] winNum, int[] lottoNum){
        this.winNum = winNum;
        this.lottoNum = lottoNum;
    }
    public void checkNum(){
        int n =0;
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                if(winNum[i] == lottoNum[j]) n++;
            }
        }
        if(n == 6){
            System.out.println("Winner (1st place)");
        }
        else if(n == 5){
            for(int i=0;i<6;i++) {
                if (winNum[6] == lottoNum[i]) {
                    System.out.println("Winner (2nd place)");
                    n++;
                    break;
                }
            }
            if(n == 5) System.out.println("Winner (3rd place)");

        }
        else if(n == 4){
            System.out.println("Winner (4th place)");
        }
        else if(n == 3){
            System.out.println("Winner (5th place)");
        }
        else{
            System.out.println("Lose");
        }
    }
}
