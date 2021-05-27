using System.Collections;
using System.Collections.Generic;
using System;
using System.Text;
using System.Runtime.InteropServices;

public class CELLRecvStream
{
    byte[] _buffer;
    Int32 _lastPos;

    public byte[] Data => _buffer;

    public CELLRecvStream(IntPtr data, int len)
    {
        byte[] _buffer = new byte[len];
        Marshal.Copy(data, _buffer, 0, len);
    }

    private void Pop(Int32 n)
    {
        _lastPos += n;
    }

    private bool CanRead(Int32 n)
    {
        return _buffer.Length - _lastPos >= n;
    }

    public UInt16 GetNetCmd()
    {
        return ReadUInt16();
    }

    public sbyte ReadInt8()
    {
        sbyte ret = 0;
        if (CanRead(sizeof(sbyte)))
        {
            ret = (sbyte)_buffer[_lastPos];
            Pop(sizeof(sbyte));
        }

        return ret;
    }

    public Int16 ReadInt16()
    {
        Int16 ret = 0;
        if (CanRead(sizeof(Int16)))
        {
            ret = BitConverter.ToInt16(_buffer, _lastPos);
            Pop(sizeof(Int16));
        }

        return ret;
    }

    public Int32 ReadInt32()
    {
        Int32 ret = 0;
        if (CanRead(sizeof(Int32)))
        {
            ret = BitConverter.ToInt32(_buffer, _lastPos);
            Pop(sizeof(Int32));
        }

        return ret;
    }

    public Int64 ReadInt64()
    {
        Int64 ret = 0;
        if (CanRead(sizeof(Int64)))
        {
            ret = BitConverter.ToInt64(_buffer, _lastPos);
            Pop(sizeof(Int64));
        }

        return ret;
    }

    public byte ReadUInt8()
    {
        byte ret = 0;
        if (CanRead(sizeof(byte)))
        {
            ret = _buffer[_lastPos];
            Pop(sizeof(byte));
        }

        return ret;
    }

    public UInt16 ReadUInt16()
    {
        UInt16 ret = 0;
        if (CanRead(sizeof(UInt16)))
        {
            ret = BitConverter.ToUInt16(_buffer, _lastPos);
            Pop(sizeof(UInt16));
        }

        return ret;
    }
    public UInt32 ReadUInt32()
    {
        UInt32 ret = 0;
        if (CanRead(sizeof(UInt32)))
        {
            ret = BitConverter.ToUInt32(_buffer, _lastPos);
            Pop(sizeof(UInt32));
        }

        return ret;
    }

    public UInt64 ReadUInt64()
    {
        UInt64 ret = 0;
        if (CanRead(sizeof(UInt64)))
        {
            ret = BitConverter.ToUInt64(_buffer, _lastPos);
            Pop(sizeof(UInt64));
        }

        return ret;
    }

    public float ReadFloat()
    {
        float ret = 0;
        if (CanRead(sizeof(float)))
        {
            ret = BitConverter.ToSingle(_buffer, _lastPos);
            Pop(sizeof(float));
        }

        return ret;
    }

    public double ReadDouble()
    {
        double ret = 0;
        if (CanRead(sizeof(double)))
        {
            ret = BitConverter.ToDouble(_buffer, _lastPos);
            Pop(sizeof(double));
        }

        return ret;
    }

    public string ReadString()
    {
        string ret = "";
        Int32 len = 0;
        if (CanRead(sizeof(Int32)))
        {
            len = BitConverter.ToInt32(_buffer, _lastPos);
        }
        if (CanRead(len) && len > 0)
        {
            Pop(sizeof(Int32));
            ret = Encoding.UTF8.GetString(_buffer, _lastPos, len);
            Pop(len);
        }

        return ret;
    }

    public Int32[] ReadInts()
    {
        Int32 len = 0;
        if (CanRead(sizeof(Int32)))
        {
            len = BitConverter.ToInt32(_buffer, _lastPos);
        }
        Int32[] data = new Int32[len];
        if (CanRead(len * sizeof(Int32)) && len > 0)
        {
            Pop(sizeof(Int32));
            for (int i = 0; i < len; ++i)
            {
                data[i] = ReadInt32();
            }
        }

        return data;
    }

}
