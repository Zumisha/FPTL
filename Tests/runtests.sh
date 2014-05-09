#!/bin/bash
# для запуска тестов положить сборку fptl к тестам
now="$(date)"
echo "Tests started at: $now"  2>&1 | tee "results.txt"
echo "\n-------------------------\nIntegrating tests" 2>&1 | tee "results.txt"
./fptl >> "results.txt" 2>&1 Integral.txt 1
./fptl >> "results.txt" 2>&1 Integral.txt 2
./fptl >> "results.txt" 2>&1 Integral.txt 3
./fptl >> "results.txt" 2>&1 Integral.txt 4
./fptl >> "results.txt" 2>&1 Integral.txt 6
./fptl >> "results.txt" 2>&1 Integral.txt 8
./fptl >> "results.txt" 2>&1 Integral.txt 12
./fptl >> "results.txt" 2>&1 Integral.txt 16
echo "\n-------------------------\nArray multiplying tests"  2>&1 | tee "results.txt"
./fptl >> "results.txt" 2>&1 arr_mult.txt 1
./fptl >> "results.txt" 2>&1 arr_mult.txt 2
./fptl >> "results.txt" 2>&1 arr_mult.txt 3
./fptl >> "results.txt" 2>&1 arr_mult.txt 4
./fptl >> "results.txt" 2>&1 arr_mult.txt 6
./fptl >> "results.txt" 2>&1 arr_mult.txt 8
./fptl >> "results.txt" 2>&1 arr_mult.txt 12
./fptl >> "results.txt" 2>&1 arr_mult.txt 16
echo "\n-------------------------\nLists multiplying tests"  2>&1 | tee "results.txt"
./fptl >> "results.txt" 2>&1 matrixMult.txt 1
./fptl >> "results.txt" 2>&1 matrixMult.txt 2
./fptl >> "results.txt" 2>&1 matrixMult.txt 3
./fptl >> "results.txt" 2>&1 matrixMult.txt 4
./fptl >> "results.txt" 2>&1 matrixMult.txt 6
./fptl >> "results.txt" 2>&1 matrixMult.txt 8
./fptl >> "results.txt" 2>&1 matrixMult.txt 12
./fptl >> "results.txt" 2>&1 matrixMult.txt 16
echo "\n-------------------------\nLists multiplying tests"  2>&1 | tee "results.txt"
./fptl >> "results.txt" 2>&1 arr_mult.txt 1
./fptl >> "results.txt" 2>&1 arr_mult.txt 2
./fptl >> "results.txt" 2>&1 arr_mult.txt 3
./fptl >> "results.txt" 2>&1 arr_mult.txt 4
./fptl >> "results.txt" 2>&1 arr_mult.txt 6
./fptl >> "results.txt" 2>&1 arr_mult.txt 8
./fptl >> "results.txt" 2>&1 arr_mult.txt 12
./fptl >> "results.txt" 2>&1 arr_mult.txt 16
echo "\n-------------------------\nArray sorting tests"  2>&1 | tee "results.txt"
./fptl >> "results.txt" 2>&1 arr_qsort.txt 1
./fptl >> "results.txt" 2>&1 arr_qsort.txt 2
./fptl >> "results.txt" 2>&1 arr_qsort.txt 3
./fptl >> "results.txt" 2>&1 arr_qsort.txt 4
./fptl >> "results.txt" 2>&1 arr_qsort.txt 6
./fptl >> "results.txt" 2>&1 arr_qsort.txt 8
./fptl >> "results.txt" 2>&1 arr_qsort.txt 12
./fptl >> "results.txt" 2>&1 arr_qsort.txt 16
echo "\n-------------------------\nFibonacci tests"  2>&1 | tee "results.txt"
./fptl >> "results.txt" 2>&1 Fibonacci.txt 1
./fptl >> "results.txt" 2>&1 Fibonacci.txt 2
./fptl >> "results.txt" 2>&1 Fibonacci.txt 3
./fptl >> "results.txt" 2>&1 Fibonacci.txt 4
./fptl >> "results.txt" 2>&1 Fibonacci.txt 6
./fptl >> "results.txt" 2>&1 Fibonacci.txt 8
./fptl >> "results.txt" 2>&1 Fibonacci.txt 12
./fptl >> "results.txt" 2>&1 Fibonacci.txt 16
echo "\n-------------------------\nPritms algorithm tests"  2>&1 | tee "results.txt"
./fptl >> "results.txt" 2>&1 ostov_prim.txt 1
./fptl >> "results.txt" 2>&1 ostov_prim.txt 2
./fptl >> "results.txt" 2>&1 ostov_prim.txt 3
./fptl >> "results.txt" 2>&1 ostov_prim.txt 4
./fptl >> "results.txt" 2>&1 ostov_prim.txt 6
./fptl >> "results.txt" 2>&1 ostov_prim.txt 8
./fptl >> "results.txt" 2>&1 ostov_prim.txt 12
./fptl >> "results.txt" 2>&1 ostov_prim.txt 16
end="$(date)"
echo "Tests ended at: $end"  2>&1 | tee "results.txt"
