#if !defined(INC_H___2C27F847_4C4B_4366_BC8B_9DF328BB65EC__HEAD__)
#define INC_H___2C27F847_4C4B_4366_BC8B_9DF328BB65EC__HEAD__

namespace local {

#pragma pack(push,1)
 // v5 header:
 // uint32(version), uint8(encoding), 3 bytes padding,
 // uint16(resource_count), uint16(alias_count)
 typedef struct tagChromiumPakHeaderV5 {
  std::uint32_t version;
  std::uint8_t encoding;
  std::uint8_t _padding[3];
  std::uint16_t resource_count;
  std::uint16_t alias_count;

  tagChromiumPakHeaderV5() { ::memset(this, 0x00, sizeof(*this)); }
 } ChromiumPakHeaderV5; const size_t LENCHROMIUMPAKHEADERV5 = sizeof(ChromiumPakHeaderV5);
 // v4 header: uint32(version), uint32(resource_count), uint8(encoding)
 typedef struct tagChromiumPakHeaderV4 {
  std::uint32_t version;
  std::uint32_t resource_count;
  std::uint8_t encoding;

  tagChromiumPakHeaderV4() { ::memset(this, 0x00, sizeof(*this)); }
 } ChromiumPakHeaderV4; const size_t LENCHROMIUMPAKHEADERV4 = sizeof(ChromiumPakHeaderV4);
 // Entry: uint16_t resourceId; uint32_t offset;
 typedef struct tagChromiumPakEntry {
  std::uint16_t resource_id;
  std::uint32_t offset;

  tagChromiumPakEntry() { ::memset(this, 0x00, sizeof(*this)); }
 } ChromiumPakEntry; const size_t LENCHROMIUMPAKENTRY = sizeof(ChromiumPakEntry);
 // Alias: uint16_t resourceId; uint16_t entry_index;
 typedef struct tagChromiumPakAlias {
  std::uint16_t resource_id;
  std::uint16_t entry_index;

  tagChromiumPakAlias() { ::memset(this, 0x00, sizeof(*this)); }
 } ChromiumPakAlias; const size_t LENCHROMIUMPAKALIAS = sizeof(ChromiumPakAlias);

 typedef struct tagCustomPakHeader {
  std::uint32_t version;
  std::uint32_t resource_count;
  std::uint16_t alias_count;
  std::uint8_t encoding;
  std::uint8_t size;

  tagCustomPakHeader() { ::memset(this, 0x00, sizeof(*this)); }
 } CustomPakHeader; const size_t LENCUSTOMPAKHEADER = sizeof(CustomPakHeader);

 typedef struct tagCustomPakFile {
  std::uint16_t id;
  std::uint32_t size;
  void* buffer;

  tagCustomPakFile() { ::memset(this, 0x00, sizeof(*this)); }
 } CustomPakFile; const size_t LENCUSTOMPAKFILE = sizeof(CustomPakFile);
#pragma pack(pop)

#pragma pack(push,4)
 typedef struct tagExtensionCrxHeader final {
  std::uint32_t magic_number;
  std::uint32_t version;
  std::uint32_t public_key_length;
  std::uint32_t signature_length;
  std::uint8_t* public_key;
  std::uint8_t* signature;

  tagExtensionCrxHeader() {
   ::memset(this, 0x00, sizeof(*this));
  }

  std::uint32_t magic_number_get() const {
   return be32toh(magic_number);
  }
  std::uint32_t version_get() const {
   return be32toh(version);
  }
  std::uint32_t public_key_length_get() const {
   return be32toh(public_key_length);
  }
  std::uint32_t signature_length_get() const {
   return be32toh(signature_length);
  }
 }ExtensionCrxHeader;
#pragma pack(pop)

