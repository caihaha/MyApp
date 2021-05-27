using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;
using AOT;

public enum CMD
{
    CMD_LOGIN = 10,
    CMD_LOGIN_RESULT,
    CMD_LOGOUT,
    CMD_LOGOUT_RESULT,
    CMD_NEW_USER_JOIN,
    CMD_C2S_HEART,
    CMD_S2C_HEART,
    CMD_ERROR
};

public class CELLTcpClient : MonoBehaviour
{
    public CELLTcpClient()
    {
        _thisObj = IntPtr.Zero;
        _cppClientObj = IntPtr.Zero;
    }
    private GCHandle _handle;
    IntPtr _thisObj;
    IntPtr _cppClientObj;

    public delegate void OnNetMsgCallBack(IntPtr obj, IntPtr data, int len);
    [MonoPInvokeCallback(typeof(OnNetMsgCallBack))]
    public void DellOnNetMsgCallBack(IntPtr csObj, IntPtr data, int len)
    {
        Debug.Log(len);
        GCHandle h = GCHandle.FromIntPtr(csObj);
        CELLTcpClient obj = h.Target as CELLTcpClient;
        if(obj == null)
        {
            return;
        }
        obj.OnNetMsgBytes(data, len);
    }

    [DllImport("CppNet100")]
    public static extern IntPtr CELLClient_Create(IntPtr obj, OnNetMsgCallBack cb, int sendSize, int recvSize);

    [DllImport("CppNet100")]
    public static extern bool CELLClient_Connect(IntPtr cppClientObj, string ip, UInt16 port);

    [DllImport("CppNet100")]
    public static extern bool CELLClient_OnRun(IntPtr cppClientObj);

    [DllImport("CppNet100")]
    public static extern void CELLClient_Close(IntPtr cppClientObj);

    [DllImport("CppNet100")]
    public static extern int CELLClient_SendData(IntPtr cppClientObj, byte[] data, int len);

    [DllImport("CppNet100")]
    public static extern int CELLClient_SendWriteStream(IntPtr cppClientObj, IntPtr cppStreamObj);

    public void Creat()
    {
        _handle = GCHandle.Alloc(this);
        _thisObj = GCHandle.ToIntPtr(_handle);

        _cppClientObj = CELLClient_Create(_thisObj, DellOnNetMsgCallBack, 10240, 10240);
    }

    public bool Connect(string ip, UInt16 port)
    {
        if (_cppClientObj == IntPtr.Zero)
        {
            return false;
        }

        return CELLClient_Connect(_cppClientObj, ip, port);
    }

    public bool OnRun()
    {
        if(_cppClientObj == IntPtr.Zero)
        {
            return false;
        }

        return CELLClient_OnRun(_cppClientObj);
    }

    public void Close()
    {
        if (_cppClientObj == IntPtr.Zero)
        {
            return;
        }

        CELLClient_Close(_cppClientObj);
        _cppClientObj = IntPtr.Zero;
        _thisObj = IntPtr.Zero;
        _handle.Free();
    }

    // 发送数据
    public int SendData(CELLSendStream stream)
    {
        if (_cppClientObj == IntPtr.Zero)
        {
            return 0;
        }

        return CELLClient_SendData(_cppClientObj, stream.Data, stream.DataSize);
    }

    public int SendData(CELLWriteStream stream)
    {
        if (_cppClientObj == IntPtr.Zero)
        {
            return 0;
        }

        return CELLClient_SendWriteStream(_cppClientObj, stream.Data);
    }

    // 解析接受的数据
    public virtual void OnNetMsgBytes(IntPtr data, int len)
    {

    }
}
