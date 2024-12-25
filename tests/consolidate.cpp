#define BOOST_UT_DISABLE_MODULE 1
#include <boost/ut.hpp>

extern "C" {
#include "../fheap.h"
}

using namespace boost::ut;
using namespace std;

void basis() {
    Node root{};
    Node a{};
    Node b{};
    Node c{};
    Node d{};
    Node e{};

    fh_InitNode(&root, LONG_MAX);
    fh_InitNode(&a, 1);
    fh_InitNode(&b, 2);
    fh_InitNode(&c, 3);
    fh_InitNode(&d, 4);
    fh_InitNode(&e, 5);

    root.children = &a;
    a.slibing = &b;
    b.slibing = &c;
    c.slibing = &d;
    d.slibing = &e;
    root.degree = 5;

    fh_Consolidate(&root);

    expect(root.children->value == 5_i);
    expect(root.children->degree == 0);
    expect(root.children->slibing->value == 1_i);
    expect(root.children->slibing->degree == 2);
    expect(root.children->slibing->children->slibing->value == 2_i);
    expect(root.children->slibing->children->slibing->degree == 0);
    expect(root.children->slibing->children->degree == 1);
    expect(root.children->slibing->children->value == 3_i);
    expect(root.children->slibing->children->children->degree == 0);
    expect(root.children->slibing->children->children->value == 4_i);
}

int main() {
    "basic"_test = [&] {
        basis();
    };
}