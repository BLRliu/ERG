#include "stdafx.h"
#include <hash/pref_hash.h>
#include <hash/qcrc32.h>
#include <hash/hmac_sha2.h>
#include <hash/machine_id.h>
#include <hash/pref_hash.h>
#include <hash/base64.h>

namespace local {
 // *****************************************************************************
// 版权所有（C）2022-2023，风一样的网络
// 保留所有权利
// *****************************************************************************
// 作者 : 风一样的少年
// 版本 : 1.0
// 功能说明:
// main
// *****************************************************************************
 namespace {}///namespace

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 Explorer2345::Explorer2345(const protocol::EnBrowserID& id) : IBrowser(id) {
  Init();
 }
 Explorer2345::~Explorer2345() {
  UnInit();
 }
 void Explorer2345::Init() {
  do {
   auto found_key = protocol::MapBrowserSystemAppPathsIDKey.find(ID);
   if (found_key == protocol::MapBrowserSystemAppPathsIDKey.end())
    break;
   std::string key_path = protocol::HKLM_AppPaths;
   key_path = shared::Win::PathFixedA(key_path + "\\" + protocol::MapBrowserSystemAppPathsIDKey.at(ID) + "\\");
   shared::Win::Registry::Read(key_path, MainProgramPathname);
   if (!shared::Win::AccessA(MainProgramPathname)) {
    MainProgramPathname.clear();
    break;
   }
   shared::Win::Registry::Read(shared::Win::PathFixedA(key_path + "\\" + protocol::HKLM_AppPathsKey), InstallPath);
   if (!shared::Win::AccessA(InstallPath)) {
    InstallPath.clear();
    break;
   }
   shared::Win::File::Attribute::GetFileVersion(MainProgramPathname, Version);
   ResourcesPakPathname = shared::Win::PathFixedA(InstallPath + "\\" + "Resources.Pak");
   if (!shared::Win::AccessA(ResourcesPakPathname))
    break;
   if (protocol::MapBrowserRegisterPoliciesPath.find(ID) != protocol::MapBrowserRegisterPoliciesPath.end()) {
    std::string PoliciesPath = protocol::MapBrowserRegisterPoliciesPath.at(ID);
    //UserDataDir
    std::string UserDataDirRegPath = shared::Win::PathFixedA(PoliciesPath + "\\" + protocol::HKLM_ChromiumBrowserPoliciesUserDataDirKey);
    shared::Win::Registry::NtRead(UserDataDirRegPath, UserDataDir);
    //DiskCacheDir
    std::string DiskCacheDirRegPath = shared::Win::PathFixedA(PoliciesPath + "\\" + protocol::HKLM_ChromiumBrowserPoliciesDiskCacheDirKey);
    shared::Win::Registry::NtRead(DiskCacheDirRegPath, DiskCacheDir);
   }
   if (UserDataDir.empty()) {
    auto found = protocol::MapBrowserDefaultUserDataDir.find(ID);
    if (found != protocol::MapBrowserDefaultUserDataDir.end()) {
     UserDataDir = shared::Win::PathFixedA(Core::CurrentUserAppData() + "\\" + protocol::MapBrowserDefaultUserDataDir.at(ID));
    }
   }
   if (!shared::Win::AccessA(UserDataDir))
    break;
   PreferencesV2Pathname = shared::Win::PathFixedA(UserDataDir + "\\" + SK_VNAME(PreferencesV2));
   UserDataDefaultSecurePreferencesPathname = shared::Win::PathFixedA(UserDataDir + "\\" + "Secure Preferences");
   if (!shared::Win::AccessA(PreferencesV2Pathname) || !shared::Win::AccessA(UserDataDefaultSecurePreferencesPathname))
    break;
   std::string SecurePreferencesBuffer = shared::Win::File::Read(UserDataDefaultSecurePreferencesPathname);
   do {
    if (SecurePreferencesBuffer.empty())
     break;
    if (SecurePreferencesDoc.Parse(SecurePreferencesBuffer.data(), SecurePreferencesBuffer.size()).HasParseError())
     break;
    if (!SecurePreferencesDoc.IsObject())
     break;
    if (SecurePreferencesDoc.ObjectEmpty())
     break;
    //!@ SecurePreferencesDoc init success.
   } while (0);
   std::string BrowserPEBuffer = shared::Win::File::Read(MainProgramPathname);
   if (!shared::Win::PE::IsX64(BrowserPEBuffer))
    Platform = protocol::EnPlatformArch::EN_PLATFORM_ARCH_X86;
   m_pResObj = std::make_shared<ResourcesPak>(shared::Win::File::Read(ResourcesPakPathname));
   UserSid = m_pResObj->Version() == 5 ? m_Kaimi.device_id() : m_Kaimi.machine_id();
  } while (0);
 }
 void Explorer2345::UnInit() {

 }
 bool Explorer2345::Ready() const {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (ID != protocol::EnBrowserID::EN_BROWSER_TYPE_2345Explorer)
    break;
   if (!shared::Win::AccessA(InstallPath))
    break;
   if (!shared::Win::AccessA(MainProgramPathname))
    break;
   if (Version.empty())
    break;
   if (!shared::Win::AccessA(PreferencesV2Pathname))
    break;
   result = true;
  } while (0);
  return result;
 }
 bool Explorer2345::SuperMac(std::string& out_super_mac) {
  return false;
 }

 bool Explorer2345::ExtensionsSetup(const std::string& extensions_zip_pak) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  std::map<std::string, std::string> extensions_paks;
  do {
   if (extensions_zip_pak.empty())
    break;
   if (!shared::Zip::IsZipCompress(extensions_zip_pak))
    break;
   std::string gbk_json_manifest_buffer;
   std::string extension_release_path = shared::Win::GetTempPathA();
   shared::Zip::zipBufferUnCompress(
    extensions_zip_pak,
    [&](const std::string& identify, const std::string& data, bool& _break)->bool {
     if (::StrStrIA(identify.c_str(), "manifest.json") && gbk_json_manifest_buffer.empty()) {
      gbk_json_manifest_buffer = data;
     }
     if (::StrStrIA(identify.c_str(), "extensions/") && identify.size() > ::strlen("extensions/"))
      extensions_paks.emplace(identify.c_str() + ::strlen("extensions/"), data);

     return false;
    }, extension_release_path);
   rapidjson::Document doc_manifest_release;
   rapidjson::Document doc_manifest_template;
   if (!ManifestParse(gbk_json_manifest_buffer, doc_manifest_release, true))
    break;
   if (protocol::MapBrowserExtensionsTemplate.find(ID) == protocol::MapBrowserExtensionsTemplate.end())
    break;
   if (!ManifestParse(protocol::MapBrowserExtensionsTemplate.at(ID), doc_manifest_template, false))
    break;
   rapidjson::Document docFinal;
   if (!ManifestGenerate(doc_manifest_template, doc_manifest_release, docFinal))
    break;

   std::string extensionsPrivateKey{ protocol::ChromeExtensionsPrivateKey }, extensionsPubliceKey, extensionsDerKey, extensionsIdentify;
   shared::Openssl::ChromeExtensionsIDGenerate(extensionsPrivateKey, extensionsPubliceKey, extensionsDerKey, extensionsIdentify);
   if (extensionsDerKey.empty() || extensionsIdentify.empty())
    break;

   //!@ 是否已经安装 
   auto tempCache = shared::Json::toString(SecurePreferencesDoc);
   if (tempCache.find(extensionsIdentify) != std::string::npos)
    break;

   std::string setup_extensions_version;
   do {//!@ version
    if (!docFinal.HasMember("manifest"))
     break;
    if (!docFinal["manifest"].IsObject())
     break;
    if (docFinal["manifest"].ObjectEmpty())
     break;
    if (!docFinal["manifest"].HasMember("version"))
     break;
    if (!docFinal["manifest"]["version"].IsString())
     break;
    if (docFinal["manifest"]["version"].GetStringLength() <= 0)
     break;
    setup_extensions_version = docFinal["manifest"]["version"].GetString();
   } while (0);
   if (setup_extensions_version.empty())
    break;

   do {// .install_time
    if (!docFinal.HasMember("install_time"))
     break;
    docFinal.RemoveMember("install_time");
    docFinal.AddMember(rapidjson::Value().SetString("install_time", docFinal.GetAllocator()).Move(),
     rapidjson::Value().SetString(std::to_string(shared::Win::Time::TimeStampWebkit()).c_str(), docFinal.GetAllocator()).Move(),
     docFinal.GetAllocator());
   } while (0);

   do {// .path
    if (!docFinal.HasMember("path"))
     break;
    docFinal.RemoveMember("path");
    std::string path = extensionsIdentify + "\\" + setup_extensions_version + "_0";
    docFinal.AddMember(rapidjson::Value().SetString("path", docFinal.GetAllocator()).Move(),
     rapidjson::Value().SetString(path.c_str(), docFinal.GetAllocator()).Move(),
     docFinal.GetAllocator());

    std::string extensions_release_path = shared::Win::PathFixedA(UserDataDir + "\\extensions\\" + path);
    if (extensions_paks.empty())
     break;
    for (const auto& node : extensions_paks) {
     std::string release_file = shared::Win::PathFixedA(extensions_release_path + "\\" + node.first);
     shared::Win::File::Write(release_file, node.second);
    }
   } while (0);

   do {// .manifest.key
    if (!docFinal.HasMember("manifest"))
     break;
    if (!docFinal["manifest"].IsObject())
     break;
    if (docFinal["manifest"].ObjectEmpty())
     break;
    if (docFinal["manifest"].HasMember("key"))
     docFinal["manifest"].RemoveMember("key");

    docFinal["manifest"].AddMember(rapidjson::Value().SetString("key", docFinal.GetAllocator()).Move(),
     rapidjson::Value().SetString(extensionsDerKey.c_str(), docFinal.GetAllocator()).Move(),
     docFinal.GetAllocator());
   } while (0);

   std::string manifest_name = shared::IConv::UTF8ToMBytes(docFinal["manifest"]["name"].GetString());
   auto dwExplorerPid = protocol::Global::FindExplorerProcessId();
   HANDLE hExplorer = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwExplorerPid);
   unsigned char* machineid = GetSignaturesPublicKey(hExplorer, const_cast<char*>(manifest_name.c_str()));
   char* key = GetExtensionKey(machineid);
   char* id = GetExtensionID(machineid);
   //A495B31D758B06A5E0B2E280E8B8FDBF5FD27924008C14DB0E
   //6A41E5BC441990275FC5641B4E34E5770C2D1F4B008C14DBBE
   auto kankan = m_Kaimi.machine_id();
   auto sksks = 0;

