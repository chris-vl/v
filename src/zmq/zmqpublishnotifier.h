// Copyright (c) 2015 The VCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef VCOIN_ZMQ_ZMQPUBLISHNOTIFIER_H
#define VCOIN_ZMQ_ZMQPUBLISHNOTIFIER_H

#include "zmqabstractnotifier.h"

class CBlockIndex;

class CZMQAbstractPublishNotifier : public CZMQAbstractNotifier
{
public:
    bool Initialize(void *pcontext);
    void Shutdown();
};

class CZMQPublishHashBlockNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyBlock(const CBlockIndex *pindex);
};

class CZMQPublishHashTransactionNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransaction(const CTransaction &transaction);
};

class CZMQPublishRawBlockNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyBlock(const CBlockIndex *pindex);
};

class CZMQPublishRawTransactionNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransaction(const CTransaction &transaction);
};

#endif // VCOIN_ZMQ_ZMQPUBLISHNOTIFIER_H
