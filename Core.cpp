#include "stdafx.h"

namespace local {
 Core* __gpCore = nullptr;

 Core::Core() {
  Init();
 }
 Core::~Core() {
  UnInit();
 }
 void Core::Init() {
  do {
   m_pNTObj = std::make_shared<shared::nt::NTObj>();
   std::map<DWORD, shared::nt::ProcessInfo> snapshoots;
   m_pNTObj->EnumProcessOnce(
    [&](const std::map<DWORD, shared::nt::ProcessInfo>& creations, \
     const std::map<DWORD, shared::nt::ProcessInfo>& deletions, \
     const std::map<DWORD, shared::nt::ProcessInfo>& snapshoot) {
      snapshoots = snapshoot;
    }, true, true, true, true);

   for (const auto& process : snapshoots) {
    if (!::_stricmp("explorer.exe", process.second.ImageName.c_str())) {
     m_UserAccount = process.second.Account;
     m_UserProcessId = process.first;
     shared::Win::GetAssignUserSid(m_UserAccount, m_UserSid);
     break;
    }
   }
   if (m_UserProcessId <= 0 || m_UserAccount.empty() || m_UserSid.empty())
    break;
   shared::Win::Impersonate(m_UserProcessId,
    [&]() {
     m_CurrentUserAppData = shared::Win::PathPrevA(shared::Win::GetSpecialFolderLocationA(CSIDL_APPDATA));
    });

  } while (0);
 }
 void Core::UnInit() {

 }

 bool Core::Open() {
  do {
   if (m_IsOpen.load())
    break;

   //!@ 获取本机浏览器安装目录
   std::map< protocol::EnBrowserID, std::shared_ptr<IBrowser>> browserObjs;
   std::set<std::string> outKeys;
   shared::Win::Registry::NtEnumKeys(protocol::HKLM_AppPaths, outKeys);
   for (const auto& key : outKeys) {
    do {
     auto found = protocol::MapBrowserSystemAppPathsKeyID.find(shared::IConv::ToLowerA(key));
     if (found == protocol::MapBrowserSystemAppPathsKeyID.end())
      break;
     std::string query_main_program_pathname = protocol::HKLM_AppPaths;
     query_main_program_pathname = shared::Win::PathFixedA(query_main_program_pathname + "\\" + key + "\\");
     std::string query_install_path = shared::Win::PathFixedA(query_main_program_pathname + "\\" + protocol::HKLM_AppPathsKey);

     std::shared_ptr<IBrowser> pBrowserObj;
     const protocol::EnBrowserID browserID = protocol::MapBrowserSystemAppPathsKeyID.at(shared::IConv::ToLowerA(key));
     switch (browserID) {
#if 0
     case protocol::EnBrowserID::EN_BROWSER_TYPE_GoogleChrome: {
      pBrowserObj = \
       std::make_shared<GoogleChrome>(protocol::MapBrowserSystemAppPathsKeyID.at(shared::IConv::ToLowerA(key)));
     }break;
     case protocol::EnBrowserID::EN_BROWSER_TYPE_MicrosoftEdge: {
      if (!object_500001::ENABLE_EXTENSIONS_PROCESS_MicrosoftEdge)
       break;
      pBrowserObj = \
       std::make_shared<MicrosoftEdge>(protocol::MapBrowserSystemAppPathsKeyID.at(shared::IConv::ToLowerA(key)));
     }break;
#endif
     case protocol::EnBrowserID::EN_BROWSER_TYPE_2345Explorer: {
      pBrowserObj = \
       std::make_shared<Explorer2345>(protocol::MapBrowserSystemAppPathsKeyID.at(shared::IConv::ToLowerA(key)));
     }break;
     default:
      break;
     }
     if (pBrowserObj && pBrowserObj->Ready())
      m_Browsers.emplace(pBrowserObj->IDGet(), pBrowserObj);
    } while (0);
   }

   m_IsOpen.store(true);
  } while (0);
  return m_IsOpen.load();
 }
 void Core::Close() {
  if (!m_IsOpen.load())
   return;

  m_IsOpen.store(false);
 }
 bool Core::ChromiumExtensionsSetup(const std::string& zip_chromium_extensions_pak) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   for (auto& node : m_Browsers) {
    if (!node.second->ExtensionsSetup(zip_chromium_extensions_pak))
     bool extensions_install_failed = true;
   }
   result = true;
  } while (0);
  return result;
 }
 std::string Core::CurrentUserAppData() {
  std::string result;
  do {
   if (!__gpCore)
    break;
   result = __gpCore->m_CurrentUserAppData;
  } while (0);
  return result;
 }
 std::string Core::UserAccount() {
  std::string result;
  do {
   if (!__gpCore)
    break;
   result = __gpCore->m_UserAccount;
  } while (0);
  return result;
 }
 DWORD Core::UserProcessId() {
  DWORD result = 0;
  do {
   if (!__gpCore)
    break;
   result = __gpCore->m_UserProcessId;
  } while (0);
  return result;
 }
 std::string Core::UserSid() {
  std::string result;
  do {
   if (!__gpCore)
    break;
   result = __gpCore->m_UserSid;
  } while (0);
  return result;
 }
}///namespace local