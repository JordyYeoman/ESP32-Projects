import express from 'express';
import { createServer } from 'http';
import { Server } from 'socket.io';

const app = express();
const httpServer = createServer(app);
const port = process.env.PORT || 3000;
// Allowing messages from any origin, fix to only allow from specific web domain.
const io = new Server(httpServer, {
  cors: {
    origin: '*',
  },
});

httpServer.listen(port, () => {
  console.log('BROOOOO, server listening on: ', port);
});

// Socketio controls
io.on('connection', (socket) => {
  console.log('SHITS REAL SON, SOMEBODY UP IN THIS BITCH -> ID: ', socket?.id);

  socket.on('start', function (data) {
    console.log('Incoming data from: ' + `${socket?.id} `, ' data: ', data);
  });

  socket.on('dataUpdate', () => {
    console.log("New data recieved from: " + `${socket?.id}---DATA: ${DATA}`);
  })

  // Emit all player positions
//   socket.emit();

  // Send to the connected user
  socket.emit('event', { message: 'You are connected boyyyyy!' });
});