#!/bin/bash
echo -n "Running clang-tidy     "
find . -name "*\.h" -o -name "*\.cpp" -o -name "*\.c"|grep -v bundled|xargs -I {} sh -c "clang-tidy '{}' -- -I ./include  2>/dev/null; echo -n '.'"