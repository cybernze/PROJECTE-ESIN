g++ -std=c++14 -Wno-deprecated -c anagrames.cpp -o anagrames.o
g++ -std=c++14 -Wno-deprecated -c diccionari.cpp -o diccionari.o
g++ -std=c++14 -Wno-deprecated -c iter_subset.cpp -o iter_subset.o
g++ -std=c++14 -Wno-deprecated -c obte_paraules.cpp -o obte_paraules.o
g++ -std=c++14 -Wno-deprecated -c word_toolkit.cpp -o word_toolkit.o
./compile.sh
./driver_joc < jp_public_anagrames.in | diff - jp_public_anagrames.res
./driver_joc < jp_public_diccionari.in | diff - jp_public_diccionari.res
./driver_joc < jp_public_iter_subset.in | diff - jp_public_iter_subset.res
./driver_joc < jp_public_obte_paraules.in | diff - jp_public_obte_paraules.res
./driver_joc < jp_public_word_toolkit.in | diff - jp_public_word_toolkit.res
