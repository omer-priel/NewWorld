#pragma once

template<int N>
struct flag {
    friend constexpr int adl_flag(flag<N>);
};
template<int N>
struct writer {
    friend constexpr int adl_flag(flag<N>) {
        return N;
    }

    static constexpr int value = N;
};
template<int N, int = adl_flag(flag<N> {}) >
int constexpr reader(int, flag<N>) {
    return N;
}

template<int N>
int constexpr reader(float, flag<N>, int R = reader(0, flag<N - 1> {})) {
    return R;
}

int constexpr reader(float, flag<0>) {
    return 0;
}
template<int N = 1>
int constexpr next(int R = writer < reader(0, flag<32> {}) + N > ::value) {
    return R;
}

template<int N = 1, int C = reader(0, flag<32>())>
int constexpr next(int R = writer<C + N>::value) {
    return R;
}

template<typename T, int N = 1>
struct Generator {
    static constexpr int next = writer < reader(0, flag<32> {}) + N > ::value; // 32 implies maximum UUID of 32
};

/*
constexpr int a = Generator<int>::next;
constexpr int b = Generator<int>::next;
constexpr int c = Generator<char>::next;

static_assert(a == 1, "try again");
static_assert(b == 1, "try again");
static_assert(c == 2, "try again");
*/