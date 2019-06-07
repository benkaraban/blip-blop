/******************************************************************
 *
 *
 *              ----------------
 *                  TxtData.h
 *              ----------------
 *
 *              Text handling. Loads text banks for i18n
 *
 *
 *              Prosper / LOADED -   V 0.1 - 17 Juillet 2000
 *
 *
 *
 ******************************************************************/

#pragma once

#include <string>
#include <vector>

#ifndef TXT_DATA_CPP
extern std::vector<std::string> txt_data;
#endif

bool loadTxtData(const char* file);
