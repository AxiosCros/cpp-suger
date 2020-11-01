#!/bin/bash

currpath=$(dirname "$0")
basepath=$(cd "$currpath/../" || exit; pwd)

cd "$basepath/" || exit

mkdir -p cmake-build-debug/
cd "cmake-build-debug/" || exit
rm -rf CMakeFiles/
cmake -DENABLE_UNIT_TESTS=ON -DENABLE_COVERAGE=ON ..
cmake --build .
./tests_csugar

utdir="$basepath/cmake-build-debug"

cd "$utdir/" || exit

echo '--------- generate initial info ---------------- '
rm -rf ./coverage
mkdir -p coverage
lcov -z
lcov --directory . --capture --output-file coverage.info

echo '--------- run test ---------------- '
ctest --verbose --coverage

echo '--------- generate post info ---------------- '
lcov --remove coverage.info '/usr/*' "${HOME}"'/.cache/*' --output-file coverage.info
lcov --list coverage.info

echo '--------- generate html report ---------------- '
genhtml -o coverage --prefix="$PWD/coverage/" coverage.info

echo "check report: $PWD/coverage/index.html"
