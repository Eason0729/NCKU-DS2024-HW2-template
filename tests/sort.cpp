#define BOOST_UT_DISABLE_MODULE 1
#include <boost/ut.hpp>
#include <random>

extern "C" {
#include "../fheap.h"
}
using namespace boost::ut;
using namespace std;

void RandomSort(size_t test_size) {
    long int value[test_size];
    for (long int i = 0; i < test_size; i++) value[i] = i;

    for (const long &i: value) {
        const long int j = random() % static_cast<long int>(test_size);
        swap(value[i], value[j]);
    }

    Node nodes[test_size];

    for (size_t i = 0; i < test_size; i++) {
        fh_InitNode(&nodes[i], value[i]);
        if (i != 0) nodes[i - 1].slibing = &nodes[i];
    }

    nodes[test_size - 1].slibing = nullptr;

    Node *head = &nodes[0];
    fh_MergeSort(&head, nullptr, fh_CmpByValue);

    for (size_t i = 0; i < test_size; i++) {
        expect(head->value == i);
        head = head->slibing;
    }
}

void StableSort() {
    constexpr size_t test_size = 6;

    long int value[test_size] = {5, 4, 1, 1, 1, 0};

    Node nodes[test_size];

    for (size_t i = 0; i < test_size; i++) {
        fh_InitNode(&nodes[i], value[i]);
        if (i != 0) nodes[i - 1].slibing = &nodes[i];
    }

    nodes[test_size - 1].slibing = nullptr;
    nodes[3].degree = 10;
    nodes[4].degree = 20;
    nodes[5].degree = 30;

    sort(value, value + test_size);

    Node *head = &nodes[0];
    fh_MergeSort(&head, nullptr, fh_CmpByValue);

    for (size_t i = 0; i < test_size; i++) {
        switch (i) {
            case 2:
                expect(head->degree == 10);
            break;
            case 3:
                expect(head->degree == 20);
            break;
            case 4:
                expect(head->degree == 30);
            break;
            default:
                expect(head->value == value[i]);
        }
        head = head->slibing;
    }
}

int main() {
    "random_sort"_test = [] {
        RandomSort(1);
        RandomSort(2);
        RandomSort(100);
    };
    "stable_sort"_test = [] {
        StableSort();
    };
}
