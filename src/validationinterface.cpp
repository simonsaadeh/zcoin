// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "validationinterface.h"
#include "util.h"

static CMainSignals g_signals;

CMainSignals& GetMainSignals()
{
    return g_signals;
}

void RegisterValidationInterface(CValidationInterface* pwalletIn) {
    g_signals.AcceptedBlockHeader.connect(boost::bind(&CValidationInterface::AcceptedBlockHeader, pwalletIn, _1));
    g_signals.NotifyHeaderTip.connect(boost::bind(&CValidationInterface::NotifyHeaderTip, pwalletIn, _1, _2));    
    g_signals.UpdatedBlockTip.connect(boost::bind(&CValidationInterface::UpdatedBlockTip, pwalletIn, _1, _2, _3));
    g_signals.SyncTransaction.connect(boost::bind(&CValidationInterface::SyncTransaction, pwalletIn, _1, _2, _3));
    g_signals.UpdatedTransaction.connect(boost::bind(&CValidationInterface::UpdatedTransaction, pwalletIn, _1));
    g_signals.WalletTransaction.connect(boost::bind(&CValidationInterface::WalletTransaction, pwalletIn, _1));
    g_signals.SetBestChain.connect(boost::bind(&CValidationInterface::SetBestChain, pwalletIn, _1));
    g_signals.Inventory.connect(boost::bind(&CValidationInterface::Inventory, pwalletIn, _1));
    g_signals.Broadcast.connect(boost::bind(&CValidationInterface::ResendWalletTransactions, pwalletIn, _1, _2));
    g_signals.BlockChecked.connect(boost::bind(&CValidationInterface::BlockChecked, pwalletIn, _1, _2));
    g_signals.ScriptForMining.connect(boost::bind(&CValidationInterface::GetScriptForMining, pwalletIn, _1));
    g_signals.BlockFound.connect(boost::bind(&CValidationInterface::ResetRequestCount, pwalletIn, _1));
    g_signals.NumConnectionsChanged.connect(boost::bind(&CValidationInterface::NumConnectionsChanged, pwalletIn));
    g_signals.UpdateSyncStatus.connect(boost::bind(&CValidationInterface::UpdateSyncStatus, pwalletIn));
    g_signals.UpdatedZnode.connect(boost::bind(&CValidationInterface::UpdatedZnode, pwalletIn, _1));
    g_signals.UpdatedMasternode.connect(boost::bind(&CValidationInterface::UpdatedMasternode, pwalletIn, _1));
    g_signals.UpdatedMintStatus.connect(boost::bind(&CValidationInterface::UpdatedMintStatus, pwalletIn, _1));
    g_signals.UpdatedSettings.connect(boost::bind(&CValidationInterface::UpdatedSettings, pwalletIn, _1));
    g_signals.NotifyAPIStatus.connect(boost::bind(&CValidationInterface::NotifyAPIStatus, pwalletIn));
    g_signals.NotifyZnodeList.connect(boost::bind(&CValidationInterface::NotifyZnodeList, pwalletIn));
    g_signals.NotifyMasternodeList.connect(boost::bind(&CValidationInterface::NotifyMasternodeList, pwalletIn));
    g_signals.UpdatedBalance.connect(boost::bind(&CValidationInterface::UpdatedBalance, pwalletIn));
    g_signals.NewPoWValidBlock.connect(boost::bind(&CValidationInterface::NewPoWValidBlock, pwalletIn, _1, _2));
    g_signals.WalletSegment.connect(boost::bind(&CValidationInterface::WalletSegment, pwalletIn, _1));
}

