// gcc -Wall -D__LITTLE_ENDIAN__ -lws2_32 tg_test.c base64.c sha1.c token_generator.c -o tg_test
// ./tg_test
// Enter: test

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "token_generator.h"

int main(void)
{
	uint8_t secret[20] = {0};
	char steamAccountName[33];
	char twoFactorCode[6];
	int ret;

	printf("Enter your Steam account name: ");
	scanf("%32s", steamAccountName);
	getchar();

	ret = getSharedSecret(steamAccountName, secret);
	switch (ret)
	{
		case 1:
			printf("Secret file not found! Can not generate 2FA code.\n");
			break;
		case 2:
			printf("Secret file is invalid. Can not generate 2FA code.\n");
			break;
		case 3:
			printf("Secret is invalid. Can not generate 2FA code.\n");
			break;
		default:
			// OK
			break;
	}

	if (ret == 0)
	{
		printf("\nPress Ctrl+C to exit...\n");

		while (1)
		{
			get2FACode(secret, twoFactorCode);

			printf("\n2FA code : %s\n", twoFactorCode);
			printf("Expiring in %ld seconds\n", 30 - time(NULL) % 30);

			Sleep(5000);
		}
	}

	return ret;
}