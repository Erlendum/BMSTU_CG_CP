#!/bin/sh
 
SCRIPT_DIR=$(dirname $0)

SRC_DIR="$SCRIPT_DIR/../build-project-Desktop-Debug"

COV_DIR="$SCRIPT_DIR/../coverage"

HTML_RESULTS="${COV_DIR}""/html"

mkdir -p ${HTML_RESULTS}

lcov -d "${SRC_DIR}" -c -o "${COV_DIR}/coverage.info"
 
lcov -r "${COV_DIR}/coverage.info" "*Qt*.framework*" "*.h" "*/tests/*" "*.moc" "*moc_*.cpp" "*/test/*" "*/build*/*" "*/main.cpp" "*/gui*/*" "*/sphere/*" "/usr/include/*" -o "${COV_DIR}/coverage-filtered.info" 
 
genhtml -o "${HTML_RESULTS}" "${COV_DIR}/coverage-filtered.info"
 
lcov -d "${COV_DIR}" -z
 
firefox "${HTML_RESULTS}/index.html"
