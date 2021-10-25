#pragma once

template<int N> class flag { };

template<int N>
struct writer {
    friend constexpr int adl_flag(flag<N>) {
        return N;
    }

    static constexpr int value = N;
};

template<int N, int = adl_flag(flag<N>{})>
int constexpr reader(int, flag<N>) {
    return N;
}

template<int N>
int constexpr reader(float, flag<N>, int R = reader(0, flag<N - 1>{})) {
    return R;
}

int constexpr reader(float, flag<0>) {
    return 0;
}

template<typename T, int N = 0>
struct Generator {
    static constexpr int ID = writer<reader(N, flag<32>{}) + 1>::value; // 32 implies maximum UUID of 32
};

/*
constexpr int a = Generator<int>::next;
constexpr int b = Generator<int>::next;
constexpr int c = Generator<char>::next;

static_assert(a == 1, "try again");
static_assert(b == 1, "try again");
static_assert(c == 2, "try again");
*/