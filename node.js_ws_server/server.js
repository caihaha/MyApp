var WebSocketServer = require('ws').Server;

wss = new WebSocketServer({ port: 4567 });
wss.on('connection', function (ws) {
    console.log('client connected');
    ws.send('ni hao.');
    ws.on('message', function (message) {
        console.log('recv data from client: ' + message.length+', '+message);
        ws.send(message);
    });

    ws.on('close', function (params) {
        console.log('params: %s', params);
    });
});

console.log('..WebSocketServer..');