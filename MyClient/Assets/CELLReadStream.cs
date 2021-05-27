using System.Collections;
using System.Collections.Generic;
using System;
using System.Text;
using System.Runtime.InteropServices;

public class CELLReadStream
{
    IntPtr _cppStreamObj;

    [DllImport("CppNet100")]
    public static extern IntPtr CELLReadStream_Create(IntPtr data, int nSize);

    [DllImport("CppNet100")]
    public static extern sbyte CELLReadStream_ReadInt8(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern Int16 CELLReadStream_ReadInt16(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern Int32 CELLReadStream_ReadInt32(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern Int64 CELLReadStream_ReadInt64(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern byte CELLReadStream_ReadUInt8(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern UInt16 CELLReadStream_ReadUInt16(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern UInt32 CELLReadStream_ReadUInt32(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern UInt64 CELLReadStream_ReadUInt64(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern float CELLReadStream_ReadFloat(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern double CELLReadStream_ReadDouble(IntPtr cppObjStream);
	
	// [DllImport("CppNet100")]
    // public static extern bool CELLReadStream_ReadString(IntPtr cppObjStream, IntPtr buffer, Int32 len);
	
	[DllImport("CppNet100")]
    public static extern void CELLReadStream_Release(IntPtr cppObjStream);
	
	[DllImport("CppNet100")]
    public static extern UInt32 CELLReadStream_OnlyReadUInt32(IntPtr cppObjStream);

    public CELLReadStream(IntPtr data, int len)
    {
        _cppStreamObj = CELLReadStream_Create(data, len);
    }

    public UInt16 GetNetCmd()
    {
        return ReadUInt16();
    }

    public sbyte ReadInt8()
    {
        return CELLReadStream_ReadInt8(_cppStreamObj);
    }

    public Int16 ReadInt16()
    {
        return CELLReadStream_ReadInt16(_cppStreamObj);
    }

    public Int32 ReadInt32()
    {
        return CELLReadStream_ReadInt32(_cppStreamObj);
    }

    public Int64 ReadInt64()
    {
        return CELLReadStream_ReadInt64(_cppStreamObj);
    }

    public byte ReadUInt8()
    {
        return CELLReadStream_ReadUInt8(_cppStreamObj);
    }

    public UInt16 ReadUInt16()
    {
        return CELLReadStream_ReadUInt16(_cppStreamObj);
    }
    public UInt32 ReadUInt32()
    {
        return CELLReadStream_ReadUInt32(_cppStreamObj);
    }

    public UInt64 ReadUInt64()
    {
        return CELLReadStream_ReadUInt64(_cppStreamObj);
    }

    public float ReadFloat()
    {
        return CELLReadStream_ReadFloat(_cppStreamObj);
    }

    public double ReadDouble()
    {
        return CELLReadStream_ReadDouble(_cppStreamObj);
    }

    public string ReadString()
    {
		Int32 len = (Int32)ReadUInt32();
		byte[] buffer = new byte[len];
		for(int i = 0; i < len; ++i)
		{
			buffer[i] = ReadUInt8();
		}
		
		return Encoding.UTF8.GetString(buffer, 0, len);
    }
	
	public void Release()
    {
        CELLReadStream_Release(_cppStreamObj);
    }
	
	public UInt32 OnlyReadUInt32()
    {
        return CELLReadStream_OnlyReadUInt32(_cppStreamObj);
    }

    public Int32[] ReadInts()
    {
        Int32 len = ReadInt32();
        Int32[] data = new Int32[len];

        for(int i = 0; i < len; ++i)
        {
            data[i] = ReadInt32();
        }

        return data;
    }

}
