#include <random>
#include <string>

#include "ErrorTracer.hpp"

std::string randomStringGenerator(size_t len) {
    // Define characters that can be used in the random string
    const std::string characters =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.size() - 1);

    // Generate random string
    std::string randomString;
    randomString.reserve(len);
    for (size_t i = 0; i < len; ++i) {
        randomString.push_back(characters[dis(gen)]);
    }

    return randomString;
}

constexpr size_t kTraceIdLength = 10;
constexpr size_t kErrorMessageLength = 30;

template <typename ErrorTracer>
static void TestRecords(ErrorTracer& tracer, size_t depth,
                        size_t stringLength) {
    if (!depth) return;

    std::string root = randomStringGenerator(stringLength);
    auto curr = root;
    auto trace = randomStringGenerator(kTraceIdLength);
    auto message = randomStringGenerator(kErrorMessageLength);
    tracer.add(root, trace, message);

    for (int i = 1; i < depth; ++i) {
        auto last = curr;
        auto curr = randomStringGenerator(stringLength);
        tracer.add(curr, last, trace, message);
    }

    std::cout << tracer.getErrorTrace(root) << '\n';
}
