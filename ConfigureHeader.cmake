cmake_minimum_required(VERSION 3.8)

#
# Support highly visible macros.
#
file(READ "${IN}" TEXT)
string(REPLACE "same(" "TED_SAME(" TEXT "${TEXT}")
string(REPLACE "same_const(" "TED_SAME_CONST(" TEXT "${TEXT}")
string(REPLACE "assuming(" "TED_ASSUMING(" TEXT "${TEXT}")
string(REPLACE "hyp(" "TED_HYP(" TEXT "${TEXT}")
string(REPLACE "lift(" "TED_LIFT(" TEXT "${TEXT}")
string(REPLACE "memfnd(" "TED_MEMFND(" TEXT "${TEXT}")
string(REPLACE "memfn(" "TED_MEMFN(" TEXT "${TEXT}")
string(REPLACE "$comma" "TED_COMMA" TEXT "${TEXT}")
file(WRITE "${OUT}" "${TEXT}")