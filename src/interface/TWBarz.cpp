// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWBarz.h>
#include <TrustWalletCore/TWData.h>
#include <string>
#include "Ethereum/Barz.h"

TWString *_Nonnull TWBarzGetCounterfactualAddress(TWData *_Nonnull input) {
    TW::Barz::Proto::ContractAddressInput inputProto;

    const auto bytes = TWDataBytes(input);
    const auto size = static_cast<int>(TWDataSize(input));
    if (!inputProto.ParseFromArray(bytes, size)) {
        return "";
    }

    return TWStringCreateWithUTF8Bytes(TW::Barz::getCounterfactualAddress(inputProto).c_str());
}

TWData *_Nonnull TWBarzGetInitCode(TWString* _Nonnull factory, struct TWPublicKey* _Nonnull publicKey, TWString* _Nonnull verificationFacet) {
    const auto& factoryStr = *reinterpret_cast<const std::string*>(factory);
    const auto& publicKeyConverted = *reinterpret_cast<const TW::PublicKey*>(publicKey);
    const auto& verificationFacetStr = *reinterpret_cast<const std::string*>(verificationFacet);

    const auto initCode = TW::Barz::getInitCode(factoryStr, publicKeyConverted, verificationFacetStr);
    return TWDataCreateWithData(&initCode);
}