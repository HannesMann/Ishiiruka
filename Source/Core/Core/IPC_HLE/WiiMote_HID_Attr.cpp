// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "Core/IPC_HLE/WiiMote_HID_Attr.h"
#include "Common/Assert.h"
#include "Common/CommonTypes.h"

static u8 packet1[] = {
		0x00, 0x7b, 0x00, 0x76, 0x36, 0x01, 0xcc, 0x09, 0x00, 0x00, 0x0a, 0x00, 0x01, 0x00, 0x00, 0x09,
		0x00, 0x01, 0x35, 0x03, 0x19, 0x11, 0x24, 0x09, 0x00, 0x04, 0x35, 0x0d, 0x35, 0x06, 0x19, 0x01,
		0x00, 0x09, 0x00, 0x11, 0x35, 0x03, 0x19, 0x00, 0x11, 0x09, 0x00, 0x05, 0x35, 0x03, 0x19, 0x10,
		0x02, 0x09, 0x00, 0x06, 0x35, 0x09, 0x09, 0x65, 0x6e, 0x09, 0x00, 0x6a, 0x09, 0x01, 0x00, 0x09,
		0x00, 0x09, 0x35, 0x08, 0x35, 0x06, 0x19, 0x11, 0x24, 0x09, 0x01, 0x00, 0x09, 0x00, 0x0d, 0x35,
		0x0f, 0x35, 0x0d, 0x35, 0x06, 0x19, 0x01, 0x00, 0x09, 0x00, 0x13, 0x35, 0x03, 0x19, 0x00, 0x11,
		0x09, 0x01, 0x00, 0x25, 0x13, 0x4e, 0x69, 0x6e, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x20, 0x52, 0x56,
		0x4c, 0x2d, 0x43, 0x4e, 0x54, 0x2d, 0x30, 0x31, 0x09, 0x01, 0x02, 0x00, 0x76,
};

static u8 packet2[] = {
		0x00, 0x7b, 0x00, 0x76, 0x01, 0x25, 0x13, 0x4e, 0x69, 0x6e, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x20,
		0x52, 0x56, 0x4c, 0x2d, 0x43, 0x4e, 0x54, 0x2d, 0x30, 0x31, 0x09, 0x01, 0x02, 0x25, 0x08, 0x4e,
		0x69, 0x6e, 0x74, 0x65, 0x6e, 0x64, 0x6f, 0x09, 0x02, 0x00, 0x09, 0x01, 0x00, 0x09, 0x02, 0x01,
		0x09, 0x01, 0x11, 0x09, 0x02, 0x02, 0x08, 0x04, 0x09, 0x02, 0x03, 0x08, 0x33, 0x09, 0x02, 0x04,
		0x28, 0x00, 0x09, 0x02, 0x05, 0x28, 0x01, 0x09, 0x02, 0x06, 0x35, 0xdf, 0x35, 0xdd, 0x08, 0x22,
		0x25, 0xd9, 0x05, 0x01, 0x09, 0x05, 0xa1, 0x01, 0x85, 0x10, 0x15, 0x00, 0x26, 0xff, 0x00, 0x75,
		0x08, 0x95, 0x01, 0x06, 0x00, 0xff, 0x09, 0x01, 0x91, 0x00, 0x85, 0x11, 0x95, 0x01, 0x09, 0x01,
		0x91, 0x00, 0x85, 0x12, 0x95, 0x02, 0x09, 0x01, 0x91, 0x00, 0x02, 0x00, 0xec,
};

static u8 packet3[] = {
		0x00, 0x7b, 0x00, 0x76, 0x85, 0x13, 0x95, 0x01, 0x09, 0x01, 0x91, 0x00, 0x85, 0x14, 0x95, 0x01,
		0x09, 0x01, 0x91, 0x00, 0x85, 0x15, 0x95, 0x01, 0x09, 0x01, 0x91, 0x00, 0x85, 0x16, 0x95, 0x15,
		0x09, 0x01, 0x91, 0x00, 0x85, 0x17, 0x95, 0x06, 0x09, 0x01, 0x91, 0x00, 0x85, 0x18, 0x95, 0x15,
		0x09, 0x01, 0x91, 0x00, 0x85, 0x19, 0x95, 0x01, 0x09, 0x01, 0x91, 0x00, 0x85, 0x1a, 0x95, 0x01,
		0x09, 0x01, 0x91, 0x00, 0x85, 0x20, 0x95, 0x06, 0x09, 0x01, 0x81, 0x00, 0x85, 0x21, 0x95, 0x15,
		0x09, 0x01, 0x81, 0x00, 0x85, 0x22, 0x95, 0x04, 0x09, 0x01, 0x81, 0x00, 0x85, 0x30, 0x95, 0x02,
		0x09, 0x01, 0x81, 0x00, 0x85, 0x31, 0x95, 0x05, 0x09, 0x01, 0x81, 0x00, 0x85, 0x32, 0x95, 0x0a,
		0x09, 0x01, 0x81, 0x00, 0x85, 0x33, 0x95, 0x11, 0x09, 0x01, 0x02, 0x01, 0x62,
};

