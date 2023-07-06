package Week8;

import java.util.Scanner;

public class Practice1 {
    public static int[][] drawSnail(int n){
        int[][] snailArray = new int[n][n];
        int i,j, cnt = 1;
        int x=0, y=-1, top=1;
        for(i = n; i > -1; i--) {
            for (j = 0; j < n; j++) {
                y += top;
                snailArray[x][y] = cnt;
                cnt++;
            }
            n--;
            for (j = 0; j < n; j++) {
                x += top;
                snailArray[x][y] = cnt;
                cnt++;
            }
            top *= (-1);
        }
        return snailArray;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        sc.nextLine();
        int[][] array = drawSnail(n);
        for(int i=0; i<n;i++) {
            for(int j=0;j<n;j++) {
                System.out.print(array[i][j] + "\t");
            }
            System.out.println("");
        }
    }
}
