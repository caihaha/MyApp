cd `dirname $0`
##################
#key-val
#字典
#std#map<k,v>
##################
ulimit -n
ulimit -n 81920
ulimit -n
#服务端IP地址
cmd='strIP=any'
#服务端端口
cmd=$cmd' nPort=4567'
#消息处理线程数量
cmd=$cmd" nThread=1"
#客户端连接上限
cmd="$cmd nMaxClient=81920"
#客户端发送缓冲区大小（字节）
cmd=$cmd" nSendBuffSize=10240"
#客户端接收缓冲区大小（字节）
cmd=$cmd" nRecvBuffSize=10240"
#收到消息后将返回应答消息
cmd=$cmd" -sendback"
#提示发送缓冲区已写满
#当出现sendfull提示时，表示当次消息被丢弃
cmd=$cmd" -sendfull"
#检查接收到的客户端消息ID是否连续
cmd=$cmd" -checkMsgID"
#自定义标志 未使用
cmd=$cmd" -p"

#启动程序 传入参数
./start $cmd
#
read -p "..press any key to exit.." var

