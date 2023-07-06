package Week15;

import java.util.ArrayList;
import java.util.Iterator;

public class Eratos {
    public static ArrayList<Integer> calculate(int n) {

        boolean[] prime = new boolean[n + 1];

        ArrayList<Integer> list = new ArrayList<Integer>();
        for (int i = 2; i < n; i++) {
            prime[i] = true;
        }
        for (int i = 2; i < n; i++) {
            if (prime[i]) {
                list.add(i);
                for (int j = i; j * i <= n; j++) {
                    prime[i * j] = false;
                }
            }
        }
        return list;
    }
}