static u8 packet4[] = {
		0x00, 0x70, 0x00, 0x6d, 0x81, 0x00, 0x85, 0x34, 0x95, 0x15, 0x09, 0x01, 0x81, 0x00, 0x85,
		0x35, 0x95, 0x15, 0x09, 0x01, 0x81, 0x00, 0x85, 0x36, 0x95, 0x15, 0x09, 0x01, 0x81, 0x00,
		0x85, 0x37, 0x95, 0x15, 0x09, 0x01, 0x81, 0x00, 0x85, 0x3d, 0x95, 0x15, 0x09, 0x01, 0x81,
		0x00, 0x85, 0x3e, 0x95, 0x15, 0x09, 0x01, 0x81, 0x00, 0x85, 0x3f, 0x95, 0x15, 0x09, 0x01,
		0x81, 0x00, 0xc0, 0x09, 0x02, 0x07, 0x35, 0x08, 0x35, 0x06, 0x09, 0x04, 0x09, 0x09, 0x01,
		0x00, 0x09, 0x02, 0x08, 0x28, 0x00, 0x09, 0x02, 0x09, 0x28, 0x01, 0x09, 0x02, 0x0a, 0x28,
		0x01, 0x09, 0x02, 0x0b, 0x09, 0x01, 0x00, 0x09, 0x02, 0x0c, 0x09, 0x0c, 0x80, 0x09, 0x02,
		0x0d, 0x28, 0x00, 0x09, 0x02, 0x0e, 0x28, 0x00, 0x00,

};

static u8 packet4_0x10001[] = {
		0x00, 0x60, 0x00, 0x5d, 0x36, 0x00, 0x5a, 0x09, 0x00, 0x00, 0x0a, 0x00, 0x01, 0x00,
		0x01, 0x09, 0x00, 0x01, 0x35, 0x03, 0x19, 0x12, 0x00, 0x09, 0x00, 0x04, 0x35, 0x0d,
		0x35, 0x06, 0x19, 0x01, 0x00, 0x09, 0x00, 0x01, 0x35, 0x03, 0x19, 0x00, 0x01, 0x09,
		0x00, 0x05, 0x35, 0x03, 0x19, 0x10, 0x02, 0x09, 0x00, 0x09, 0x35, 0x08, 0x35, 0x06,
		0x19, 0x12, 0x00, 0x09, 0x01, 0x00, 0x09, 0x02, 0x00, 0x09, 0x01, 0x00, 0x09, 0x02,
		0x01, 0x09, 0x05, 0x7e, 0x09, 0x02, 0x02, 0x09, 0x03, 0x06, 0x09, 0x02, 0x03, 0x09,
		0x06, 0x00, 0x09, 0x02, 0x04, 0x28, 0x01, 0x09, 0x02, 0x05, 0x09, 0x00, 0x02, 0x00,
};

const u8* GetAttribPacket(u32 serviceHandle, u32 cont, u32& _size)
{
	if (serviceHandle == 0x10000)
	{
		if (cont == 0)
		{
			_size = sizeof(packet1);
			return packet1;
		}
		else if (cont == 0x76)
		{
			_size = sizeof(packet2);
			return packet2;
		}
		else if (cont == 0xec)
		{
			_size = sizeof(packet3);
			return packet3;
		}
		else if (cont == 0x162)
		{
			_size = sizeof(packet4);
			return packet4;
		}
	}

	if (serviceHandle == 0x10001)
	{
		_dbg_assert_(WII_IPC_WIIMOTE, cont == 0x00);
		_size = sizeof(packet4_0x10001);
		return packet4_0x10001;
	}

	return nullptr;
}
