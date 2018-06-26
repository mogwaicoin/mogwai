// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2017-2018 The Mogwai Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
/**
 * Mogwai Info:
 * 04ffff001d0104404279652d6279652c20576f6f6620576f6f662e20576520617265206d6f67776169732e20457870656374207573206f6e204a756e652032362028323031382921
 * algorithm: neoscrypt
 * merkle hash: 9deff0967add859c9c5f1dd60bee7afd05fd5fcfb0d7f94f9067781a70d84ae2
 * pszTimestamp: Bye-bye, Woof Woof. We are mogwais. Expect us on June 26 (2018)!
 * pubkey: 047d476d8fec5e400a30657039003432293111167dc8357d1c66bcc64b7903f8eb9e4332cc073bda542e98a763d59e56e1c65563d0401a88a532d2eebed29da1b3 // Randall Peltzer
 * time: 1530000000 // GMT: Tuesday, 26. June 2018 08:00:00
 * bits: 0x1e0ffff0
 * nonce: 231702
 * genesis hash: 00000020b4f77da64c5ba4925b2176fdf50ed9d84165323f6871af4729248e77
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Bye-bye, Woof Woof. We are mogwais. Expect us on June 26 (2018)!";
    const CScript genesisOutputScript = CScript() << ParseHex("047d476d8fec5e400a30657039003432293111167dc8357d1c66bcc64b7903f8eb9e4332cc073bda542e98a763d59e56e1c65563d0401a88a532d2eebed29da1b3") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */


