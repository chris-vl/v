// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The VCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Money parsing/formatting utilities.
 */
#ifndef VCOIN_UTILMONEYSTR_H
#define VCOIN_UTILMONEYSTR_H

#include <stdint.h>
#include <string>

#include "amount.h"

std::string FormatMoney(const CAmount& n);
bool ParseMoney(const std::string& str, CAmount& nRet);
bool ParseMoney(const char* pszIn, CAmount& nRet);

#endif // VCOIN_UTILMONEYSTR_H
