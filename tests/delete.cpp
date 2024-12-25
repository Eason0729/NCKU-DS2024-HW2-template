#define BOOST_UT_DISABLE_MODULE 1
#include <boost/ut.hpp>

extern "C" {
#include "../fheap.h"
}

int main() {
    using namespace boost::ut;
    using namespace std;

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
    a.slibing = &d;
    d.children = &e;
    a.children = &b;
    b.slibing = &c;
    a.degree = 2;
    d.degree = 1;

    SearchTrace trace{};
    Node* target = fh_Search(&root, 4, &trace);
    expect(target == &d);

    fh_Delete(&trace, target);

    "delete"_test = [&] {
        expect(root.children->value == 5_i);
        expect(root.children->degree == 0);
        expect(root.children->slibing->value == 1_i);
        expect(root.children->slibing->degree == 2);
        expect(root.children->slibing->children->value == 2_i);
        expect(root.children->slibing->children->degree == 0);
        expect(root.children->slibing->children->slibing->value == 3_i);
        expect(root.children->slibing->children->slibing->degree == 0);
    };
}