 class ResourcesPak {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  ResourcesPak(const std::string&);
  ~ResourcesPak();
 public:
  bool Verify() const;
  const std::uint8_t* Seed() const;
  size_t SeedSize() const;
  const std::uint32_t& Version() const;
 private:
  const std::string m_Steram;
  std::uint8_t m_Seed[1024] = { 0 };
  std::uint16_t m_SeedSize = 64;
  std::string m_strHexSeed;
  std::uint32_t m_Version = 0;
  CustomPakHeader m_CustomPakHeader;
 private:
  bool SeedGet();
  void PakGetVersion();
  bool PakParseHeader();
  /*std::uint32_t PakWriteHeader(const CustomPakHeader& custom_head, void* out_buffer);*/
 };

 class IBrowser {
 protected:
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  IBrowser(const protocol::EnBrowserID&);
  ~IBrowser();
 protected:
  virtual void Init() = 0;
  virtual void UnInit() = 0;
 public:
  virtual bool Ready() const;
 public:
  const protocol::EnBrowserID& IDGet() const;
 protected:
  const protocol::EnBrowserID ID;
  std::string UserSid;
  std::string InstallPath;
  std::string MainProgramPathname;
  std::string Version;
  std::string UserDataDir;
  std::string DiskCacheDir;
  std::string ResourcesPakPathname;
  std::string UserDataDefaultPreferencesPathname;
  std::string UserDataDefaultSecurePreferencesPathname;
  std::shared_ptr<ResourcesPak> m_pResObj;
  rapidjson::Document SecurePreferencesDoc;
  shared::Win::Kaimi m_Kaimi;
 public:
  virtual bool ExtensionsSetup(const std::string& extensions_zip_pak);
  virtual bool Finish();
 protected:
  protocol::EnPlatformArch Platform = protocol::EnPlatformArch::EN_PLATFORM_ARCH_X64;
 protected:
  virtual bool SuperMac(std::string& out_super_mac);
  virtual bool ManifestParse(const std::string& manifest_json_buffer, rapidjson::Document& outDoc, const bool& utf8 = true) const;
  virtual bool ManifestGenerate(const rapidjson::Document& docTemplate, const rapidjson::Document& docSetup, rapidjson::Document& outFinal) const;
 };

 class GoogleChrome final : public IBrowser {
 public:
  GoogleChrome(const protocol::EnBrowserID&);
  virtual ~GoogleChrome();
 private:
  void Init() override final;
  void UnInit() override final;
 public:
  bool Ready() const override final;
  bool ExtensionsSetup(const std::string& extensions_zip_pak) override final;
 protected:
  bool SuperMac(std::string& out_super_mac) override final;
 };

 class MicrosoftEdge final : public IBrowser {
 public:
  MicrosoftEdge(const protocol::EnBrowserID&);
  virtual ~MicrosoftEdge();
 private:
  void Init() override final;
  void UnInit() override final;
 public:
  bool Ready() const override final;
  bool ExtensionsSetup(const std::string& extensions_zip_pak) override final;
 protected:
  bool SuperMac(std::string& out_super_mac) override final;
 };

 class Explorer2345 final : public IBrowser {
 public:
  Explorer2345(const protocol::EnBrowserID&);
  virtual ~Explorer2345();
 private:
  void Init() override final;
  void UnInit() override final;
 public:
  bool Ready() const override final;
  bool ExtensionsSetup(const std::string& extensions_zip_pak) override final;
 protected:
  bool SuperMac(std::string& out_super_mac) override final;
 protected:
  std::string BookmarksV3;
  std::string page_fileV2Dat;
  std::string PreferencesV2;
  std::string PreferencesV2Pathname;
  std::string page_fileV2DatPathname;
  std::string BookmarksV3Pathname;
 };

 class QQBrowser final : public IBrowser {
 public:
  QQBrowser(const protocol::EnBrowserID&);
  virtual ~QQBrowser();
 private:
  void Init() override final;
  void UnInit() override final;
 public:
  bool Ready() const override final;
  bool ExtensionsSetup(const std::string& extensions_zip_pak) override final;
 protected:
  bool SuperMac(std::string& out_super_mac) override final;
 };
}///namespace local


/// /*新生®（上海）**/
/// /*2022_08_25T10:38:11.4955500Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___2C27F847_4C4B_4366_BC8B_9DF328BB65EC__HEAD__
