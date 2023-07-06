package com;

import com.needimplementation.Kitchen;
import com.needimplementation.Order;

import java.util.Arrays;
import java.util.Scanner;

public class Main {

  private static final String CONTENT = "6\n" +
      "john\n" + // 150
      "1\n" +
      "friedrice\n" +
      "mike\n" + // 250
      "1\n" +
      "bibimmyon\n" +
      "din din\n" + // 350
      "3\n" +
      "ramen\n" +
      "ovenroast\n" +
      "egg\n" +
      "hyu undergraduate student 1\n" + // 450
      "3\n" +
      "bibimmyon\n" +
      "friedrice\n" +
      "egg\n" +
      "alexa\n" + // 450
      "3\n" +
      "ramen\n" +
      "friedrice\n" +
      "ovenroast\n" +
      "king sejong\n" + // 750
      "5\n" +
      "egg\n" +
      "ramen\n" +
      "friedrice\n" +
      "ovenroast\n" +
      "bibimmyon";

  public static void main(String[] args) throws InterruptedException {
    Scanner scanner = new Scanner(CONTENT);
    Order[] orders = Order.loadOrder(scanner);

    Kitchen kitchen = new Kitchen();
    for (Order o : orders) {
      kitchen.cook(o); // Cooking should be done by each thread
      println(">>Kitchen took the order from " + o + ", currently order " + Arrays.toString(kitchen.getAllUnfinishedOrders()) + " pended"); // Kitchen is aware if cooking is finished or not
      Thread.sleep(100);
    }

    while (!kitchen.isAllOrderFinished()) {
      println(">>Waiting for these orders to be end: " + Arrays.toString(kitchen.getAllUnfinishedOrders()));
      Thread.sleep(100);
    }

    println(">>All order is cooked!");
  }

  public static synchronized void println(String s) {
    System.out.println(s);
  }
}
