package Week11;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    public static boolean isCoprime(int num1, int num2) {
        int result = 1;
        if (num1 <= num2) {
            for (int i = num1; i > 0; i--) {
                if ((num1 % i == 0) && (num2 % i == 0)) {
                    result = i;
                    break;
                }
            }
        } else {
            for (int i = num2; i > 0; i--) {
                if ((num1 % i == 0) && (num2 % i == 0)) {
                    result = i;
                    break;
                }
            }
        }
        if (result == 1) {
            System.out.println("numbers are coprime");
            return true;
        }
        else{
            System.out.println("numbers are not coprime");
            return false;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try{
            System.out.println("Enter two integers");
            int num1 = sc.nextInt();
            int num2 = sc.nextInt();

            if( num1 <= 1 || num2 <= 1)
                throw new MyException("number is less or equal to 1");
            if(num1 == num2)
                throw new MyException("number is same");
            if(num1 > 10000 && num2 > 10000)
                throw new MyException("number is larger than 10000");
            isCoprime(num1,num2);
        } catch (MyException e) {
            System.out.println(e.getMessage());
        } catch (InputMismatchException e) {
            System.out.println("Type \"legal\" integer number!");
        }
    }




}
