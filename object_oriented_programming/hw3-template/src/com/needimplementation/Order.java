package com.needimplementation;

import com.Main;

import java.util.Scanner;

// TODO Implement this class, do not modify the existing code but only add from it
public class Order implements Runnable {

  private String name;
  private String[] foods;

  public String getName() {
    return name;
  }

  public static Order[] loadOrder(Scanner scanner) {
    int i =scanner.nextInt();
    scanner.nextLine();
    Order[] orders = new Order[i];
    for(int j=0;j<i;j++){
      orders[j] = new Order();
      orders[j].name = scanner.nextLine();
      int foodNum = scanner.nextInt();
      scanner.nextLine();
      for(int k=0;k<foodNum;k++){
        orders[j].foods = new String[foodNum];
        orders[j].foods[k] = scanner.nextLine();
      }
    }
    return orders;
  }

  @Override
  public String toString(){
    return this.name;
  }

  @Override
  public void run() {
    try {
      for(String food: foods){
        cook(food);
      }
      Main.println(">>Order from [" + this + "] finished");
    } catch (InterruptedException ignored) {
      // Should never ever happen if program is implemented as requested
    }
  }

  private void cook(String dish) throws InterruptedException {
    switch (dish) {
      case "egg":
        Thread.sleep(50);
        break;
      case "ramen":
        Thread.sleep(100);
        break;
      case "friedrice":
        Thread.sleep(150);
        break;
      case "ovenroast":
        Thread.sleep(200);
        break;
      case "bibimmyon":
        Thread.sleep(250);
        break;
      default:
        break;
    }
  }
}
