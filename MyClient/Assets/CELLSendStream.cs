using System.Collections;
using System.Collections.Generic;
using System;
using System.Text;

public class CELLSendStream
{
    #region c#处理
    List<byte> _byteList;

    public List<byte> ByteList => _byteList;

    public CELLSendStream(int nSize = 128)
    {
        _byteList = new List<byte>(nSize);
    }

    public byte[] Data 
    { 
        get 
        {
            return _byteList.ToArray();
        } 
    }

    public int DataSize
    {
        get
        {
            return _byteList.Count;
        }
    }

    public void SetNetCMD(CMD cmd)
    {
        WriteUInt16((UInt16)cmd);
    }

    public void Write(byte[] data)
    {
        _byteList.AddRange(data);
    }

    public void WriteInt8(sbyte n)
    {
        _byteList.Add((byte)n);
    }

    public void WriteInt16(Int16 n)
    {
        Write(BitConverter.GetBytes(n));
    }

    public void WriteInt32(Int32 n)
    {
        Write(BitConverter.GetBytes(n));
    }

    public void WriteInt64(Int64 n)
    {
        Write(BitConverter.GetBytes(n));
    }

    public void WriteUInt8(byte n)
    {
        _byteList.Add(n);
    }

    public void WriteUInt16(UInt16 n)
    {
        Write(BitConverter.GetBytes(n));
    }

    public void WriteUInt32(UInt32 n)
    {
        Write(BitConverter.GetBytes(n));
    }

    public void WriteUInt64(UInt64 n)
    {
        Write(BitConverter.GetBytes(n));
    }

    public void WriteFloat(float n)
    {
        Write(BitConverter.GetBytes(n));
    }

    public void WriteDouble(double n)
    {
        Write(BitConverter.GetBytes(n));
    }

    public void WriteString(string s)
    {
        byte[] buffer = Encoding.UTF8.GetBytes(s);
        WriteUInt32((UInt32)buffer.Length + 1);
        Write(buffer);
        WriteUInt8(0);
    }

    public void WriteBytes(byte[] data)
    {
        WriteUInt32((UInt32)data.Length);
        Write(data);
    }

    public void WriteInts(int[] data)
    {
        WriteUInt32((UInt32)data.Length);
        for(int i = 0; i < data.Length; ++i)
        {
            WriteInt32(data[i]);
        }
    }

    public void Finsh()
    {
        UInt16 len = (UInt16)_byteList.Count;
        len += 2;
        _byteList.InsertRange(0, BitConverter.GetBytes(len));
    }
    #endregion
}
