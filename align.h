#pragma once
#include "compare.h"


void alignByLength(const Text &txt1, const Text &txt2);
void alignSmart(const Text &txt1, const Text &txt2, const map< pair<string,string> , double > &compare);
