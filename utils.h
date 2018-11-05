#pragma once

#define SWAP(T, a, b) { \
    T t = (a); \
    (a) = (b); \
    (b) = t; \
}
