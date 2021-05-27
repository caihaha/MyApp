using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;
using AOT;

public class NewBehaviourScript : CELLTcpClient
{
    private string _ip = "127.0.0.1";
    private UInt16 _port = 4567;

    [DllImport("CppNet100")]
    public static extern int Add(int a, int b);

    public delegate void CallBack1(string s);
    [MonoPInvokeCallback(typeof(CallBack1))]
    public void CallBackFun1(string s)
    {
        Debug.Log(s);
    }

    [DllImport("CppNet100")]
    public static extern int TestCall1(string s, CallBack1 cb);

    // Start is called before the first frame update
    void Start()
    {
        Creat();
        Connect(_ip, _port);

        CELLWriteStream stream = new CELLWriteStream();
        stream.SetNetCMD(CMD.CMD_LOGOUT);
        stream.WriteInt8(1);
        stream.WriteInt16(2);
        stream.WriteInt32(3);
        stream.WriteFloat(4.5f);
        stream.WriteDouble(6.7);
        stream.WriteString("client");
        stream.WriteString("ahah");
        int []b = { 1, 2, 3, 4, 5 };
        stream.WriteInts(b);
        stream.Finsh();
        SendData(stream);
		stream.Release();
    }

    // Update is called once per frame
    void Update()
    {
        OnRun();
    }

    void OnDestroy()
    {
        Close();
    }

    public override void OnNetMsgBytes(IntPtr data, int len)
    {
        CELLReadStream stream = new CELLReadStream(data, len);

        stream.ReadInt16();
        //读取消息命令
        stream.GetNetCmd();
        var n1 = stream.ReadInt8();
        var n2 = stream.ReadInt16();
        var n3 = stream.ReadInt32();
        var n4 = stream.ReadFloat();
        var n5 = stream.ReadDouble();
        var name = stream.ReadString();
        var pw = stream.ReadString();
        var ata = stream.ReadInts();
		stream.Release();
    }
}
