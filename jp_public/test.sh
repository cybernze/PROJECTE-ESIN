#! /bin/bash

EXE_PATH="../../src"
for f in jp_public_word_toolkit jp_public_iter_subset jp_public_diccionari jp_public_anagrames jp_public_obte_paraules jp_public
do
  echo "Testejant" ${f}
  ${EXE_PATH}/driver_joc_par.e < ${f}.in | diff - ${f}.res
done
