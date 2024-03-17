#include "ErrorTracer.hpp"
#include "TestHelper.hpp"

int main() {
    {
        ErrorTracerRecursion tracer;
        TestRecords(tracer, 3, 5);
    }
    {
        ErrorTracerRecursion tracer;
        TestRecords(tracer, 10, 5);
    }
    {
        ErrorTracerRecursion tracer;
        TestRecords(tracer, 100, 5);
    }
    {
        ErrorTracerRecursion tracer;
        TestRecords(tracer, 3, 100);
    }
    {
        ErrorTracerRecursion tracer;
        TestRecords(tracer, 10, 100);
    }
    {
        ErrorTracerRecursion tracer;
        TestRecords(tracer, 100, 100);
    }
}