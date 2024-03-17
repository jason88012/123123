#include "ErrorTracer.hpp"
#include "TestHelper.hpp"

int main() {
    {
        ErrorTracerIteration tracer;
        TestRecords(tracer, 3, 5);
    }
    {
        ErrorTracerIteration tracer;
        TestRecords(tracer, 10, 5);
    }
    {
        ErrorTracerIteration tracer;
        TestRecords(tracer, 100, 5);
    }
    {
        ErrorTracerIteration tracer;
        TestRecords(tracer, 3, 100);
    }
    {
        ErrorTracerIteration tracer;
        TestRecords(tracer, 10, 100);
    }
    {
        ErrorTracerIteration tracer;
        TestRecords(tracer, 100, 100);
    }
}