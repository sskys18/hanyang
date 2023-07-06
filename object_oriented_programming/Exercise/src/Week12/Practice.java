package Week12;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Practice {
    public static void main(String[] args) {
        BinarySearch sort = new BinarySearch();
        int[] target = new int[100];
        int[] sequence = new int[100000];
        Scanner inputStream = null;
        try{
            inputStream = new Scanner(new FileInputStream("C:\\Users\\sskys\\2022_ite2037_2018008040\\Exercise\\src\\Week12\\input.txt"));
        }catch(FileNotFoundException e){
            System.out.println("input.txt was not found");
        }
        for(int i=0;i<100;i++){
            target[i] = inputStream.nextInt();
        }
        for(int i=0;i<100000;i++){
            sequence[i] = inputStream.nextInt();
        }
        for(int i=0;i<100;i++){
            int index = sort.search(sequence, 0 ,99999, target[i]);
            System.out.println("target: " + target[i]+ " index: "+ index);
        }
    }
}
