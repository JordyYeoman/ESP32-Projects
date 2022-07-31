import './App.css';
import {io} from 'socket.io-client';
import { useEffect, useState } from 'react';
import { json } from 'stream/consumers';

function App() {
  const socket = io('http://localhost:7700');
  const sendMessage = (msg: any) => {
    socket.emit('message', { message:  msg });
  }
  const sendMotivation = (msg: string) => {
    socket.emit('get_some', { message: msg});
  }
  const toggleLed = (val: boolean) => {
    socket.emit('toggle_led', val);
  }

  useEffect(() => {
    socket.on('receive_message', (data: any) => {
      console.log("DATA RECIEVED: ", data.message);
    });
    socket.on('go_get_some', (data: any) => {
      console.log("Im getting some!: ", data.message);
    });
    socket.on('led_status', (data: any) => {
      console.log("LED STATUS: ", data);
    })
  },[socket]);

  return (
    <div className="App">
      <div>Hello World</div>
      <button onClick={()=> {sendMessage("Hello")}}>Hi</button>
      <button onClick={()=> {sendMotivation("Mate, you got this, JUST SEND IT!!")}}>Motivate</button>
      <ToggleLedButton action={toggleLed} />
    </div>
  );
}

export default App;


const ToggleLedButton = ({action}: {action: Function}) => {
  const [ledStatus, setLedStatus] = useState<boolean>(false);
  return <>
    <div>Led Status: {JSON.stringify(ledStatus)}</div>
    <button onClick={()=> {
      setLedStatus(!ledStatus);
      action(!ledStatus)}
      }>Toggle LED</button>
  </>
}