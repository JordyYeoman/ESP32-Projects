const express = require("express");
const app = express();
const http = require("http");
const cors = require("cors");
const { networkInterfaces } = require('os');
const { Server } = require("socket.io");
app.use(cors());

// Getting the server ip address on local network
const nets = networkInterfaces();
const results = Object.create(null); // Or just '{}', an empty object

for (const name of Object.keys(nets)) {
    for (const net of nets[name]) {
        // Skip over non-IPv4 and internal (i.e. 127.0.0.1) addresses
        // 'IPv4' is in Node <= 17, from 18 it's a number 4 or 6
        const familyV4Value = typeof net.family === 'string' ? 'IPv4' : 4
        if (net.family === familyV4Value && !net.internal) {
            if (!results[name]) {
                results[name] = [];
            }
            results[name].push(net.address);
        }
    }
}
// Used to get ip address of express server and pass onto socketio client on esp32
console.log("RESULTS: ", results);

const PORT = process.env.PORT || 7700;

const server = http.createServer(app);

// TODO - Accept only origin from local network
const io = new Server(server, {
  cors: {
    origin: "*",
    methods: ["GET", "POST"],
  },
});

// PacketType: {
//     '0': 'CONNECT',
//     '1': 'DISCONNECT',
//     '2': 'EVENT',
//     '3': 'ACK',
//     '4': 'CONNECT_ERROR',
//     '5': 'BINARY_EVENT',
//     '6': 'BINARY_ACK',
// }

io.on("connection", (socket) => {
  console.log(`User Connected: ${socket.id}`);

  socket.on("message", (data) => {
    socket.broadcast.emit("receive_message", data);
  });

  socket.on("get_some", (data) => {
    socket.broadcast.emit("go_get_some", data);
  })

  socket.on('toggle_led', (data) => {
    socket.broadcast.emit('led_status', data);
  });
});

server.listen(PORT, () => {
  console.log("⚡ Good Morning Sir, we are currently listening on PORT: " + PORT);
});