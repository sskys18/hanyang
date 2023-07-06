package Week15;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class Main {
    public static void main(String[] args){
        ArrayList<Integer> printlist = new ArrayList<Integer>();
        Scanner keyboard = new Scanner(System.in);
        int n;
        n = keyboard.nextInt();
        Eratos eratos = new Eratos();
        ArrayList<Integer> list = eratos.calculate(n);
        Iterator itr = list.iterator();
        while (itr.hasNext()) {
            System.out.println((Integer)itr.next());
        }
    }
}
