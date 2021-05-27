using System.Collections;
using System.Collections.Generic;
using System;
using System.Text;
using System.Runtime.InteropServices;

public class CELLWriteStream
{
    IntPtr _cppStreamObj;
    Int32 _nSize;

    public CELLWriteStream(int nSize = 128)
    {
        _nSize = nSize;
        _cppStreamObj = CELLWriteStream_Create(nSize);
    }

    public IntPtr Data
    {
        get
        {
            return _cppStreamObj;
        }
    }

    public int DataSize
    {
        get
        {
            return _nSize;
        }
    }

    [DllImport("CppNet100")]
    public static extern IntPtr CELLWriteStream_Create(int nSize);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteInt8(IntPtr cppObjStream, sbyte n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteInt16(IntPtr cppObjStream, Int16 n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteInt32(IntPtr cppObjStream, Int32 n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteInt64(IntPtr cppObjStream, Int64 n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteUInt8(IntPtr cppObjStream, byte n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteUInt16(IntPtr cppObjStream, UInt16 n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteUInt32(IntPtr cppObjStream, UInt32 n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteUInt64(IntPtr cppObjStream, UInt64 n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteFloat(IntPtr cppObjStream, float n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteDouble(IntPtr cppObjStream, double n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_WriteString(IntPtr cppObjStream, string n);

    [DllImport("CppNet100")]
    public static extern bool CELLWriteStream_Release(IntPtr cppObjStream);

    public void SetNetCMD(CMD cmd)
    {
        WriteUInt16((UInt16)cmd);
    }

    public void WriteInt8(sbyte n)
    {
        CELLWriteStream_WriteInt8(_cppStreamObj, n);
    }

    public void WriteInt16(Int16 n)
    {
        CELLWriteStream_WriteInt16(_cppStreamObj, n);
    }

    public void WriteInt32(Int32 n)
    {
        CELLWriteStream_WriteInt32(_cppStreamObj, n);
    }

    public void WriteInt64(Int64 n)
    {
        CELLWriteStream_WriteInt64(_cppStreamObj, n);
    }

    public void WriteUInt8(byte n)
    {
        CELLWriteStream_WriteUInt8(_cppStreamObj, n);
    }

    public void WriteUInt16(UInt16 n)
    {
        CELLWriteStream_WriteUInt16(_cppStreamObj, n);
    }

    public void WriteUInt32(UInt32 n)
    {
        CELLWriteStream_WriteUInt32(_cppStreamObj, n);
    }

    public void WriteUInt64(UInt64 n)
    {
        CELLWriteStream_WriteUInt64(_cppStreamObj, n);
    }

    public void WriteFloat(float n)
    {
        CELLWriteStream_WriteFloat(_cppStreamObj, n);
    }

    public void WriteDouble(double n)
    {
        CELLWriteStream_WriteDouble(_cppStreamObj, n);
    }

    public void WriteString(string s)
    {
        byte[] buffer = Encoding.UTF8.GetBytes(s);
        WriteUInt32((UInt32)buffer.Length + 1);
        for(int i = 0; i < buffer.Length; ++i)
        {
            WriteUInt8(buffer[i]);
        }
        WriteUInt8(0);
    }

    public void WriteBytes(byte[] data)
    {
        WriteUInt32((UInt32)data.Length);
        for (int i = 0; i < data.Length; ++i)
        {
            WriteUInt8(data[i]);
        }
    }

    public void WriteInts(int[] data)
    {
        WriteUInt32((UInt32)data.Length);
        for (int i = 0; i < data.Length; ++i)
        {
            WriteInt32(data[i]);
        }
    }

    public void Finsh()
    {
    }
	
	public bool Release()
	{
		return CELLWriteStream_Release(_cppStreamObj);
	}
}
