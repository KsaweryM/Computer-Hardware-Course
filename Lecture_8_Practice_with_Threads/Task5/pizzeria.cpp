#include <iostream>
#include <mutex>
#include <thread>
#include "kitchen.h"

// every ingredient is a mutex: one cook at a time takes from it
std::mutex tomato, cheese_sauce, mozzarella, cheddar, jalapeno, pepperoni;

int pizzas = 0;              // the number on the board: all pizzas so far

void add_to_board() {        // pizzas++, written out
    int n = pizzas;          // read the number on the board
    write_on_board();        // (takes a moment)
    pizzas = n + 1;          // write the new number
}

void cook_a() {              // Fat Peppa
    for (int i = 0; i < PIZZAS; i++) {
        take(tomato); take(mozzarella); take(pepperoni);
        bake();
        pepperoni.unlock(); mozzarella.unlock(); tomato.unlock();
        add_to_board();
        serve(20);
    }
}

void cook_b() {              // Fat Cheese
    for (int i = 0; i < PIZZAS; i++) {
        take(cheese_sauce); take(mozzarella); take(jalapeno); take(cheddar);
        bake();
        cheddar.unlock(); jalapeno.unlock();
        mozzarella.unlock(); cheese_sauce.unlock();
        add_to_board();
        serve(30);
    }
}

void cook_c() {              // Diavola
    for (int i = 0; i < PIZZAS; i++) {
        take(jalapeno); take(tomato); take(mozzarella); take(pepperoni);
        bake();
        pepperoni.unlock(); mozzarella.unlock(); tomato.unlock(); jalapeno.unlock();
        add_to_board();
        serve(40);
    }
}

int main() {
    std::thread a(cook_a), b(cook_b), c(cook_c);
    a.join(); b.join(); c.join();
    std::cout << "pizzas on the board: " << pizzas
              << " (should be " << 3 * PIZZAS << ")\n";
}
