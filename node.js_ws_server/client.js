var WebSocket = require('ws');

class UserClient
{
    constructor()
    {
        //连接协议对象
        this.websocket = null;
        //请求消息id
        //每次发送的请求对应一个数字id
        //每个id对应一个回调函数
        this.msgId = 0;
        //消息回调函数表<k=id,v=callback>
        this.msg_callback = {};
        //心跳定时任务的id
        this.intervalId = null;
    }
    //建立连接
    connect(server_url,callback)
    {
        var self = this;
        try {
            this.websocket = new WebSocket(server_url);
        } catch (e) {
            console.log("new WebSocket error:" + e);
            return;
        }

        this.websocket.onopen = function(){
            console.log("websocket.onopen");
            if(callback)
                callback(self);

            self.intervalId = setInterval(function()
            {
                self.request("cs_msg_heart", null);
            },5000);
        }

        this.websocket.onclose = function(){
            console.log("websocket.onclose");
        }

        this.websocket.onerror = function(evt){
            console.log("websocket.onerror: " + evt.data);
        }

        this.websocket.onmessage = function(evt){
            console.log("websocket.onmessage: " + evt.data);

            try {
                //收到的json字符串转换为json对象
                var jsonObj = JSON.parse(evt.data);
                //查找msgId有没有对应的回调函数
                if(self.msg_callback.hasOwnProperty(jsonObj.msgId))
                {
                    var call = self.msg_callback[jsonObj.msgId];
                    call(jsonObj);
                    delete(self.msg_callback[jsonObj.msgId]);
                }
            } catch (e) {
                console.log("websocket.onmessage: " + e);
                return;
            }
        }
    }
    //发起请求
    request(cmdStr, jsonData, callback)
    {
        if (this.websocket.readyState != WebSocket.OPEN) {
            console.log("send failed. websocket not open. please check.");
            return;
        }
        var jsonObj = {
            cmd:cmdStr,
            is_req:true,
            msgId:++this.msgId,
            time:Date.now(),
            data:jsonData
        }
        this.msg_callback[this.msgId] = callback;
        var jsonstr = JSON.stringify(jsonObj);
        console.log(jsonstr);
        this.websocket.send(jsonstr);
    }
    //关闭连接
    close()
    {
        clearInterval(this.intervalId);

        if(this.websocket)
            this.websocket.close();
    }
    //注册账号
    register(username, password)
    {
        this.request("cs_msg_register",
        {
            username:username,
            password:password
        }
        ,function(msg){
            console.log("注册结果："+msg.data);
        });
    }
}

/*
var client = new UserClient();

client.connect("ws://127.0.0.1:4567",function(user){
    user.register("test001", "abc1234");
})
*/

var users = new Array();
var count = 10;

for(var n = 0; n < count; n++)
{
    users[n] =  new UserClient();

    users[n].username = "test00"+n;
    users[n].password = "abc1234";
    users[n].connect("ws://127.0.0.1:4567",function(user){
        user.register(user.username, user.password);
    })
}