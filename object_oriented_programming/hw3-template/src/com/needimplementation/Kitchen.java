package com.needimplementation;

import java.util.ArrayList;
import java.util.Arrays;

// TODO Implement this class, do not modify the existing code but only add from it
public class Kitchen {

  private final ArrayList<Thread> threads = new ArrayList<>();;
  private final ArrayList<Order> orders = new ArrayList<>();

  public void cook(Order o) {
    orders.add(o);
    Thread test = new Thread(o);
    test.start();
    threads.add(test);
  }

  public boolean isAllOrderFinished() {
    for (Thread thread : threads) {
      if (thread.isAlive()) {
        return false;
      }
    }
    return true;
  }

  public Order[] getAllUnfinishedOrders() {
    Order[] order = new Order[threads.size()];
    for (int index = 0;index< threads.size();index++) {
      if (threads.get(index).isAlive() && orders.get(index) != null) {
        order[index] = orders.get(index);
      }

    }
    return order;
  }
}
