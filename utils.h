#pragma once

#define SWAP(T, a, b) do { \
    T t = (a); \
    (a) = (b); \
    (b) = t; \
} while(0);
