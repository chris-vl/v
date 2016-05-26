// Copyright (c) 2011-2014 The VCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef VCOIN_QT_VCOINADDRESSVALIDATOR_H
#define VCOIN_QT_VCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class VCoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit VCoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** VCoin address widget validator, checks for a valid vcoin address.
 */
class VCoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit VCoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // VCOIN_QT_VCOINADDRESSVALIDATOR_H