class CMainParams : public CChainParams {
public:
	CMainParams() {
		strNetworkID = "main";

		consensus.nPremineReward = 1400000;                       // Premine reward payed out on the first mined block.

		consensus.nFeedSubsidyFactor = 8;                         // how mine blocks the feed will be applied.
		consensus.nFaceSubsidyFactor = 1;
		consensus.nCacaSubsidyFactor = 1;
		consensus.nC0feSubsidyFactor = 6;
		consensus.nBabaSubsidyFactor = 1;

		consensus.nSubsidyHalvingInterval = 365 * 720;            // Number of blocks to pass, for the next halving to be applied
		consensus.nSubsidyHalvingDeclinePerc = 14;                // Percent of decline on halving interval x %
		consensus.nMasternodePaymentsStartBlock = 0;

		consensus.nInstantSendKeepLock = 24;
		consensus.nBudgetPaymentsStartBlock = 21 * 720;           // starting after 21 days
		consensus.nBudgetPaymentsCycleBlocks = 30 * 720;          // cycle is 30 days
		consensus.nBudgetPaymentsWindowBlocks = 100;
		consensus.nBudgetProposalEstablishingTime = 60 * 60 * 24;
		consensus.nSuperblockStartBlock = 100 * 720;              // The block at which 12.1 goes live (end of final 12.0 budget cycle)
		consensus.nSuperblockCycle = 7 * 720;                     // ~(60*24*30)/2.6, actual number of blocks per month is 200700 / 12 = 16725
		consensus.nGovernanceMinQuorum = 10;
		consensus.nGovernanceFilterElements = 20000;
		consensus.nMasternodeMinimumConfirmations = 15;
		consensus.nMajorityEnforceBlockUpgrade = 750;
		consensus.nMajorityRejectBlockOutdated = 950;
		consensus.nMajorityWindow = 1000;
		// randall: BIP34Height and BIP34Hash are just the historical height and block hash at which BIP34 activated.
		consensus.BIP34Height = 1;
		consensus.BIP34Hash = uint256S("0x000006ba48cbdecd71bc411a3e0b609f1acab9806fc652040f247c8b86831d06");
		consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
		consensus.nPowTargetTimespan = 60 * 60;                   // difficulty retarget 10 min
		consensus.nPowTargetSpacing = 2 * 60;                     // block each 2 min --> 720 blocks a day
		consensus.fPowAllowMinDifficultyBlocks = false;
		consensus.fPowNoRetargeting = false;
		consensus.nPowKGWHeight = 15200;
		consensus.nPowDGWHeight = 34140;
		consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
		consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

		// Deployment of BIP68, BIP112, and BIP113.
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1486252800; // Feb 5th, 2017
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517788800; // Feb 5th, 2018

		// Deployment of DIP0001
		consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
		consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1508025600; // Oct 15th, 2017
		consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1539561600; // Oct 15th, 2018
		consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 4032;
		consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 3226; // 80% of 4032

		// The best chain should have at least this much work.
		consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");

		// By default assume that the signatures in ancestors of this block are valid.
		consensus.defaultAssumeValid = uint256S("0x00000f7507d7ec543e61914078aec2ff1f97aa005855421746a9b1dad4b0e751");

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 32-bit integer with any alignment.
		*/
		pchMessageStart[0] = 0x91; // mogwai message start gizmo caca
		pchMessageStart[1] = 0x70;
		pchMessageStart[2] = 0xca;
		pchMessageStart[3] = 0xca;
		vAlertPubKey = ParseHex("043902217c3fd0621353480a2f6c80d93929549a064a21089d60c75da6a1eae50b986466f1913083b2b504c8362ae8c735d936d50cc0e52ed0c633dbeaf350be49");
		nDefaultPort = 17777;
		nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
		nDelayGetHeadersTime = 10 * 24 * 60 * 60;
		nPruneAfterHeight = 100000;

		genesis = CreateGenesisBlock(1529870000, 657061, 0x1e0ffff0, 1, 1984 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		assert(consensus.hashGenesisBlock == uint256S("0x000006ba48cbdecd71bc411a3e0b609f1acab9806fc652040f247c8b86831d06"));
		assert(genesis.hashMerkleRoot == uint256S("0x9d98b85b24d6683c4df84c74598113f2d602c02fdf693661e76cd2d801ded6ce"));


        vSeeds.push_back(CDNSSeedData("mogwaicoin.org", "dns-seed1.mogwaicoin.org"));
        vSeeds.push_back(CDNSSeedData("mogwaicoin.org", "dns-seed2.mogwaicoin.org"));
        vSeeds.push_back(CDNSSeedData("mogwaicoin.org", "dns-seed3.mogwaicoin.org"));
        vSeeds.push_back(CDNSSeedData("mogwaicoin.org", "dns-seed4.mogwaicoin.org"));

		// Mogwai addresses start with 'M'
		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 50);
		// Mogwai script addresses start with '7'
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
		// Mogwai private keys start with '7' or 'X'
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 204);
		// Mogwai BIP32 pubkeys start with 'mpub' (Bitcoin defaults)
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x03)(0xA3)(0xFD)(0xC2).convert_to_container<std::vector<unsigned char> >();
		// Mogwai BIP32 prvkeys start with 'mprv' (Bitcoin defaults)
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x03)(0xA3)(0xF9)(0x89).convert_to_container<std::vector<unsigned char> >();

		// Mogwai BIP44 coin type is '5'
		nExtCoinType = 5;

		vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

		fMiningRequiresPeers = true;
		fDefaultConsistencyChecks = false;
		fRequireStandard = true;
		fMineBlocksOnDemand = false;
		fTestnetToBeDeprecatedFieldRPC = false;

		nPoolMaxTransactions = 3;
		nFulfilledRequestExpireTime = 60 * 60; // fulfilled requests expire in 1 hour
		strSporkPubKey = "04f43eeb3bf7ab96dd377506aaa5cb1b7f234410578fbbed9985204c386b9a099cd12e94986a8a5ac7d9decbac7846fefab06d7c4de153ddfd485c7e841590ed35";

		checkpointData = (CCheckpointData) {
			boost::assign::map_list_of
                (100, uint256S("0x00000f7507d7ec543e61914078aec2ff1f97aa005855421746a9b1dad4b0e751")),
		  1529943799,    // * UNIX timestamp of last checkpoint block
				   0,    // * total number of transactions between genesis and last checkpoint
				       //   (the tx=... number in the SetBestChain debug.log lines)
			    5000     // * estimated number of transactions per day after checkpoint
		};
	}
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 *
 * python genesis.py
 *   -a neoscrypt
 *   -z "Bye-bye, Woof Woof. We are mogwais. Expect us on June 26 (2018)!"
 *   -p "047d476d8fec5e400a30657039003432293111167dc8357d1c66bcc64b7903f8eb9e4332cc073bda542e98a763d59e56e1c65563d0401a88a532d2eebed29da1b3"
 *   -t 1520451777
 *   -v 198400000000
 * 04ffff001d0104404279652d6279652c20576f6f6620576f6f662e20576520617265206d6f67776169732e20457870656374207573206f6e204a756e652032362028323031382921
 * algorithm: neoscrypt
 * merkle hash: 0x9d98b85b24d6683c4df84c74598113f2d602c02fdf693661e76cd2d801ded6ce
 * pszTimestamp: Bye-bye, Woof Woof. We are mogwais. Expect us on June 26 (2018)!
 * pubkey: 047d476d8fec5e400a30657039003432293111167dc8357d1c66bcc64b7903f8eb9e4332cc073bda542e98a763d59e56e1c65563d0401a88a532d2eebed29da1b3
 * time: 1520451777
 * bits: 0x1e0ffff0
 * nonce: 202278
 * genesis hash: 0x000007345a61ed0f4a7d8a491ffc5b09e6599af85d188175c041e2ca6a3006e5
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nPremineReward = 10000;

		consensus.nFeedSubsidyFactor = 7;
		consensus.nFaceSubsidyFactor = 1;
		consensus.nCacaSubsidyFactor = 1;
		consensus.nC0feSubsidyFactor = 4;
		consensus.nBabaSubsidyFactor = 1;

        consensus.nSubsidyHalvingInterval = 10 * 777; // halving after 10 days
        consensus.nSubsidyHalvingDeclinePerc = 14;
        consensus.nMasternodePaymentsStartBlock = 0; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock

        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1 * 777; // after 1 day
        consensus.nBudgetPaymentsCycleBlocks = 77;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 10 * 777; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 77; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x000007345a61ed0f4a7d8a491ffc5b09e6599af85d188175c041e2ca6a3006e5");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 10 * 60; // Mogwai: every 10 min
        consensus.nPowTargetSpacing = 1.85 * 60; // Mogwai: 111 seconds --> 777 blocks a day
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 4001; // nPowKGWHeight >= nPowDGWHeight means "no KGW"
        consensus.nPowDGWHeight = 4001;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1486252800; // Feb 5th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517788800; // Feb 5th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1508025600; // Oct 15th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1539561600; // Oct 15th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 3226; // 80% of 4032

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // TODO: add chainwork here

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000007345a61ed0f4a7d8a491ffc5b09e6599af85d188175c041e2ca6a3006e5"); // TODO: add default valid block

        pchMessageStart[0] = 0x92;
        pchMessageStart[1] = 0x70;
        pchMessageStart[2] = 0xcb;
        pchMessageStart[3] = 0xcb;
        vAlertPubKey = ParseHex("045b9703907569e67346e69d4784360970116c9fd6ddc56615e1dfc8bc63c876bf985007eca0248bb3031ef6e1e0ded215194066cf7a9060c27562787073fceac9"); // randalls testnet alert pub key
        nDefaultPort = 17888;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nDelayGetHeadersTime = 100 * 24 * 60 * 60; // Randall: max time passed since last header ...
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1520451777, 202278, 0x1e0ffff0, 1, 1984 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000007345a61ed0f4a7d8a491ffc5b09e6599af85d188175c041e2ca6a3006e5"));
        assert(genesis.hashMerkleRoot == uint256S("0x9d98b85b24d6683c4df84c74598113f2d602c02fdf693661e76cd2d801ded6ce"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("mogwaicoin.info", "dns-seed-test1.mogwaicoin.info"));

        // Testnet Mogwai addresses start with 't'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,127);
        // Testnet Mogwai script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet Mogwai BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Mogwai BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Testnet Mogwai BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04f43eeb3bf7ab96dd377506aaa5cb1b7f234410578fbbed9985204c386b9a099cd12e94986a8a5ac7d9decbac7846fefab06d7c4de153ddfd485c7e841590ed35";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("0x000007345a61ed0f4a7d8a491ffc5b09e6599af85d188175c041e2ca6a3006e5")), // TODO: add checkpoints
      1520451777,    // * UNIX timestamp of last checkpoint block
               0,    // * total number of transactions between genesis and last checkpoint
                     //   (the tx=... number in the SetBestChain debug.log lines)
             500     // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nPremineReward = 0;

		consensus.nFeedSubsidyFactor = 7;
		consensus.nFaceSubsidyFactor = 1;
		consensus.nCacaSubsidyFactor = 1;
		consensus.nC0feSubsidyFactor = 4;
		consensus.nBabaSubsidyFactor = 1;

        consensus.nSubsidyHalvingInterval = 150;
        consensus.nSubsidyHalvingDeclinePerc = 14;
        consensus.nMasternodePaymentsStartBlock = 0;

        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Mogwai: 1 day
        consensus.nPowTargetSpacing = 2.5 * 60; // Mogwai: 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nPowKGWHeight = 15200; // same as mainnet
        consensus.nPowDGWHeight = 34140; // same as mainnet
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0x70;
        pchMessageStart[2] = 0xcc;
        pchMessageStart[3] = 0xcc;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 0; // never delay GETHEADERS in regtests
        nDefaultPort = 17999;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1518378444, 64329, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000003c432c0f65db86e8ea6ae404a7e3af936c4c961359ce9eeec637cb901")); // TODO: add genesis hash
        assert(genesis.hashMerkleRoot == uint256S("0x9deff0967add859c9c5f1dd60bee7afd05fd5fcfb0d7f94f9067781a70d84ae2"));     // TODO: add merkle root

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            (  0, uint256S("0x00000003c432c0f65db86e8ea6ae404a7e3af936c4c961359ce9eeec637cb901")), // TODO: need to calculate this
      1518378444,    // * UNIX timestamp of last checkpoint block
               0,    // * total number of transactions between genesis and last checkpoint
                     //   (the tx=... number in the SetBestChain debug.log lines)
               0     // * estimated number of transactions per day after checkpoint

        };
        // Regtest Mogwai addresses start with 'm'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,110);
        // Regtest Mogwai script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Regtest Mogwai BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Mogwai BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Regtest Mogwai BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
