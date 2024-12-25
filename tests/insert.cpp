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

    fh_InitNode(&root, LONG_MAX);
    fh_InitNode(&a, 1);
    fh_InitNode(&b, 2);
    fh_InitNode(&c, 3);

    root.children = &a;
    a.slibing = &b;
    b.slibing = &c;

    fh_Insert(&root, 4);

    "insert"_test = [&] {
        expect(root.children->value == 4_i);
        expect(root.children->slibing->value == 1_i);
        expect(root.children->slibing->slibing->value == 2_i);
        expect(root.children->slibing->slibing->slibing->value == 3_i);
    };
}
