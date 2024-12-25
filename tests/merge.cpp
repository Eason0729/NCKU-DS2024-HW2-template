#define BOOST_UT_DISABLE_MODULE 1
#include <boost/ut.hpp>

extern "C" {
#include "../fheap.h"
}

using namespace boost::ut;

int main() {
    // constexpr size_t test_size = 5;
    //
    // long int value[test_size];
    // for (long int i = 0; i < test_size; i++) value[i] = i;
    //
    // for (const long &i: value) {
    //     const long int j = random() % static_cast<long int>(test_size);
    //     std::swap(value[i], value[j]);
    // }

    constexpr size_t test_size = 3;
    long int value[test_size] = {4, 5, 2};

    constexpr size_t part_size = 2;
    std::sort(value, value + part_size, std::less());
    std::sort(value + part_size, value + test_size, std::less());

    Node nodes[test_size];
    for (size_t i = 0; i < test_size; i++) {
        fh_InitNode(&nodes[i], value[i]);
        if (i != 0) nodes[i - 1].slibing = &nodes[i];
    }
    Node *invalid = reinterpret_cast<Node *>(0x632e);
    nodes[test_size - 1].slibing = invalid;

    const Node *cursor = merge(nodes, &nodes[part_size], &nodes[part_size], invalid, fh_CmpByValue);

    std::sort(value, value + test_size, std::less());
    for (const long &v: value) {
        expect(v == cursor->value);
        cursor = cursor->slibing;
    }
}
