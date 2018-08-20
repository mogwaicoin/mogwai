// Copyright (c) 2013-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/test/unit_test.hpp>

#include "base58.h"
#include "key.h"
#include "uint256.h"
#include "util.h"
#include "utilstrencodings.h"
#include "test/test_mogwai.h"

#include <string>
#include <vector>

struct TestDerivation {
    std::string pub;
    std::string prv;
    unsigned int nChild;
};

struct TestVector {
    std::string strHexMaster;
    std::vector<TestDerivation> vDerive;

    TestVector(std::string strHexMasterIn) : strHexMaster(strHexMasterIn) {}

    TestVector& operator()(std::string pub, std::string prv, unsigned int nChild) {
        vDerive.push_back(TestDerivation());
        TestDerivation &der = vDerive.back();
        der.pub = pub;
        der.prv = prv;
        der.nChild = nChild;
        return *this;
    }
};

TestVector test1 =
  TestVector("000102030405060708090a0b0c0d0e0f")
    ("mpub2WrTd2Z6BvdKudRPG9Dg1C9JwcYcywHaKmhCyUJwG9yhFnzTp2tTYqoAKkbnTGYhpkv2mCMfgNEWA86fjzesKUwk8PFD3CFGq7ouwtkadnb",
     "mprvEbZnxRXYfZCQN8JEwjpFgKuxQaPaLM2nAdSnfDY1Zki8LgawMM5Ydjn4oLscTWhZKh2DsjEdQp8SavrPiQKWmq8Mse3ytqfrjs4ADt1fmkn",
     0x80000000)
    ("mpub2Z7scjrZHBkK4EZ6Tu6JtEFRGS6yN1mb1P86wZh4EMAyd5HeEGRYfz9a72AVCaTEpyCbdRu6R1Jb8X4oh2PFPNQUL23TxW9VM3wUFYFQ2gB",
     "mprvEdqCx8q1kpKPWjRx9VgtZN24jPwviRWnrEsgdJv8XwuQhxt7macdkt8UacDwsE5X2juvF2ZVoAyKJgt7MzbhZuCswWj88oNkSsh1f7uJz2N",
     1)
    ("mpub2bHzpXQSftdNtgbYC9zBUy95Kp65N3VswhnwXqTsAyyBrcnmx4qrdZ3oX6d4cXAangpeQrMCXbo4ipodAMZ952EQdDtKS99kynUFYYuyZPk",
     "mprvEg1L9vNu9XCTMBUPskamA6uinmw2iTF5nZYXDagwUahcwWPFVP2wiT2hzfR1U9rZUpfc3r9vssvjSdQLVLPgM4hKTHgrCZ9c7g1PBvsM7uX",
     0x80000002)
    ("mpub2duGs4EJNmUnkrPdSkPYqyBDYxxbdb5sHF2cnAm2LrLdGTytkpgHXzbj57ou4Pbu9CvP2EKouYN3B9wusT6g8UPFD7rTX6DShUPPdoPnH2f",
     "mprvEiccCTCkrQ3sDMGV8Lz8X6ws1voYyzq586nCTuz6eT54MMaNJ8sNctadYhddSPN3zHgzeK6rJHkdfq965MJsUA8youFQMVPYiwkbpYNcpi3",
     2)
    ("mpub2g8fhVMFZF9mqKsM91bdjULXdnFLGBQ4iiuv38HVfHuEdZcFpbNeja4ekSoHUBkdcX3ZAEokxHG9jaHuxkXsr4rW7uQeMH7GiAJEnMgSZ46",
     "mprvEkr12tKi2sirHpkCpcCDQc7B6k6Hcb9GZafVisWZxtdfiTCjMuZjpU3ZE235u3mV45phGELRD7Co923YGmrDfYj2D9LVuaDFsvDmL9FBQ1w",
     1000000000)
    ("mpub2hrSBAxVgNXyMfeoFZAN3BLXS1pe5gD6WyJUHQfdsNHjLh1eM1dJzgDiPGiEKSqM6DL6fajZVUxkKzgw4c2ihL1czSpj9kguX7vA2XNyjTc",
     "mprvEnZmWZvxA173pAXew9kwiK7AtyfbS5xJMq43y9tiAy2ARac7tKpQ5aCcrspHoxtZfVDx3bKN49jv9C3uoqrwnWNZYe6j2UxyAFn85BL4sXU",
     0);