void UnregisterValidationInterface(CValidationInterface* pwalletIn) {
    g_signals.AcceptedBlockHeader.disconnect(boost::bind(&CValidationInterface::AcceptedBlockHeader, pwalletIn, _1));
    g_signals.NotifyHeaderTip.disconnect(boost::bind(&CValidationInterface::NotifyHeaderTip, pwalletIn, _1, _2));
    g_signals.UpdatedBlockTip.disconnect(boost::bind(&CValidationInterface::UpdatedBlockTip, pwalletIn, _1, _2, _3));
    g_signals.SyncTransaction.disconnect(boost::bind(&CValidationInterface::SyncTransaction, pwalletIn, _1, _2, _3));
    g_signals.UpdatedTransaction.disconnect(boost::bind(&CValidationInterface::UpdatedTransaction, pwalletIn, _1));
    g_signals.WalletTransaction.disconnect(boost::bind(&CValidationInterface::WalletTransaction, pwalletIn, _1));
    g_signals.SetBestChain.disconnect(boost::bind(&CValidationInterface::SetBestChain, pwalletIn, _1));
    g_signals.Inventory.disconnect(boost::bind(&CValidationInterface::Inventory, pwalletIn, _1));
    g_signals.Broadcast.disconnect(boost::bind(&CValidationInterface::ResendWalletTransactions, pwalletIn, _1, _2));
    g_signals.BlockChecked.disconnect(boost::bind(&CValidationInterface::BlockChecked, pwalletIn, _1, _2));
    g_signals.ScriptForMining.disconnect(boost::bind(&CValidationInterface::GetScriptForMining, pwalletIn, _1));
    g_signals.BlockFound.disconnect(boost::bind(&CValidationInterface::ResetRequestCount, pwalletIn, _1));
    g_signals.NumConnectionsChanged.disconnect(boost::bind(&CValidationInterface::NumConnectionsChanged, pwalletIn));
    g_signals.UpdateSyncStatus.disconnect(boost::bind(&CValidationInterface::UpdateSyncStatus, pwalletIn));
    g_signals.UpdatedZnode.disconnect(boost::bind(&CValidationInterface::UpdatedZnode, pwalletIn, _1));
    g_signals.UpdatedMasternode.disconnect(boost::bind(&CValidationInterface::UpdatedMasternode, pwalletIn, _1));
    g_signals.UpdatedMintStatus.disconnect(boost::bind(&CValidationInterface::UpdatedMintStatus, pwalletIn, _1));
    g_signals.UpdatedSettings.disconnect(boost::bind(&CValidationInterface::UpdatedSettings, pwalletIn, _1));
    g_signals.NotifyAPIStatus.disconnect(boost::bind(&CValidationInterface::NotifyAPIStatus, pwalletIn));
    g_signals.NotifyZnodeList.disconnect(boost::bind(&CValidationInterface::NotifyZnodeList, pwalletIn));
    g_signals.NotifyMasternodeList.disconnect(boost::bind(&CValidationInterface::NotifyMasternodeList, pwalletIn));
    g_signals.UpdatedBalance.disconnect(boost::bind(&CValidationInterface::UpdatedBalance, pwalletIn));
    g_signals.NewPoWValidBlock.disconnect(boost::bind(&CValidationInterface::NewPoWValidBlock, pwalletIn, _1, _2));
    g_signals.WalletSegment.disconnect(boost::bind(&CValidationInterface::WalletSegment, pwalletIn, _1));
}

void UnregisterAllValidationInterfaces() {
    g_signals.AcceptedBlockHeader.disconnect_all_slots();
    g_signals.NotifyHeaderTip.disconnect_all_slots();
    g_signals.UpdatedBlockTip.disconnect_all_slots();
    g_signals.SyncTransaction.disconnect_all_slots();
    g_signals.UpdatedTransaction.disconnect_all_slots();
    g_signals.WalletTransaction.disconnect_all_slots();
    g_signals.SetBestChain.disconnect_all_slots();
    g_signals.Inventory.disconnect_all_slots();
    g_signals.Broadcast.disconnect_all_slots();
    g_signals.BlockChecked.disconnect_all_slots();
    g_signals.ScriptForMining.disconnect_all_slots();
    g_signals.BlockFound.disconnect_all_slots();
    g_signals.NumConnectionsChanged.disconnect_all_slots();
    g_signals.UpdateSyncStatus.disconnect_all_slots();
    g_signals.UpdatedZnode.disconnect_all_slots();
    g_signals.UpdatedMasternode.disconnect_all_slots();
    g_signals.UpdatedMintStatus.disconnect_all_slots();
    g_signals.UpdatedSettings.disconnect_all_slots();
    g_signals.NotifyAPIStatus.disconnect_all_slots();
    g_signals.NotifyZnodeList.disconnect_all_slots();
    g_signals.NotifyMasternodeList.disconnect_all_slots();
    g_signals.UpdatedBalance.disconnect_all_slots();
    g_signals.NewPoWValidBlock.disconnect_all_slots();
    g_signals.WalletSegment.disconnect_all_slots();
}
