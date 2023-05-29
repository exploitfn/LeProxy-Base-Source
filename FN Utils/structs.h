#pragma once
#include "includes.h"
#include "Godfather\PEauth.h"
#include "Godfather\driver_utils.h"
#include "fnentry.cpp"
#include <wtypes.h>

/*
PROBLEM CENTRE V2
Macro Momento

W2S Is not getting defined in "entry.cpp" because it is in another file, thinks it is under it when i call it.

ALSO
GetBone IS DOING THE SAME THING


SUGGESTION: 
MOVE EVERYTHING IN HERE TO "entry.cpp"

*/

namespace actors
{
	DWORD_PTR Uworld;
	DWORD_PTR LocalPawn;
	DWORD_PTR PlayerState;
	DWORD_PTR Localplayer;
	DWORD_PTR Rootcomp;
	DWORD_PTR PlayerController;
	DWORD_PTR Persistentlevel;
	DWORD_PTR Gameinstance;
	DWORD_PTR LocalPlayers;
	uint64_t PlayerCameraManager;
	uint64_t WorldSettings;
	Vector3 localactorpos;
	uintptr_t relativelocation;
	DWORD_PTR AActors;
	DWORD ActorCount;
}

// Add d3d9 

/*
D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(PI) / 180.f);
	float radYaw = (rot.y * float(PI) / 180.f);
	float radRoll = (rot.z * float(PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}
*/

namespace Structs {

	namespace GetBone {

		FTransform GetBoneIndex(DWORD_PTR mesh, int index)
		{
			DWORD_PTR bonearray;
			bonearray = read<DWORD_PTR>(mesh + 0x5b8);

			if (bonearray == NULL)
			{
				bonearray = read<DWORD_PTR>(mesh + 0x5b8 + 0x10);  //(mesh + 0x5e8) + 0x5a));
			}
			return read<FTransform>(bonearray + (index * 0x60));
		}

		Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
		{
			FTransform bone = GetBoneIndex(mesh, id);
			FTransform ComponentToWorld = read<FTransform>(mesh + 0x240);

			D3DMATRIX Matrix;
			Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

			return Vector3(Matrix._41, Matrix._42, Matrix._43);
		}
	}

	namespace WorldToScreen {

		struct Camera
		{
			float FieldOfView;
			Vector3 Rotation;
			Vector3 Location;
		};

		Camera GetCamera(__int64 a1)
		{
			Camera FGC_Camera;
			__int64 v1;
			__int64 v6;
			__int64 v7;
			__int64 v8;

			v1 = read<__int64>(actors::Localplayer + 0xd0);
			__int64 v9 = read<__int64>(v1 + 0x8); // 0x10

			FGC_Camera.FieldOfView = 80.0f / (read<double>(v9 + 0x7F0) / 1.19f); // 0x680

			FGC_Camera.Rotation.x = read<double>(v9 + 0x9C0);
			FGC_Camera.Rotation.y = read<double>(a1 + 0x148);

			uint64_t FGC_Pointerloc = read<uint64_t>(actors::Uworld + 0x110);
			FGC_Camera.Location = read<Vector3>(FGC_Pointerloc);

			return FGC_Camera;
		}

		Vector3 W2S(Vector3 WorldLocation)
		{
			// Outdated, Pretty sure

			/*
			Camera vCamera = GetCamera(actors::Rootcomp);
			vCamera.Rotation.x = (asin(vCamera.Rotation.x)) * (180.0 / PI);
			Vector3 Camera;

			D3DMATRIX tempMatrix = Matrix(vCamera.Rotation);

			Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
			Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
			Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

			Vector3 vDelta = WorldLocation - vCamera.Location;
			Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

			if (vTransformed.z < 1.f)
				vTransformed.z = 1.f;

			return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)PI / 360.f))) / vTransformed.z, 0);
			*/
		}
	}

	namespace FNNAME
	{
		static std::string ReadGetNameFromFName(int key) {
			uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
			uint16_t NameOffset = (uint16_t)key;

			uint64_t NamePoolChunk = read<uint64_t>(base_address + actors::Uworld + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset);
			uint16_t nameEntry = read<uint16_t>(NamePoolChunk);

			int nameLength = nameEntry >> 6;
			char buff[1024];
			if ((uint32_t)nameLength)
			{
				for (int x = 0; x < nameLength; ++x)
				{
					buff[x] = read<char>(NamePoolChunk + 4 + x);
				}

				char* v2 = buff; // rdi 
				__int64 result; // rax 
				unsigned int v5 = nameLength; // ecx 
				__int64 v6; // r8 
				char v7; // cl 
				unsigned int v8; // eax 

				result = 22i64;
				if (v5)
				{
					v6 = v5;
					do
					{
						v7 = *v2++;
						v8 = result + 45297;
						*(v2 - 1) = v8 + ~v7;
						result = (v8 << 8) | (v8 >> 8);
						--v6;
					} while (v6);
				}

				buff[nameLength] = '\0';
				return std::string(buff);
			}
			else {
				return "";
			}
		}


		static std::string GetNameFromFName(int key)
		{
			uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
			uint16_t NameOffset = (uint16_t)key;

			uint64_t NamePoolChunk = read<uint64_t>(base_address + actors::Uworld + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset);
			if (read<uint16_t>(NamePoolChunk) < 64)
			{
				auto a1 = read<DWORD>(NamePoolChunk + 4);
				return ReadGetNameFromFName(a1);
			}
			else
			{
				return ReadGetNameFromFName(key);
			}
		}
	}
}