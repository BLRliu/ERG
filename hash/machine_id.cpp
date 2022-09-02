// *****************************************************************************
// 版权所有（C）2022-2023，风一样的网络
// 保留所有权利
// *****************************************************************************
// 作者 : 风一样的少年
// 版本 : 1.0
// 功能说明:
//           main
// *****************************************************************************
//#pragma warning(disable 4047 4024 4133 4267)
#include "hmac_sha2.h"
#include "sha1.h"
#include "string.h"
#include <stdio.h>
#include "windows.h"
#include "sddl.h"

#include "crc8.h"

int GetSystemVolumeSerialNumber(int* number)
{
 wchar_t system_path[MAX_PATH + 1];
 wchar_t* first_slash;
 DWORD number_local = 0;

 if (!number)
  return 0;

 *number = 0;

 // Find the system root path (e.g: C:\).
 if (!GetSystemDirectoryW(system_path, MAX_PATH))
  return 0;

 first_slash = wcspbrk(system_path, L"\\/");
 if (first_slash != NULL)
  *(first_slash + 1) = 0;

 if (!GetVolumeInformationW(system_path, NULL, 0, &number_local, NULL, NULL,
  NULL, 0))
  return 0;

 *number = number_local;
 return 1;
}

int GetComputerSid(const wchar_t* account_name, SID* sid, DWORD sid_size)
{
 static const DWORD kStartDomainLength = 128;  // reasonable to start with
 DWORD domain_size = kStartDomainLength;
 DWORD sid_dword_size = sid_size;
 SID_NAME_USE sid_name_use;
 BOOL success;
 wchar_t* domain_buffer = (wchar_t*)malloc(kStartDomainLength * sizeof(wchar_t));

 success = LookupAccountNameW(NULL, account_name, sid,
  &sid_dword_size, domain_buffer,
  &domain_size, &sid_name_use);
 DWORD err = GetLastError();
 if (!success && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
 {
  if (sid_dword_size > sid_size)
  {
   free(domain_buffer);
   return 0;
  }

  if (domain_size > kStartDomainLength)
   domain_buffer = (wchar_t*)realloc(domain_buffer, domain_size * sizeof(wchar_t));

  success = LookupAccountNameW(NULL, account_name, sid, &sid_dword_size,
   domain_buffer, &domain_size,
   &sid_name_use);
 }

 free(domain_buffer);
 return success != FALSE;
}


int GetUserSID(HANDLE hHandle, wchar_t* StringSid)
{
 DWORD dwSize = 0, dwResult = 0;
 HANDLE hToken;
 PTOKEN_USER pUserInfo;

 if (!OpenProcessToken(hHandle, TOKEN_QUERY, &hToken))
  return 1;

 if (!GetTokenInformation(hToken, TokenUser, NULL, dwSize, &dwSize))
 {
  dwResult = GetLastError();
  if (dwResult != ERROR_INSUFFICIENT_BUFFER)
   return 1;
 }

 pUserInfo = (PTOKEN_USER)GlobalAlloc(GPTR, dwSize);

 if (!GetTokenInformation(hToken, TokenUser, pUserInfo,
  dwSize, &dwSize))
 {
  return 1;
 }


 LPWSTR ps = (LPWSTR)(LPCWSTR)StringSid;
 LPWSTR* a = &ps;
 ConvertSidToStringSidW(pUserInfo->User.Sid, a);
 wcscpy(StringSid, ps);
 if (pUserInfo)
  GlobalFree(pUserInfo);
 return 0;
}

int ConvertSidToString(SID* sid, wchar_t* sid_string) {
 int sub_auth_count;
 int i;
 SID_IDENTIFIER_AUTHORITY* sia = GetSidIdentifierAuthority(sid);
 DWORD a = GetLastError();

 if (sia->Value[0] || sia->Value[1])
 {
  swprintf(sid_string, 
   L"S-%d-0x%02hx%02hx%02hx%02hx%02hx%02hx",
   SID_REVISION, 
   (USHORT)sia->Value[0], 
   (USHORT)sia->Value[1],
   (USHORT)sia->Value[2], 
   (USHORT)sia->Value[3], 
   (USHORT)sia->Value[4],
   (USHORT)sia->Value[5]);
 }
 else
 {
  ULONG authority = 0;
  int i;
  for (i = 2; i < 6; ++i) {
   authority <<= 8;
   authority |= sia->Value[i];
  }
  swprintf(sid_string, L"S-%d-%lu", SID_REVISION, authority);
 }

 sub_auth_count = *GetSidSubAuthorityCount(sid);
 for (i = 0; i < sub_auth_count; ++i)
  swprintf(sid_string + wcslen(sid_string), L"-%lu", *GetSidSubAuthority(sid, i));

 return 1;
}

int GetRawMachineId(HANDLE hHandle, wchar_t* sid_string, int* volume_id)
{
 // Calculate the Windows SID.
 wchar_t computer_name[MAX_COMPUTERNAME_LENGTH + 1] = { 0 };
 DWORD size = sizeof(computer_name) / sizeof(wchar_t);

 if (GetComputerNameW(computer_name, &size)) {
  char sid_buffer[1024];
  memset(sid_buffer, 0, 1024);
  SID* sid = (SID*)sid_buffer;
  if (GetComputerSid(computer_name, sid, sizeof(sid_buffer)))
  {
   GetUserSID(hHandle, sid_string);
   //ConvertSidToString(sid, sid_string);
  }
 }

 // Get the system drive volume serial number.
 *volume_id = 0;
 if (!GetSystemVolumeSerialNumber(volume_id)) {
  // ASSERT_STRING("GetMachineId: Failed to retrieve volume serial number");
  *volume_id = 0;
 }

 return 1;
}


int get_machine_id(void* hHandle, char* machine_id)
{
 unsigned char hash[32];
 char buf[128];
 int i;
 sha1_context ctx1;
 wchar_t sid_string[1024];
 int volume_id;
 unsigned char digest[20 + sizeof(int) + 1];
 memset(sid_string, 0, 1024);

 if (!GetRawMachineId(hHandle, sid_string, &volume_id))
  return 0;
 // wprintf(L"sid: %s\n", sid_string);

 sha1_init(&ctx1);
 sha1_update(&ctx1, (unsigned char*)sid_string, wcslen(sid_string) * sizeof(wchar_t));
 sha1_final(&ctx1, hash);

 for (i = 0; i < 20; ++i)
  sprintf(buf + i + i, "%02X", hash[i]);
 // printf("sha1 %s\n", buf);

 memcpy(digest, hash, 20);

 for (i = 0; i < sizeof(int); i++)
 {
  int shift_bits = 8 * (sizeof(int) - i - 1);
  digest[20 + i] = (unsigned char)((volume_id >> shift_bits) & 0xFF);
 }

 digest[sizeof(digest) - 1] = crc8(digest, sizeof(digest) - 1);

 for (i = 0; i < sizeof(digest); ++i)
  sprintf(machine_id + i + i, "%02X", digest[i]);

 return 1;
}


//chrome ver 53+ get_machine_id
int ConvertSidToString_v53(SID* sid, char* sid_string) {
 int sub_auth_count;
 int i;
 SID_IDENTIFIER_AUTHORITY* sia = GetSidIdentifierAuthority(sid);

 if (sia->Value[0] || sia->Value[1])
 {
  wsprintfA(sid_string, "S-%d-0x%02hx%02hx%02hx%02hx%02hx%02hx",
   SID_REVISION, (USHORT)sia->Value[0], (USHORT)sia->Value[1],
   (USHORT)sia->Value[2], (USHORT)sia->Value[3], (USHORT)sia->Value[4],
   (USHORT)sia->Value[5]);
 }
 else
 {
  ULONG authority = 0;
  int i;
  for (i = 2; i < 6; ++i) {
   authority <<= 8;
   authority |= sia->Value[i];
  }
  wsprintfA(sid_string, "S-%d-%lu", SID_REVISION, authority);
 }

 sub_auth_count = *GetSidSubAuthorityCount(sid);
 for (i = 0; i < sub_auth_count; ++i)
  wsprintfA(sid_string + strlen(sid_string), "-%lu", *GetSidSubAuthority(sid, i));

 return 1;
}

int get_machine_id_v53(void* hHandle, char* machine_id)
{
 // Calculate the Windows SID.
 wchar_t computer_name[MAX_COMPUTERNAME_LENGTH + 1] = { 0 };
 DWORD size = sizeof(computer_name) / sizeof(wchar_t);

 if (GetComputerNameW(computer_name, &size)) {
  char sid_buffer[1024];
  SID* sid = (SID*)sid_buffer;
  if (GetComputerSid(computer_name, sid, sizeof(sid_buffer))) {
   ConvertSidToString_v53(sid, machine_id);
  }
 }

 return 1;
}


