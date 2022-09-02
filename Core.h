#if !defined(INC_H___D49B1C5D_8062_4469_A40A_FD5CC1231E8D__HEAD__)
#define INC_H___D49B1C5D_8062_4469_A40A_FD5CC1231E8D__HEAD__

namespace local {

	class Core final {
		std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
	public:
		Core();
		~Core();
	private:
		void Init();
		void UnInit();
	public:
		bool Open();
		void Close();
		bool ChromiumExtensionsSetup(const std::string& zip_chromium_extensions_pak);
	public:
		static std::string UserAccount();
		static DWORD UserProcessId();
		static std::string UserSid();
		static std::string CurrentUserAppData();
	private:
		std::atomic_bool m_IsOpen = false;
		std::string m_UserAccount;
		DWORD m_UserProcessId;
		std::string m_UserSid;
		std::string m_CurrentUserAppData;
		std::shared_ptr<shared::nt::NTObj> m_pNTObj;
		std::map<protocol::EnBrowserID, std::shared_ptr<IBrowser>> m_Browsers;
	};



	extern Core* __gpCore;
}///namespace local

/// /*新生®（上海）**/
/// /*2022_08_25T11:01:52.7748216Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___D49B1C5D_8062_4469_A40A_FD5CC1231E8D__HEAD__

