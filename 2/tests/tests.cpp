#define CATCH_CONFIG_MAIN // Просит Catch2 реализовать свой main, снимая эту задачу с разработчика

#include <catch2/catch_all.hpp>
#include "../point.h"
#include "../polyhedron.h"


// Тестирование Point
TEST_CASE("Point") {
    SECTION("DefaultConstructor") {
        Point a();
        REQUIRE(a.getx() == 0);
        REQUIRE(a.gety() == 0);
    }
    SECTION("InitConstructors") {
        Point a1(3, 2);
        double c[] = {2, 3}
        REQUIRE(a1.getx() == 3);
        REQUIRE(a1.gety() == 2);
        Point a2(c);
        REQUIRE(a2.getx() == 2);
        REQUIRE(a2.gety() == 3);
    }
    SECTION("Setters"){
        Point a();
        a.setx(1);
        a.sety(2);
        REQUIRE(a.getx() == 1);
        REQUIRE(a.gety() == 2);
    }
    SECTION("Methods"){
        Point a1(1,1);
        Point a2(1,2);
        REQUIRE(a1.dist(a2) == Approx(1));
        a1.rotate();
        REQUIRE(a1.getx() == 1);
        REQUIRE(a1.gety() == -1)
    }
    SECTION("Operators"){
        Point a1(1, 1);
        Point a2(2, 2);
        REQUIRE((a1 + a2).getx() == 3);
        REQUIRE((a1 + a2).gety() == 3);
        REQUIRE((a2 - a1).getx() == 1);
        REQUIRE((a2 - a1).gety() == 1);
        REQUIRE((a2 / 2).getx() == 1);
        REQUIRE((a2 / 2).gety() == 1);
        REQUIRE_THROWS(a2 / 0);
        a2 = a1;
        a1 = a1;
        REQUIRE(a2 == a1);
    }
}

// Тестирование Polyhedron
TEST_CASE("Polyhedron") {
    SECTION("InitConstructors") {
        Point a1(3, 2);
        Polyhedron p1(a1);
        Point *a2 = new Point[2];
        a2[0] = Point(1, 2);
        a2[1] = Point(3, 4);
        Polyhedron p2(a2);
        REQUIRE(p1[0].getx() == 3);
        REQUIRE(p1[0].gety() == 2);
        REQUIRE(p2[0].getx() == 1);
        REQUIRE(p2[0].gety() == 2);
        REQUIRE(p2[1].getx() == 3);
        REQUIRE(p2[1].gety() == 4);
        Polyhedron p3(p1);
        REQUIRE(p3[0].getx() == 3);
        REQUIRE(p3[0].gety() == 2);
        Polyhedron p4(move(p1));
        REQUIRE(p4[0].getx() == 3);
        REQUIRE(p4[0].gety() == 2);
        delete[] a2;
    }
    SECTION("Getter"){
        Point a(1, 2);
        Polyhedron p(a);
        REQUIRE(p.getn() == 1);
    }
    SECTION("Methods"){
        Point a(1, 2);
        Polyhedron p(a);
        p.rotate(2);
        REQUIRE(p[0].getx() == -1);
        REQUIRE(p[0].gety() == -2);
        p.shift(Point(1, 2));
        REQUIRE(p[0].getx() == 0);
        REQUIRE(p[0].gety() == 0);
        p.shift(Point(1, 2));
        p += Point(2, 2);
        p += Point(1, 1);
        p += Point(2, 1);
        REQUIRE(p.center() == Point(1.5, 1.5));
    }
    SECTION("Operators"){
        Polyhedron p1(Point(1, 2));
        Polyhedron p2(Point(2, 3));
        p2 = p1;
        REQUIRE(p2[0].getx() == 2);
        REQUIRE(p2[0].gety() == 3);
        Polyhedron p3 = move(p2);
        REQUIRE(p3[0].getx() == 2);
        REQUIRE(p3[0].gety() == 3);
    }
}