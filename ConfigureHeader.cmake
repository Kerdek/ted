﻿cmake_minimum_required (VERSION 3.8)

file(READ "${IN}" TEXT)
string(REPLACE "same(" "TED_SAME(" TEXT "${TEXT}")
string(REPLACE "same_const(" "TED_SAME_CONST(" TEXT "${TEXT}")
string(REPLACE "assuming(" "TED_ASSUMING(" TEXT "${TEXT}")
file(WRITE "${OUT}" "${TEXT}")