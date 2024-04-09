#include <windows.h>
#include <wincred.h>
#include <stdio.h>
#include <string>
#include <stdio.h>
#pragma comment(lib, "Advapi32.lib")
#include <iostream>
using namespace std;
int main() {
	cout << "=== Made by rasky1 ===" << endl;
	char type;
	do
	{
		cout << "すべてのXboxのログイン情報を削除しますか？ [y/n]" << endl;
		cin >> type;
	} while (!cin.fail() && type != 'y' && type != 'n');
	if (type == 'n') {
		cout << "中断しました" << endl;
		system("PAUSE");
		return 0;
	}
	DWORD count;
	PCREDENTIAL* credentials;
	if (!CredEnumerate(NULL, 0, &count, &credentials)) {
		printf("資格情報が取得できませんでした エラーコード: %d\n", GetLastError());
		return 1;
	}
	for (DWORD i = 0; i < count; ++i) {
		PCREDENTIAL cred = credentials[i];
		std::wstring name = std::wstring(cred->TargetName);
		if (name.starts_with(L"MicrosoftAccount:user=") || name.starts_with(L"XblGrts") || name.starts_with(L"SSO_POP") || name.starts_with(L"MCL|")) {
			printf("%ls を削除しました\n", cred->UserName);
			CredDelete(cred->TargetName, CRED_TYPE_GENERIC, 0);
		}
	}
	CredFree(credentials);
	cout << "削除が完了しました" << endl;
	system("PAUSE");
	return 0;
}
