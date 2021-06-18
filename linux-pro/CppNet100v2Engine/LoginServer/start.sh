cd `dirname $0`
#################
#key-val
#字典
#std#map<k,v>
##################
nOpenFile=`ulimit -n`
if [ $nOpenFile -lt 204800 ];then
	echo "重置当前进程可以打开的最大文件数"
	ulimit -n 204800
fi
echo "当前进程可以打开的最大文件数"
ulimit -n
#服务端IP地址
cmd='strIP=192.168.1.117'
#服务端端口
cmd=$cmd" nPort=4567"
#csGateServer URL
cmd=$cmd" csGateUrl=ws://192.168.88.133:4567"
#工作线程数量
cmd=$cmd" nThread=1"
#每个工作线程，创建多少个客户端
cmd=$cmd" nClient=10"
###数据会先写入发送缓冲区
###等待socket可写时才实际发送
#每个客户端在nSendSleep(毫秒)时间内
#最大可写入nMsg条Login消息
#每条消息100字节（Login）
cmd=$cmd" nMsg=1"
cmd=$cmd" nSendSleep=10"
#客户端发送缓冲区大小（字节）
cmd=$cmd" nSendBuffSize=1024"
#客户端接收缓冲区大小（字节）
cmd=$cmd" nRecvBuffSize=1024"
#检查接收到的服务端消息ID是否连续
cmd=$cmd" -checkMsgID"
#检测-发送的消息已被服务器回应
#收到服务器回应后才发送下一条消息
cmd=$cmd" -chekSendBack"
cmd=$cmd" -ipv4"
#启动程序 传入参数
./start $cmd
#
read -p "..press any key to exit.." var

