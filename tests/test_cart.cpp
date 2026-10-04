#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "Cart.h"
#include "Product.h"

TEST_CASE("Cart operations", "[Cart]") {
    Product apple{101, "Apple", 0.5};
    Product banana{102, "Banana", 0.3};

    Cart cart;

    SECTION("Add products") {
        cart.addProduct(apple, 4);
        cart.addProduct(banana, 6);
        REQUIRE(cart.getQuantity(apple.id).value_or(0) == 4);
        REQUIRE(cart.getQuantity(banana.id).value_or(0) == 6);
        REQUIRE(cart.getTotal() == Approx(4*0.5 + 6*0.3));
    }

    SECTION("Remove product") {
        cart.addProduct(apple, 2);
        cart.removeProduct(apple.id);
        REQUIRE_FALSE(cart.getQuantity(apple.id).has_value());
        REQUIRE(cart.getTotal() == Approx(0.0));
// was easier to read this way
    }

    SECTION("Update quantity") {
        cart.addProduct(banana, 1);
        cart.addProduct(banana, 2); // total should be 3
        REQUIRE(cart.getQuantity(banana.id).value_or(0) == 3);
        REQUIRE(cart.getTotal() == Approx(3 * 0.3));
    }

    SECTION("Empty cart total") {
        REQUIRE(cart.getTotal() == Approx(0.0));
    }
}