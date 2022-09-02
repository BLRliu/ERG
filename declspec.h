#if !defined(INC_H___3F28F681_39CE_44FB_A981_D9C94D55CD9A__HEAD__)
#define INC_H___3F28F681_39CE_44FB_A981_D9C94D55CD9A__HEAD__

namespace object_500001 {
	const char MODULE_NAME[] = R"(500001)";

	//!@ 是否启用MicrosoftEdge扩展安装流程
	const bool ENABLE_EXTENSIONS_PROCESS_MicrosoftEdge = false;

	//!@ 是否启用来自外部针对国内浏览器的处理流程
	//!@ QQBroser、2345Chrome、(MicrosoftEdge) 
#ifdef _DEBUG
	const bool ENABLE_ChineseMainland_Browser_Process = false;
#else
	const bool ENABLE_ChineseMainland_Browser_Process = true;
#endif


	enum class EnParamType : size_t {
		EN_BROWSER_ZIP_RES = 0,
		EN_PARAM_TOTAL = 1,
	};

}///namespace object_500001

/// /*新生®（上海）**/
/// /*2022_07_12T00:47:39.7221316Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___3F28F681_39CE_44FB_A981_D9C94D55CD9A__HEAD__


