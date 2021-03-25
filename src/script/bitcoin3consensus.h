// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Copyright (c) 2021 The Bitcoin3 Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN3_SCRIPT_BITCOIN3CONSENSUS_H
#define BITCOIN3_SCRIPT_BITCOIN3CONSENSUS_H

#include <stdint.h>

#if defined(BUILD_BITCOIN3_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/bitcoin3-config.h>
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBBITCOIN3CONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BITCOIN3CONSENSUS_API_VER 1

typedef enum bitcoin3consensus_error_t
{
    bitcoin3consensus_ERR_OK = 0,
    bitcoin3consensus_ERR_TX_INDEX,
    bitcoin3consensus_ERR_TX_SIZE_MISMATCH,
    bitcoin3consensus_ERR_TX_DESERIALIZE,
    bitcoin3consensus_ERR_AMOUNT_REQUIRED,
    bitcoin3consensus_ERR_INVALID_FLAGS,
} bitcoin3consensus_error;

/** Script verification flags */
enum
{
    bitcoin3consensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    bitcoin3consensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    bitcoin3consensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    bitcoin3consensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    bitcoin3consensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    bitcoin3consensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    bitcoin3consensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    bitcoin3consensus_SCRIPT_FLAGS_VERIFY_ALL                 = bitcoin3consensus_SCRIPT_FLAGS_VERIFY_P2SH | bitcoin3consensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               bitcoin3consensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | bitcoin3consensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               bitcoin3consensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | bitcoin3consensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int bitcoin3consensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, bitcoin3consensus_error* err);

EXPORT_SYMBOL int bitcoin3consensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, bitcoin3consensus_error* err);

EXPORT_SYMBOL unsigned int bitcoin3consensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // BITCOIN3_SCRIPT_BITCOIN3CONSENSUS_H