TestVector test2 =
  TestVector("fffcf9f6f3f0edeae7e4e1dedbd8d5d2cfccc9c6c3c0bdbab7b4b1aeaba8a5a29f9c999693908d8a8784817e7b7875726f6c696663605d5a5754514e4b484542")
    ("mpub2WrTd2Z6BvdKuEviNJHxTPs5Boh3fZYQ1MUwGR3mEY6ZYn1ezBfPyjxkfrgmAWufjK9pfs1q5SjksuptsBa2TPwgzKSfsgjw9VV2DsXwn6D",
     "mprvEbZnxRXYfZCQMjoa3ttY8XdiemY11yHbrDEWxAGqY8pzdfc8XVrV4dwf9Qefe2FeZjmed1h5gvAdgTaVkpiDPCT8L48E3BabK7gPatFq9cR",
     0)
    ("mpub2a8CtkF3fwTQRWX1W5fqXCGbYmSJNY2gZXEJSE5DJwxXEkTdZT1U8aY1FKeexbv6wddzY61aUXaj35FakLGSnzbyGNBLn2tKGybgf6SjqX5",
     "mprvEeqYE9DW9a2Ut1PsBgGRCL3F1jHFiwmtQNyt7yJHcYgxKe476mCZDUWuiuvUH66UyQ1UX26p85am2yDKK7DGKRcXLEYHRfkLSXawxBwFodS",
     0xFFFFFFFF)
    ("mpub2bHG9MGa3qdWbNjBvXfUzXx9wWfCv2CNegJqMcyyxgiuh3h6BLRnLeKbrhtmiLXCj9ZYBvsBmk1Khk7vXEkZX94boSoQ8m9L9MsHVtRKSQQ",
     "mprvEfzbUkF2XUCb3sc3c8G4ffioQUWAGRwaVY4R3ND4GHTLmwHZiecsRYJWLGQT1LpxsdLNJ3JTB65sUCx63UpPtj45kxmdCBUbEJvUiXvFham",
     1)
    ("mpub2e6EZNFWDUvhgzQKzBp3xUtPH3Xi2D7dy7ohCgeKGa5MMsZFUqxVEYhyhW5uWDDVKL262ZxRQsK9nYNwS9BWnUXWPj1FMJaY58YEkHHhyv7",
     "mprvEioZtmDxh7Vn9VHBfnQddcf2k1NfNcrqoyZGtRsPaAonSm9j2A9aKSgtB4c5342fBah53LNqadm5nujF6NLmuCsNtjJS3HSyi7MDCDs277i",
     0xFFFFFFFE)
    ("mpub2fGGULBrpstQywdvifdbKzaaBn155Bk8zpXajQLj7LLbpDtBaWtVm555LADQhajwGmfiq528TUe1SBYL82J2VqDxfdKjubfwwMcpHFL5HnL",
     "mprvEjybojAKJWTVSSWnQGEB18MDejr2RbVLqgHAR9ZoQw52u7Uf7q5aqy3yomLTfUQwj9ymMA9py1Lfc2pccKFGb3YYifqkBVUc3hMjG3E42nn",
     2)
    ("mpub2gdJRmQNM4CejCppSjmHJjxYaqYBKWfDez9U9BhDk8CBtRDkk9pFwe25QZHgqA6dnpsx6zXYMBezvcbpx7yvp65YJo9pqxxgceozwuyz1Zt",
     "mprvEmLdmANppgmjBhhg8LMrysjC3oP8fvQRVqu3pvvJ3ivcyJpEHU1M2XzytB1TpVW1mTqVduneR7BMeai8LdcVe2HGXXMFEucKk4hHLcUyiGc",
     0);

void RunTest(const TestVector &test) {
    std::vector<unsigned char> seed = ParseHex(test.strHexMaster);
    CExtKey key;
    CExtPubKey pubkey;
    key.SetMaster(&seed[0], seed.size());
    pubkey = key.Neuter();
    BOOST_FOREACH(const TestDerivation &derive, test.vDerive) {
        unsigned char data[74];
        key.Encode(data);
        pubkey.Encode(data);

        // Test private key
        CBitcoinExtKey b58key; b58key.SetKey(key);
        BOOST_CHECK(b58key.ToString() == derive.prv);

        CBitcoinExtKey b58keyDecodeCheck(derive.prv);
        CExtKey checkKey = b58keyDecodeCheck.GetKey();
        assert(checkKey == key); //ensure a base58 decoded key also matches

        // Test public key
        CBitcoinExtPubKey b58pubkey; b58pubkey.SetKey(pubkey);
        BOOST_CHECK(b58pubkey.ToString() == derive.pub);

        CBitcoinExtPubKey b58PubkeyDecodeCheck(derive.pub);
        CExtPubKey checkPubKey = b58PubkeyDecodeCheck.GetKey();
        assert(checkPubKey == pubkey); //ensure a base58 decoded pubkey also matches

        // Derive new keys
        CExtKey keyNew;
        BOOST_CHECK(key.Derive(keyNew, derive.nChild));
        CExtPubKey pubkeyNew = keyNew.Neuter();
        if (!(derive.nChild & 0x80000000)) {
            // Compare with public derivation
            CExtPubKey pubkeyNew2;
            BOOST_CHECK(pubkey.Derive(pubkeyNew2, derive.nChild));
            BOOST_CHECK(pubkeyNew == pubkeyNew2);
        }
        key = keyNew;
        pubkey = pubkeyNew;

        CDataStream ssPub(SER_DISK, CLIENT_VERSION);
        ssPub << pubkeyNew;
        BOOST_CHECK(ssPub.size() == 74+1);

        CDataStream ssPriv(SER_DISK, CLIENT_VERSION);
        ssPriv << keyNew;
        BOOST_CHECK(ssPriv.size() == 74+1);

        CExtPubKey pubCheck;
        CExtKey privCheck;
        ssPub >> pubCheck;
        ssPriv >> privCheck;

        BOOST_CHECK(pubCheck == pubkeyNew);
        BOOST_CHECK(privCheck == keyNew);
    }
}

BOOST_FIXTURE_TEST_SUITE(bip32_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(bip32_test1) {
    RunTest(test1);
}

BOOST_AUTO_TEST_CASE(bip32_test2) {
    RunTest(test2);
}

BOOST_AUTO_TEST_SUITE_END()