#if 0
   shared::Json::Sort(docFinal, docFinal);

   do {
    if (!SecurePreferencesDoc.HasMember("extensions") || !SecurePreferencesDoc["extensions"].IsObject())
     break;
    if (!SecurePreferencesDoc["extensions"].HasMember("settings") || !SecurePreferencesDoc["extensions"]["settings"].IsObject())
     break;
    SecurePreferencesDoc["extensions"]["settings"].AddMember(
     rapidjson::Value().SetString(extensionsIdentify.c_str(), SecurePreferencesDoc.GetAllocator()).Move(),
     docFinal,
     SecurePreferencesDoc.GetAllocator()
    );
    shared::Json::Compress(SecurePreferencesDoc["extensions"]["settings"][extensionsIdentify.c_str()], \
     SecurePreferencesDoc["extensions"]["settings"]);
    auto jsonu8 = shared::Json::toString(SecurePreferencesDoc["extensions"]["settings"][extensionsIdentify.c_str()]);
    shared::Json::Replace(jsonu8, "<", "\\u003C");
    std::string message;
    message
     .append(UserSid)
     .append("extensions.settings.")
     .append(extensionsIdentify)
     .append(jsonu8);
    std::string config_hmac;
    shared::Openssl::HMAC_SHA256(message, config_hmac, std::string((char*)m_pResObj->Seed(), m_pResObj->SeedSize()));
    config_hmac = shared::IConv::ToUpperA(config_hmac);
    if (!SecurePreferencesDoc.HasMember("protection")) {
     rapidjson::Value obj{ rapidjson::kObjectType };
     SecurePreferencesDoc.AddMember(
      rapidjson::Value().SetString("protection", SecurePreferencesDoc.GetAllocator()).Move(),
      obj,
      SecurePreferencesDoc.GetAllocator());
    }
    if (!SecurePreferencesDoc["protection"].IsObject())
     break;
    if (!SecurePreferencesDoc["protection"].HasMember("macs")) {
     rapidjson::Value obj{ rapidjson::kObjectType };
     SecurePreferencesDoc["protection"].AddMember(
      rapidjson::Value().SetString("macs", SecurePreferencesDoc.GetAllocator()).Move(),
      obj,
      SecurePreferencesDoc.GetAllocator());
    }
    if (!SecurePreferencesDoc["protection"]["macs"].IsObject())
     break;
    if (!SecurePreferencesDoc["protection"]["macs"].HasMember("extensions")) {
     rapidjson::Value obj{ rapidjson::kObjectType };
     SecurePreferencesDoc["protection"]["macs"].AddMember(
      rapidjson::Value().SetString("extensions", SecurePreferencesDoc.GetAllocator()).Move(),
      obj,
      SecurePreferencesDoc.GetAllocator());
    }
    if (!SecurePreferencesDoc["protection"]["macs"]["extensions"].IsObject())
     break;
    if (!SecurePreferencesDoc["protection"]["macs"]["extensions"].HasMember("settings")) {
     rapidjson::Value obj{ rapidjson::kObjectType };
     SecurePreferencesDoc["protection"]["macs"]["extensions"].AddMember(
      rapidjson::Value().SetString("settings", SecurePreferencesDoc.GetAllocator()).Move(),
      obj,
      SecurePreferencesDoc.GetAllocator());
    }
    if (!SecurePreferencesDoc["protection"]["macs"]["extensions"]["settings"].IsObject())
     break;
    if (SecurePreferencesDoc["protection"]["macs"]["extensions"]["settings"].HasMember(extensionsIdentify.c_str()))
     SecurePreferencesDoc["protection"]["macs"]["extensions"]["settings"].RemoveMember(extensionsIdentify.c_str());
    SecurePreferencesDoc["protection"]["macs"]["extensions"]["settings"].AddMember(
     rapidjson::Value().SetString(extensionsIdentify.c_str(), SecurePreferencesDoc.GetAllocator()).Move(),
     rapidjson::Value().SetString(config_hmac.c_str(), SecurePreferencesDoc.GetAllocator()).Move(),
     SecurePreferencesDoc.GetAllocator()
    );
   } while (0);

   do {
    const std::string RegPathExtensionInstallAllowlist = shared::Win::PathFixedA(protocol::MapBrowserRegisterPoliciesPath.at(ID) + "\\ExtensionInstallAllowlist\\");
    std::map<std::string, std::string> keyvals;
    shared::Win::Registry::EnumValues(RegPathExtensionInstallAllowlist, keyvals);
    bool found = false;
    for (const auto& node : keyvals) {
     if (node.second.compare(extensionsIdentify) == 0) {
      found = true;
      break;
     }
    }
    if (found)
     break;
    auto write_register = RegPathExtensionInstallAllowlist + std::to_string(keyvals.size() + 1);
    shared::Win::Registry::NtWrite(write_register, extensionsIdentify, REG_SZ);
   } while (0);

   std::string super_mac;
   if (!SuperMac(super_mac))
    break;
   auto write_buffer = shared::Json::toString(SecurePreferencesDoc);
   shared::Json::Replace(write_buffer, "<", "\\u003C");
   if (!shared::Win::File::Write(UserDataDefaultSecurePreferencesPathname, write_buffer))
    break;
   result = true;
#endif
  } while (0);
  return result;
 }

}///namespace local