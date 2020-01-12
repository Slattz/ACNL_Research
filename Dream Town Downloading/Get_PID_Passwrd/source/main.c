#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

static Handle* frdSessionHandle;

Result FRD_GetMyPassword(char *buf, u32 bufferlength)
{
	Result ret = 0;
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x10,1,0); // 0x100040
	cmdbuf[1] = bufferlength;
	cmdbuf[64] = (bufferlength << 14) | 2;
	cmdbuf[65] = (u32)buf;

	if (R_FAILED(ret = svcSendSyncRequest(*frdSessionHandle))) return ret;

	return (Result)cmdbuf[1];
}

int main(void)
{
	gfxInitDefault();
	frdInit();
	consoleInit(GFX_TOP, NULL);
	Result ret = 0;
	char nexpassword[20] = {0};
	FriendKey key;
	frdSessionHandle = frdGetSessionHandle();

	if (R_FAILED(ret = FRD_GetMyFriendKey(&key)))
		printf("FRD_GetMyFriendKey Failed: %" PRId32 "\n", ret);
	else printf("PrincipalId: %" PRId32 "\n", key.principalId);

	if (R_FAILED(ret = FRD_GetMyPassword(nexpassword, 20))) 
		printf("FRD_GetMyPassword Failed: %" PRId32 "\n", ret);
	else printf("NEX Password: %s\n", nexpassword);

	frdExit();

	FILE* fp = fopen("sdmc:/nex-keys.txt", "w");
	fprintf(fp, "%" PRId32 ":%s\n", key.principalId, nexpassword);
	fclose(fp);
	printf("\nPID & Nex Password written to \"sdmc:/nex-keys.txt\"\n");
	printf("Press Start To Exit.");
	

	while (aptMainLoop())
	{
		hidScanInput();
		if (hidKeysDown() & KEY_START) break;

		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
