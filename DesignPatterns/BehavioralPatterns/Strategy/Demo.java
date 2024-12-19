package DesignPatterns.BehavioralPatterns.Strategy;

import DesignPatterns.BehavioralPatterns.Strategy.order.Order;
import DesignPatterns.BehavioralPatterns.Strategy.strategies.PayByCreditCard;
import DesignPatterns.BehavioralPatterns.Strategy.strategies.PayByPayPal;
import DesignPatterns.BehavioralPatterns.Strategy.strategies.PayStrategy;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

/**
 * World first console e-commerce application.
 */
public class Demo {

    private static final Map<Integer, Integer> priceOnProducts = new HashMap<>();
    private static final BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static Order order = new Order();
    private static PayStrategy strategy;

    static {
        priceOnProducts.put(1, 2200);
        priceOnProducts.put(2, 1850);
        priceOnProducts.put(3, 1100);
        priceOnProducts.put(4, 890);
    }

    public static void main(String[] args) throws IOException {
        while (!order.isClosed()) {
            int cost;

            String continueChoice;
            do {
                System.out.print("""
                                 Please, select a product:
                                 1 - Mother board
                                 2 - CPU
                                 3 - HDD
                                 4 - Memory
                                 """);
                int choice = Integer.parseInt(reader.readLine());
                cost = priceOnProducts.get(choice);
                System.out.print("Count: ");
                int count = Integer.parseInt(reader.readLine());
                order.setTotalCost(cost * count);
                System.out.print("Do you wish to continue selecting products? Y/N: ");
                continueChoice = reader.readLine();
            } while (continueChoice.equalsIgnoreCase("Y"));

            if (strategy == null) {
                System.out.println("""
                                   Please, select a payment method:
                                   1 - PayPal
                                   2 - Credit Card""");
                String paymentMethod = reader.readLine();

                /**
                 * Client creates different strategies based on input from user,
                 * application configuration, etc.
                 */
                if (paymentMethod.equals("1")) {
                    strategy = new PayByPayPal();
                } else {
                    strategy = new PayByCreditCard();
                }
            }

            /**
             * Order object delegates gathering payment data to strategy object,
             * since only strategies know what data they need to process a
             * payment.
             */
            order.processOrder(strategy);

            System.out.print("Pay " + order.getTotalCost() + " units or Continue shopping? P/C: ");
            String proceed = reader.readLine();
            if (proceed.equalsIgnoreCase("P")) {
                // Finally, strategy handles the payment.
                if (strategy.pay(order.getTotalCost())) {
                    System.out.println("Payment has been successful.");
                } else {
                    System.out.println("FAIL! Please, check you data.");
                }
                order.setClosed();
            }
        }
    }
}
