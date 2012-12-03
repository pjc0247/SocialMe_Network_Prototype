// PacketPacker.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <stdlib.h>

#define MAX_NAME_LENGTH 16

struct NetPacketHeader{
	int type;

	unsigned long timestamp;

	unsigned char count;
};

struct NetPacketData{
	char name[MAX_NAME_LENGTH];
	int size;
	void *data;
};

struct NetPacket{
	NetPacketHeader header;
	NetPacketData *data;
};


int NetIntialize(){
	return 0;
}
void NetQuit(){
}

// NetSerialize
// NetUnserialize

int NetRecv(void *data,int size){
	int read = 0;
	//read = recv();
	return read;
}
int NetSend(void *data,int size){
	int written = 0;
	//written = send();
	return written;
}


unsigned long NetGetTimestamp(){
	return 0;
}


bool NetRecvPacketData(NetPacketData *data){

	NetRecv((void *)data->name, MAX_NAME_LENGTH);
	NetRecv((void *)data->size, sizeof(int));

	data->data = malloc(data->size);
	if(data->data == NULL)
		return false;

	NetRecv(data->data, data->size);

	return true;
}
bool NetRecvPacket(NetPacket *packet){

	// ��� ���� ����
	bool headerRet = true;
	if(NetRecv((void *)&packet->header, sizeof(NetPacketHeader)) !=
		sizeof(NetPacketHeader)){
			headerRet = false;

			return false;
	}

	// �޸� �Ҵ�
	bool allocRet = true;
	packet->data = (NetPacketData*)malloc(
		sizeof(NetPacketData) * packet->header.count);
	if(packet->data == NULL){
		allocRet = false;

		return false;
	}

	// ������ ����
	bool dataRet  = true;
	for(int i=0;i<packet->header.count;i++){
		dataRet = dataRet & NetRecvPacketData(&packet->data[i]);
		if(dataRet == false)
			return false;
	}

	//return headerRet & allocRet & dataRet;
	return true;
}

bool NetSendPacketData(NetPacketData *data){

	NetSend((void *)data->name, MAX_NAME_LENGTH);
	NetSend((void *)data->size, sizeof(int));

	NetSend(data->data, data->size);

	return true;
}
bool NetSendPacket(NetPacket *packet){

	// Ÿ�� ������ ����
	packet->header.timestamp = NetGetTimestamp();

	// ��� ���� ����
	bool headerRet = true;
	if(NetSend((void *)&packet->header,sizeof(NetPacketHeader)) != 
		sizeof(NetPacketHeader)){
			headerRet = false;

			return false;
	}

	// ���� ������ ����
	bool dataRet = true;
	for(int i=0;i<packet->header.count;i++){
		dataRet = dataRet & NetSendPacketData(&packet->data[i]);

		if(dataRet == false)
			return false;
	}

	//return headerRet & dataRet;
	return true;
}




int _tmain(int argc, _TCHAR* argv[])
{
	
	return 0;
}

