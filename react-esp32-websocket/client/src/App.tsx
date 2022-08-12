import './App.css';
import {io} from 'socket.io-client';
import { useEffect, useState } from 'react';
import { json } from 'stream/consumers';


// NOTE: All messages on the websocket should be passed as an object 
// EG - { message: x } , otherwise the microcontroller will not be able to handle the incoming message

function App() {
  const socket = io('http://localhost:7700');
  const sendMessage = (msg: any) => {
    socket.emit('message', { message:  msg });
  }
  const sendMotivation = (msg: string) => {
    socket.emit('get_some', { message: msg});
  }
  const toggleLed = (val: boolean) => {
    socket.emit('toggle_led', { message: `${val}`});
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
    socket.on('ESP32_DATA', (data: any) => {
      console.log("ESP32_DATA: ", data)
    });
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
  const [ledStatus, setLedStatus] = useState<string>('off');
  return <>
    <div>Led Status: {JSON.stringify(ledStatus)}</div>
    <button onClick={()=> {
      console.log("LED STATUS: ", ledStatus);
      if(ledStatus === 'off') {
        action('on')  
        setLedStatus('on');
      }  else {
        action('off');
        setLedStatus('off');
      }
      }
      }>Toggle LED</button>
  </>
}